#include "clips.h"

/*
 * IsOdd -- an example runtime-loader plugin whose actual computation is performed
 * in hand-written assembly for the target architecture (AArch64: GNU/Clang
 * is_odd_aarch64.S on Linux/macOS, Microsoft armasm64 is_odd_arm64_msvc.asm on
 * Windows/ARM64). It is the representative case for this whole component: the
 * plugin author drops to architecture-specific code for the hot path, and the
 * runtime loader exposes it to CLIPS rules as an ordinary function -- no rebuild
 * of CLIPS itself required.
 *
 * This C file is just the adapter: it unpacks the CLIPS UDF calling convention
 * into the asm routine's plain (long long) -> int signature and packs the result
 * back into a CLIPS result. Everything interesting happens in the .S/.asm file.
 *
 * Result: a CLIPS symbol, deliberately three-valued rather than a boolean --
 *   TRUE   the argument is an odd integer
 *   FALSE  the argument is an even integer
 *   FAIL   the argument was not an integer at all
 * Collapsing the not-an-integer case into FALSE (as a boolean return would) would
 * misread a type error as "even". CLIPS booleans are themselves just the symbols
 * TRUE/FALSE, so returning a symbol directly loses nothing and adds the FAIL case.
 */

/* Defined in the per-toolchain assembly source. */
extern int is_odd_asm(long long n);

void IsOdd(
	Environment* env,
	UDFContext* udfc,
	UDFValue* out)
{
	UDFValue theArg;
	/* Under the dispatcher, argument 1 is the dispatch name; argument 2 onward are
	   the real call arguments. IsOdd takes a single integer.

	   Retrieve arg 2 PERMISSIVELY (ANY_TYPE_BITS) and check the type ourselves.
	   Passing a restrictive mask like INTEGER_BIT would make CLIPS raise a hard
	   [ARGACCES2] error and HALT the deffunction on a non-integer, so the caller
	   would see an evaluation error rather than our FAIL symbol. This is the
	   graceful-validation pattern a plugin returning FAIL wants. */
	if (!UDFNthArgument(udfc, 2, ANY_TYPE_BITS, &theArg) || theArg.header->type != INTEGER_TYPE)
	{
		out->lexemeValue = CreateSymbol(env, "FAIL");
		return;
	}
	int odd = is_odd_asm(theArg.integerValue->contents);
	out->lexemeValue = CreateSymbol(env, odd ? "TRUE" : "FALSE");
}
