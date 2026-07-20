#include "uthash.h"
#include "loader.h"
#include "locker.h"
#include "clips.h"


#ifdef WIN32

#else
#define _strdup strdup
#endif

struct library_table {
	char* libname;            /* we'll use this field as the key */
	void* ref;
	UT_hash_handle hh; /* makes this structure hashable */
};
struct function_table {
	char* function;            /* we'll use this field as the key */
	char* libname;
	CALLABLE ref;
	UT_hash_handle hh; /* makes this structure hashable */
};
static struct library_table* libraries = NULL;
static struct function_table* functions = NULL;
/* The lock guarding the process-global tables above is not a mutable global:
   it is obtained through ensure_lock(), which creates it exactly once in a
   thread-safe way (see locker.h). */


int PerformLoading(const char* library, const char* function) {
	int result = 0;
	void* lib = NULL;
	CALLABLE func = NULL;
	struct library_table* lt = NULL;
	struct library_table* lib_exists = NULL;
	struct function_table* fc = NULL;
	struct function_table* func_exists = NULL;

	/* F4 constraint: function names must be unique across ALL libraries. If this
	   name is already registered from a DIFFERENT library, refuse -- otherwise
	   this environment's calls would silently dispatch into the other library.
	   The first library to register a name owns it (process-globally) until it is
	   fully unloaded. Loading the same name from the SAME library is fine (that's
	   the cross-environment dedup path). */
	lock_read(ensure_lock());
	HASH_FIND_STR(functions, function, func_exists);
	if (func_exists != NULL && strcmp(func_exists->libname, library) != 0) {
		unlock_read(ensure_lock());
		return -4;   /* name already loaded from a different library */
	}
	unlock_read(ensure_lock());
	func_exists = NULL;   /* re-looked-up under lock below */

	lock_read(ensure_lock());
	HASH_FIND_STR(libraries, library, lib_exists);
	unlock_read(ensure_lock());
	if (!lib_exists) {
		lib = load_lib(library);
		if (lib) {
			lock_write(ensure_lock());
			/* F3: re-check under the WRITE lock -- another thread may have added
			   this library while we were loading it (the read-check above and this
			   insert are not atomic). Only one entry wins; the loser discards its
			   handle below. Without this, both threads HASH_ADD the same key
			   (uthash does not dedup) -> a duplicate, leaked entry. */
			HASH_FIND_STR(libraries, library, lib_exists);
			if (!lib_exists) {
				lt = (struct library_table*)malloc(sizeof(struct library_table));
				lt->libname = _strdup(library);
				lt->ref = lib;
				HASH_ADD_KEYPTR(hh, libraries, lt->libname, strlen(lt->libname), lt);
				lib = NULL;   /* ownership transferred to the table */
			}
			unlock_write(ensure_lock());
			if (lib != NULL) {
				/* lost the race: release our duplicate handle. free_lib balances
				   the extra dlopen/LoadLibrary refcount, so the winner's handle
				   (same underlying library) stays valid. */
				free_lib(lib);
			}
		}
	}
	lock_read(ensure_lock());
	HASH_FIND_STR(libraries, library, lib_exists);
	unlock_read(ensure_lock());
	if (lib_exists) {
		lock_read(ensure_lock());
		HASH_FIND_STR(functions, function, func_exists);
		unlock_read(ensure_lock());
		if (!func_exists) {
			func = load_fn(lib_exists->ref, function);
			if (func) {
				lock_write(ensure_lock());
				/* F3: re-check under the WRITE lock before inserting, same as the
				   library above. func is just a resolved pointer into the library,
				   so a race loser has nothing to release -- it simply doesn't add. */
				HASH_FIND_STR(functions, function, func_exists);
				if (!func_exists) {
					fc = (struct function_table*)malloc(sizeof(struct function_table));
					fc->function = _strdup(function);
					fc->libname = _strdup(library);
					fc->ref = func;
					HASH_ADD_KEYPTR(hh, functions, fc->function, strlen(fc->function), fc);
				}
				unlock_write(ensure_lock());
			}
		}
	}
	lock_read(ensure_lock());
	HASH_FIND_STR(functions, function, func_exists);
	unlock_read(ensure_lock());
	if (func_exists) {
		result = 1;
	}
	return result;
}


void Dispatcher(
	Environment* env,
	UDFContext* udfc,
	UDFValue* out)
{
	/*
	* Credit: Matteo Cafasso from clipspy for original implementation for runtime
	*	This runtime dispatch system is modeled after clipspy python-function
	*	addudf will point to this router function, which can use runtime system to sort out where to actually dispatch to
	*	every custom function should route to here where the first argument is the lookup name of the actual function to call
	*/

	// The first argument is the function name
	UDFValue theArg;
	struct function_table* func_exists = NULL;
	if (!UDFFirstArgument(udfc, STRING_BIT | SYMBOL_BIT, &theArg)) {
		out->lexemeValue = CreateBoolean(env, false);
		return;
	}
	lock_read(ensure_lock());
	HASH_FIND_STR(functions, theArg.lexemeValue->contents, func_exists);
	unlock_read(ensure_lock());
	if (func_exists) {
		func_exists->ref(env, udfc, out);
	} else {
		/* Function not loaded -- e.g. it was unloaded (unload is process-global;
		   see F2) while this environment still had a deffunction bound to it, or
		   the library it came from was released. Fail safe with FALSE rather than
		   leaving `out` unset for the caller to read as garbage. */
		out->lexemeValue = CreateBoolean(env, false);
	}
}

void DefineFuncIfRequired(
	Environment* env, 
	UDFContext* udfc,
	UDFValue* out,
	const char* function) {
	BuildError build_result;
	char builder[1024] = { 0 };

	Deffunction* func =  FindDeffunction(env, function);
	if (!func) {
		int written = snprintf((char *)&builder, 1024, "(deffunction %s ($?args) 	(Dispatch %s (expand$ ?args)))", function, function);
		if (written > 0 && written < 1024) {
			build_result = Build(env, builder);
			if (build_result) {
				out->integerValue = CreateInteger(env, -1);
			} else {
				out->integerValue = CreateInteger(env, 1);
			}
		} else {
			out->integerValue = CreateInteger(env, -2);
		}
	}
	else {
		out->integerValue = CreateInteger(env, -5);
	}
}

void Loader(
	Environment* env,
	UDFContext* udfc,
	UDFValue* out) {
	UDFValue library, function;
	if (!UDFNthArgument(udfc, 1, STRING_BIT, &library) || !UDFNthArgument(udfc, 2, STRING_BIT, &function))
	{
		out->integerValue = CreateInteger(env, -200);
		return;   /* args not populated -- must not fall through and deref them */
	}
	int loaded = PerformLoading(library.lexemeValue->contents, function.lexemeValue->contents);
	if (loaded > 0) {
		DefineFuncIfRequired(env, udfc, out, (const char*)function.lexemeValue->contents);
	}
	else if (loaded == -4) {
		out->integerValue = CreateInteger(env, -4);   /* name collision across libraries */
	}
	else {
		out->integerValue = CreateInteger(env, -3);
	}
}


bool UnDefineFuncIfRequired(
	Environment* env,
	UDFContext* udfc,
	UDFValue* out,
	const char* function) {
	bool success = false;
	Deffunction* func = FindDeffunction(env, function);
	if (!func) {
		/* No deffunction bound in THIS environment -- e.g. the unload fact was
		   asserted in an env that never loaded the function, while the global
		   table entry exists via another env (unload is process-global, F2).
		   Nothing to undefine here; vacuous success so the caller proceeds with
		   the global removal. DeffunctionIsDeletable dereferences its argument,
		   so this must be checked (F7). */
		out->integerValue = CreateInteger(env, 0);
		return true;
	}
	bool deletable = DeffunctionIsDeletable(func);
	if (deletable) {
		bool deleted = Undeffunction(func, env);
		if (deleted) {
			success = true;
			out->integerValue = CreateInteger(env, 0);
		} else {
			out->integerValue = CreateInteger(env, -30);
		}
	} else {
		out->integerValue = CreateInteger(env, -31);
	}
	return success;
}

void UnLoader(
	Environment* env,
	UDFContext* udfc,
	UDFValue* out) {
	UDFValue library, function;
	struct function_table* func_exists = NULL;
	struct library_table* lib_exists = NULL;

	if (!UDFNthArgument(udfc, 1, STRING_BIT, &library) || !UDFNthArgument(udfc, 2, STRING_BIT, &function))
	{
		out->integerValue = CreateInteger(env, -200);
		return;   /* args not populated -- must not fall through and deref them */
	}
	lock_write(ensure_lock());
	HASH_FIND_STR(functions, function.lexemeValue->contents, func_exists);
	if (func_exists) {
		HASH_FIND_STR(libraries, func_exists->libname, lib_exists);
	}
	if (!func_exists || !lib_exists) {
		/* Not in the global table: never loaded, or already unloaded
		   process-globally by another environment (F2). Unlike the -200 path this
		   IS reachable -- the unloadlib rule fires on any hand-asserted
		   (loaded 1) fact and writes `out` into the fact's `loaded` slot -- so
		   `out` must be a defined value, not left unset as garbage (F8). */
		out->integerValue = CreateInteger(env, -32);
	} else {
		struct function_table* other = NULL;
		struct function_table* other_tmp = NULL;
		bool library_still_referenced = false;

		/* Undefine the per-environment deffunction (operates on env, not the
		   tables), then remove the function being unloaded from the global
		   table. */
		UnDefineFuncIfRequired(env, udfc, out, (const char*)function.lexemeValue->contents);
		HASH_DEL(functions, func_exists);

		/* Only unload the library once NO remaining function references it.
		   Unloading it while a sibling function (same library) is still in the
		   table would leave that sibling's ->ref dangling into unmapped code
		   -- a segfault on its next Dispatch (F1). func_exists is out of the
		   hash now but still allocated, so its libname is valid to compare. */
		HASH_ITER(hh, functions, other, other_tmp) {
			if (strcmp(other->libname, func_exists->libname) == 0) {
				library_still_referenced = true;
				break;
			}
		}
		if (!library_still_referenced) {
			lib_exists->ref = free_lib(lib_exists->ref);
			if (!lib_exists->ref) {
				HASH_DEL(libraries, lib_exists);
				free(lib_exists->libname);
				free(lib_exists);
			}
		}

		free(func_exists->libname);
		free(func_exists->function);
		free(func_exists);
	}
	unlock_write(ensure_lock());
}

long loader_library_count(void) {
	long n;
	lock_read(ensure_lock());
	n = (long)HASH_COUNT(libraries);
	unlock_read(ensure_lock());
	return n;
}

long loader_function_count(void) {
	long n;
	lock_read(ensure_lock());
	n = (long)HASH_COUNT(functions);
	unlock_read(ensure_lock());
	return n;
}

/* Register the three loader UDFs. Returns AUE_NO_ERROR only if all three were
   added; otherwise the first failure (so the caller can refuse to set up a
   dispatcher whose dispatch mechanism is non-functional). */
AddUDFError LoadUserFunctions(
	Environment* env)
{
	AddUDFError err = AddUDF(env, "LoadDispatch", "l", 2, 2, "s", Loader, "LoadDispatch", NULL);
	if (err != AUE_NO_ERROR) { return err; }
	err = AddUDF(env, "UnLoadDispatch", "l", 2, 2, "s", UnLoader, "UnLoadDispatch", NULL);
	if (err != AUE_NO_ERROR) { return err; }
	err = AddUDF(env, "Dispatch", "*", 1, UNBOUNDED, "*", Dispatcher, "Dispatch", NULL);
	return err;
}

static BuildError LoadErrorRules(Environment* env) {
	BuildError build_result;
	build_result = Build(env, ""
		"(defrule loader-invalid-args"
		"   ?d <- (functions (loaded -200))"
		"   =>"
		"   (modify ?d "
		"          (error \"Invalid Arguments - Must be library, function as strings\") "
		"   )"
		" )");

	build_result = Build(env, ""
		"(defrule loader-invalid-function-name"
		"   ?d <- (functions (loaded -1))"
		"   =>"
		"   (modify ?d "
		"          (error \"Unable to build rule from loaded library - use ASCII characters for function\") "
		"   )"
		" )");

	build_result = Build(env, ""
		"(defrule loader-invalid-function-length"
		"   ?d <- (functions (loaded -2))"
		"   =>"
		"   (modify ?d "
		"          (error \"Function name is too long, limit function name to 256 characters\") "
		"   )"
		" )");

	build_result = Build(env, ""
		"(defrule loader-load-failed"
		"   ?d <- (functions (loaded -3))"
		"   =>"
		"   (modify ?d "
		"          (error \"Unable to load the requested library or function\") "
		"   )"
		" )");
	build_result = Build(env, ""
		"(defrule loader-name-collision"
		"   ?d <- (functions (loaded -4))"
		"   =>"
		"   (modify ?d "
		"          (error \"Function name already loaded from a different library - function names must be unique across libraries\") "
		"   )"
		" )");
	build_result = Build(env, ""
		"(defrule loader-already-defined"
		"   ?d <- (functions (loaded -5))"
		"   =>"
		"   (modify ?d "
		"          (error \"Function was already defined, not redefining\") "
		"          (loaded 1) "
		"   )"
		" )");
	build_result = Build(env, ""
		"(defrule unloader-not-deletable"
		"   ?d <- (functions (loaded -30))"
		"   =>"
		"   (modify ?d "
		"          (error \"Unable to delete the function\") "
		"   )"
		" )");
	build_result = Build(env, ""
		"(defrule unloader-unable-to-delete"
		"   ?d <- (functions (loaded -31))"
		"   =>"
		"   (modify ?d "
		"          (error \"Function is in use, triggererd reload\") "
		"          (action \"load\") "
		"          (loaded 0) "
		"   )"
		" )");
	build_result = Build(env, ""
		"(defrule unloader-not-loaded"
		"   ?d <- (functions (loaded -32))"
		"   =>"
		"   (modify ?d "
		"          (error \"Function is not loaded - nothing to unload (it may have been unloaded by another environment)\") "
		"   )"
		" )");

	return build_result;
}


/* CLIPS environment cleanup callback: invoked from DestroyEnvironment for each
   environment setup_dispatcher() installed into. Un-counts it. */
static void loader_env_destroyed(Environment* env) {
	(void)env;
	loader_env_unregister();
}


BuildError setup_dispatcher(Environment* env) {
	BuildError  build_result = 0;

	/* The library/function hash tables are process-global (shared across every
	   environment) and are guarded by a single process-wide lock. Force its
	   one-time, thread-safe creation now -- setup typically runs single-threaded,
	   so later concurrent dispatch never has to initialize it. */
	ensure_lock();

	/* Idempotent per environment: if the `functions` deftemplate already exists,
	   this environment has already been set up. Return success before re-adding
	   the UDFs or redefining the template (which fails with [CSTRCPSR4] once
	   facts are in use), so a second call is a harmless no-op. */
	if (FindDeftemplate(env, "functions") != NULL) {
		return BE_NO_ERROR;
	}

	/* Register the loader UDFs FIRST. If any fails, the whole dispatch mechanism
	   is dead and the rules built below would reference missing functions, so
	   report the failure instead of masking it and returning as if set up. */
	if (LoadUserFunctions(env) != AUE_NO_ERROR) {
		return BE_COULD_NOT_BUILD_ERROR;
	}

	/* Count this environment as a live loader user, and arrange to un-count it
	   when it is destroyed. CLIPS runs environment cleanup functions from
	   DestroyEnvironment and offers no public way to remove one, so the decrement
	   is guaranteed to fire exactly once. Only count it if registration actually
	   succeeded (it allocates); an uncounted env just isn't tracked. Done only
	   after the UDFs are in place, so a failed setup is not counted. */
	if (AddEnvironmentCleanupFunction(env, "runtime_loader_env", loader_env_destroyed, 0)) {
		loader_env_register();
	}

	build_result += Build(env, ""
		"(deftemplate functions"
		"    (slot library (type STRING))"
		"    (slot function (type STRING))"
		"    (slot action (type STRING) (default \"load\"))"
		"    (slot loaded (type INTEGER) (default 0))"
		"    (slot error (type STRING))"
		")");

	build_result += Build(env, ""
		"(defrule loadlib"
		"   ?d <- (functions (library ?lib) (function ?func) (action \"load\") (loaded 0))"
		"   =>"
		"   (modify ?d "
		"          (loaded (LoadDispatch ?lib ?func)) "
		"   )"
		" )");
	build_result += Build(env, ""
		"(defrule unloadlib"
		"   ?d <- (functions (library ?lib) (function ?func) (action \"unload\") (loaded 1))"
		"   =>"
		"   (modify ?d "
		"          (loaded (UnLoadDispatch ?lib ?func)) "
		"   )"
		" )");

	build_result += LoadErrorRules(env);
	return build_result;
}


bool teardown_dispatcher(void) {
	struct library_table* lt;
	struct library_table* lt_tmp;
	struct function_table* ft;
	struct function_table* ft_tmp;

	/* Refuse if any environment we set up is still alive. This catches the
	   common ordering mistake (tearing down before destroying environments); it
	   is NOT a defense against concurrent misuse -- a thread could set up a new
	   environment right after this check. The quiescence/threading contract in
	   dispatcher.h still applies and cannot be enforced here. */
	if (loader_env_active() != 0) {
		return false;
	}

	/* Callers MUST also have ensured the loader is quiescent (no other thread in
	   a Dispatch/Load/UnLoad call). See the full contract in dispatcher.h.

	   Free the function table first (its entries only reference table state),
	   then unload each library and free the library table. */
	HASH_ITER(hh, functions, ft, ft_tmp) {
		HASH_DEL(functions, ft);
		free(ft->function);
		free(ft->libname);
		free(ft);
	}
	HASH_ITER(hh, libraries, lt, lt_tmp) {
		HASH_DEL(libraries, lt);
		free_lib(lt->ref);
		free(lt->libname);
		free(lt);
	}
	functions = NULL;
	libraries = NULL;

	/* Destroy the shared lock last; the next setup_dispatcher()/ensure_lock()
	   will build a fresh one. */
	reset_lock();
	return true;
}


