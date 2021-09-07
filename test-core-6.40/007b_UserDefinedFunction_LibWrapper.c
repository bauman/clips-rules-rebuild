#include <dlfcn.h>
#include "clips.h"

typedef void(*Dispatched)(Environment* env,
                          UDFContext* udfc,
                          UDFValue* out);


void Dispatcher(
        Environment * env,
        UDFContext * udfc,
        UDFValue * out)
{
    /*
    * Credit: Matteo Cafasso from clipspy for original implementation for runtime
    *	This runtime dispatch system is modeled after clipspy python-function
    *	addudf will point to this router function, which can use runtime system to sort out where to actually dispatch to
    *	every custom function should route to here where the first argument is the lookup name of the actual function to call
    */


    // The first argument is the function name
    // need to maintain internal mapping of name to functions
    UDFValue theArg;
    UDFFirstArgument(udfc, STRING_BIT | SYMBOL_BIT, &theArg);

    //   This should be implemented as a switch / dict / lookup
    if (strncmp(theArg.lexemeValue->contents, "cube", 4) == 0) {
        void* so = dlopen("./libUDFRTlib007.so", RTLD_NOW);
        if (!so) {
            printf("%s\n", dlerror());
        }else {
            Dispatched Cube = (Dispatched) dlsym(so, "Cube");
            if(Cube){
                Cube(env, udfc, out);
            }
            dlclose(so);
        }
    }

}

void UserFunctions(
        Environment* env)
{
    AddUDFError adderr = AddUDF(env, "Dispatch", "*", 1, UNBOUNDED, "*", Dispatcher, "Dispatch", NULL);
}


int main(
        int argc,
        char* argv[])
{
    Environment* theEnv = NULL;
    FactBuilder* theFB = NULL;
    Deftemplate* animal = NULL;
    CLIPSValue returnValue;
    int rules_fired = 0;
    bool destroy_success = false;
    BuildError  build_result = 0;
    int new_rule_fired = -1;
    int post_run_facts = 0;
    theEnv = CreateEnvironment();
    if (theEnv) {


        build_result = Build(theEnv, ""
                                     "(deftemplate maths"
                                     "    (slot basei (type INTEGER))"
                                     "    (slot basef (type FLOAT))"
                                     "    (slot cubedf (type FLOAT))"
                                     "    (slot cubedi (type INTEGER))"
                                     ")");

        // run the cube'd clips function through the C Dispatcher
        build_result += Build(theEnv, ""
                                      "(deffunction cube ($?args)"
                                      "	(Dispatch cube (expand$ ?args)))");

        build_result += Build(theEnv, ""
                                      "(defrule dothemath"
                                      "   ?d <- (maths (basei ?bi) (basef ?bf))"
                                      "   =>"
                                      "   (modify ?d "
                                      "          (cubedf (cube ?bf)) "
                                      "          (cubedi (cube ?bi))"
                                      "   )"
                                      " )");

        Reset(theEnv);

        theFB = CreateFactBuilder(theEnv, "maths");
        FBPutSlotCLIPSFloat(theFB, "basef", CreateFloat(theEnv, 2.7));
        FBPutSlotCLIPSInteger(theFB, "basei", CreateInteger(theEnv, 2));
        FBAssert(theFB);
        FBDispose(theFB);

        rules_fired = (int)Run(theEnv, -1);

        Fact* n = GetNextFact(theEnv, NULL);
        while (n) {
            post_run_facts++;
            new_rule_fired = strncmp(n->whichDeftemplate->header.name->contents, "maths", 5); // animal must still be there
            GetSlotError gse = GetFactSlot(n, "cubedi", &returnValue);
            if (returnValue.integerValue->contents != 2 * 2 * 2) {
                new_rule_fired += 1;  // whatever, just note the error
            }
            gse = GetFactSlot(n, "cubedf", &returnValue);
            double expectedf = 2.7 * 2.7 * 2.7;
            if (returnValue.floatValue->contents - expectedf > 0.1 || returnValue.floatValue->contents - expectedf < -0.1) {
                new_rule_fired += 1;  // whatever, just note the error
            }
            n = GetNextFact(theEnv, n);
        }

        destroy_success = DestroyEnvironment(theEnv);
    }

    if (theEnv &&  /* environment works */
        build_result == 0 && /* build worked */
        rules_fired == 2 && /* should fire the stdout print and the quacking facts */
        new_rule_fired == 0 && /* this is the check that the expected fact slot is quack */
        post_run_facts == 1 && /* the rules should have removed the intermediate facts */
        destroy_success /* teardown should have reported complete without errors */) {
        return 0;
    }
    else {
        return -1;
    }
}
