#include "clips.h"
#include <string.h>

#define PLUGIN_VERSION 1

void Contains(
        Environment* env,
        UDFContext* udfc,
        UDFValue* out)
{
    UDFValue criteria;
    UDFValue theArg;

    // under this method, the first argument is the function name,
    //		the second and on are the actual args
    // Retrieve the second argument.
    if (!UDFNthArgument(udfc, 3, STRING_BIT, &criteria) || !UDFNthArgument(udfc, 2, STRING_BIT, &theArg))
    {
        return;
    }
    if (theArg.header->type == STRING_TYPE)
    {
        char *result = strstr(theArg.lexemeValue->contents, criteria.lexemeValue->contents);
        if (result){
            out->integerValue = CreateInteger(env, 1);
        } else {
            out->integerValue = CreateInteger(env, 0);
        }
    }
}

int get_version(){
    return PLUGIN_VERSION;
}