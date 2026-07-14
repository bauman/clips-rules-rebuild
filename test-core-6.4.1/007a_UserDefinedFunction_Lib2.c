#include "clips.h"

void Square(
        Environment* env,
        UDFContext* udfc,
        UDFValue* out)
{
    UDFValue theArg;
    // under this method, the first argument is the function name,
    //		the second and on are the actual args
    // Retrieve the second argument.
    if (!UDFNthArgument(udfc, 2, NUMBER_BITS, &theArg))
    {
        return;
    }
    // Square the argument.
    if (theArg.header->type == INTEGER_TYPE)
    {
        long long integerValue = theArg.integerValue->contents;
        integerValue = integerValue * integerValue;
        out->integerValue = CreateInteger(env, integerValue);
    }
    else /* the type must be FLOAT */
    {
        double floatValue = theArg.floatValue->contents;
        floatValue = floatValue * floatValue;
        out->floatValue = CreateFloat(env, floatValue);
    }
}
