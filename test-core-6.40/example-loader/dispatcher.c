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
static void* table_lock = NULL;


int PerfromLoading(const char* library, const char* function) {
	int result = 0;
	void* lib = NULL;
	CALLABLE func;
	struct library_table* lt = NULL;
	struct library_table* lib_exists = NULL;
	struct function_table* fc = NULL;
	struct function_table* func_exists = NULL;
	lock_read(table_lock);
	HASH_FIND_STR(libraries, library, lib_exists);
	unlock_read(table_lock);
	if (!lib_exists) {
		lib = load_lib(library);
		if (lib) {
			lt = (struct library_table*)malloc(sizeof(struct library_table));
			lt->libname = _strdup(library);
			lt->ref = lib;
			lock_write(table_lock);
			HASH_ADD_KEYPTR(hh, libraries, lt->libname, strlen(lt->libname), lt);
			unlock_write(table_lock);
		}
	}
	lock_read(table_lock);
	HASH_FIND_STR(libraries, library, lib_exists);
	unlock_read(table_lock);
	if (lib_exists) {
		lock_read(table_lock);
		HASH_FIND_STR(functions, function, func_exists);
		unlock_read(table_lock);
		if (!func_exists) {
			func = load_fn(lib_exists->ref, function);
			if (func) {
				fc = (struct function_table*)malloc(sizeof(struct function_table));
				fc->function = _strdup(function);
				fc->libname = _strdup(library);
				fc->ref = func;
				lock_write(table_lock);
				HASH_ADD_KEYPTR(hh, functions, fc->function, strlen(fc->function), fc);
				unlock_write(table_lock);
			}
		}
	}
	lock_read(table_lock);
	HASH_FIND_STR(functions, function, func_exists);
	unlock_read(table_lock);
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
	UDFFirstArgument(udfc, STRING_BIT | SYMBOL_BIT, &theArg);
	struct function_table* func_exists = NULL;
	lock_read(table_lock);
	HASH_FIND_STR(functions, theArg.lexemeValue->contents, func_exists);
	unlock_read(table_lock);
	if (func_exists) {
		func_exists->ref(env, udfc, out);
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
	}
	int loaded = PerfromLoading(library.lexemeValue->contents, function.lexemeValue->contents);
	if (loaded > 0) {
		DefineFuncIfRequired(env, udfc, out, (const char*)function.lexemeValue->contents);
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
	}
	lock_write(table_lock);
	HASH_FIND_STR(functions, function.lexemeValue->contents, func_exists);
	if (func_exists) {
		HASH_FIND_STR(libraries, func_exists->libname, lib_exists);
		if (lib_exists) {
			lib_exists->ref = free_lib(lib_exists->ref);
			if (!lib_exists->ref) {
				free(lib_exists->libname);
				HASH_DEL(libraries, lib_exists);
				free(lib_exists);
				free(func_exists->libname);
				free(func_exists->function);
				HASH_DEL(functions, func_exists);
				free(func_exists);
			}
			UnDefineFuncIfRequired(env, udfc, out, (const char*)function.lexemeValue->contents);
		}
	}
	unlock_write(table_lock);
}

void LoadUserFunctions(
	Environment* env)
{	
	AddUDFError adderr = AddUDF(env, "LoadDispatch", "l", 2, 2, "s", Loader, "LoadDispatch", NULL);
	adderr = AddUDF(env, "UnLoadDispatch", "l", 2, 2, "s", UnLoader, "UnLoadDispatch", NULL);
	adderr = AddUDF(env, "Dispatch", "*", 1, UNBOUNDED, "*", Dispatcher, "Dispatch", NULL);
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
		"(defrule loader-invalid-loader-type"
		"   ?d <- (functions (loaded -3))"
		"   =>"
		"   (modify ?d "
		"          (error \"Invalid Arguments - Must be library, function as strings\") "
		"   )"
		" )");
	build_result = Build(env, ""
		"(defrule loader-invalid-loader-type"
		"   ?d <- (functions (loaded -5))"
		"   =>"
		"   (modify ?d "
		"          (error \"Function was already defined, not redefining\") "
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

	return build_result;
}


BuildError setup_dispatcher(Environment* env) {
	BuildError  build_result = 0;

	LoadUserFunctions(env);
	table_lock = create_lock();

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


