#include "clips.h"
#include <stdbool.h>


void Cube(
	Environment * env,
	UDFContext * udfc,
	UDFValue * out)
{
	UDFValue theArg;
	// Retrieve the first argument.
	if (!UDFFirstArgument(udfc, NUMBER_BITS, &theArg))
	{
		return;
	}
	// Cube the argument.
	if (theArg.header->type == INTEGER_TYPE)
	{
		long long integerValue = theArg.integerValue->contents;
		integerValue = integerValue * integerValue * integerValue;
		out->integerValue = CreateInteger(env, integerValue);
	}
	else /* the type must be FLOAT */
	{
		double floatValue = theArg.floatValue->contents;
		floatValue = floatValue * floatValue * floatValue;
		out->floatValue = CreateFloat(env, floatValue);
	}
}

void UserFunctions(
	Environment* env)
{
	AddUDFError adderr = AddUDF(env, "cube", "ld", 1, 1, "ld", Cube, "Cube", NULL);
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
			if(!gse){
                if (returnValue.integerValue->contents != 2 * 2 * 2) {
                    new_rule_fired += 1;  // whatever, just note the error
                }
			}

			gse = GetFactSlot(n, "cubedf", &returnValue);
			if(!gse){
			    double expectedf = 2.7 * 2.7 * 2.7;
                if (returnValue.floatValue->contents - expectedf > 0.1 || returnValue.floatValue->contents - expectedf < -0.1) {
                    new_rule_fired += 1;  // whatever, just note the error
                }
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