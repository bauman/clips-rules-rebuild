#include "clips.h"

/*
 * NOT A REAL PLUGIN -- TEST FIXTURE ONLY. Do not copy this as an example.
 *
 * This exports `Cube` but deliberately returns the WRONG answer: n^3 + 1000
 * instead of n^3. It is not a "version 2" of the Cube plugin and it is not an
 * improvement on anything -- the arithmetic is intentionally incorrect.
 *
 * Its sole purpose is to make a hot update OBSERVABLE. tests/hot_update.c stages
 * the realistic bugfix rollout: it deploys THIS build first (standing in for buggy
 * code already in production), builds a rule base on top of it, then unloads and
 * deploys the real plugins/Cube build as the fix. Because the answer visibly
 * changes from 1027 to 27, the test can prove the old library was genuinely
 * released and the new bytes were genuinely read from disk. With a behaviourally
 * identical build, a "reload" that silently kept the original library mapped
 * would be indistinguishable from a real one, and the test would prove nothing.
 *
 * See plugins/Cube for the real example plugin, and plugins/IsOdd for the
 * architecture-specific one.
 *
 * (Distinct from the `cube2` target in ../Cube: that is a byte-identical copy of
 * the real plugin, used to exercise the cross-library name-collision constraint.
 * This one differs in BEHAVIOUR, which is exactly what makes it unfit for any
 * purpose other than the hot-update test.)
 */

void Cube(
	Environment* env,
	UDFContext* udfc,
	UDFValue* out)
{
	UDFValue theArg;
	/* argument 1 is the dispatch name; argument 2 is the value */
	if (!UDFNthArgument(udfc, 2, NUMBER_BITS, &theArg))
	{
		return;
	}
	if (theArg.header->type == INTEGER_TYPE)
	{
		long long v = theArg.integerValue->contents;
		out->integerValue = CreateInteger(env, (v * v * v) + 1000);   /* deliberately wrong */
	}
	else /* FLOAT */
	{
		double v = theArg.floatValue->contents;
		out->floatValue = CreateFloat(env, (v * v * v) + 1000.0);     /* deliberately wrong */
	}
}
