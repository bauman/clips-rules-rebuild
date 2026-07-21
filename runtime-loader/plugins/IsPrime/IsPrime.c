#include "clips.h"

/*
 * IsPrime -- the second assembly-backed example plugin, and a more representative
 * one than IsOdd.
 *
 * Where IsOdd's core is a single masking instruction, this one is a real routine:
 * comparisons and conditional branches, a loop, a multiply, and integer division
 * with a remainder -- trial division by odd divisors up to sqrt(n). It is still
 * small enough to read in one sitting, but it exercises the things that actually
 * make hand-written assembly look like assembly, and it exposes an ABI difference
 * that a one-instruction function cannot:
 *
 *   - On AArch64 the argument and the return value share x0, and Windows agrees
 *     with POSIX, so the two AArch64 sources differ only in assembler dialect.
 *   - On x86-64 the argument arrives in RDI (System V) or RCX (Windows), and the
 *     result must come back in EAX, so those two sources differ in their actual
 *     register allocation -- not just syntax.
 *
 * See plugins/IsPrime/is_prime_aarch64.S for the algorithm in full.
 *
 * This C file is only the adapter: it unpacks the CLIPS UDF calling convention
 * into the asm routine's plain (long long) -> int signature and packs the result
 * back into a CLIPS symbol.
 *
 * Result: a CLIPS symbol, three-valued for the same reason IsOdd's is --
 *   TRUE   the argument is a prime integer
 *   FALSE  the argument is an integer that is not prime
 *   FAIL   the argument was not an integer at all
 * Folding the not-an-integer case into FALSE would make a type error
 * indistinguishable from a genuine "not prime".
 */

/* Defined in the per-(architecture, toolchain) assembly source. */
extern int is_prime_asm(long long n);

void IsPrime(
	Environment* env,
	UDFContext* udfc,
	UDFValue* out)
{
	UDFValue theArg;
	/* Under the dispatcher, argument 1 is the dispatch name; argument 2 onward
	   are the real call arguments. IsPrime takes a single integer.

	   Retrieve arg 2 PERMISSIVELY (ANY_TYPE_BITS) and check the type ourselves: a
	   restrictive mask like INTEGER_BIT would make CLIPS raise a hard [ARGACCES2]
	   error and HALT the deffunction on a non-integer, so the caller would see an
	   evaluation error rather than our FAIL symbol. */
	if (!UDFNthArgument(udfc, 2, ANY_TYPE_BITS, &theArg) || theArg.header->type != INTEGER_TYPE)
	{
		out->lexemeValue = CreateSymbol(env, "FAIL");
		return;
	}
	int prime = is_prime_asm(theArg.integerValue->contents);
	out->lexemeValue = CreateSymbol(env, prime ? "TRUE" : "FALSE");
}
