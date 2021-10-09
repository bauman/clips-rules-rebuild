
#include "clips.h"
#include "dispatcher.h"


int see_if_it_works() {
	Environment* theEnv = NULL;
	FactBuilder* theFB = NULL;
	CLIPSValue returnValue;
	long long rules_fired = 0;
	bool destroy_success = false;
	BuildError  build_result = 0;
	int math_rule_fired = -1;
	int load_rule_fired = -1;
	int post_run_facts = 0;
	theEnv = CreateEnvironment();
	if (theEnv) {
		
		Reset(theEnv);
		build_result = setup_dispatcher(theEnv);

		theFB = CreateFactBuilder(theEnv, "functions");
		FBPutSlotCLIPSLexeme(theFB, "library", CreateString(theEnv, "cube.dll"));
		FBPutSlotCLIPSLexeme(theFB, "function", CreateString(theEnv, "Cube"));
		Fact * theFact = FBAssert(theFB);
		FBDispose(theFB);
		

		rules_fired = Run(theEnv, -1);
		Save(theEnv, "dan.clp");

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
			"          (cubedf (Cube ?bf)) "
			"          (cubedi (Cube ?bi))"
			"   )"
			" )");
		
		theFB = CreateFactBuilder(theEnv, "maths");
		FBPutSlotCLIPSFloat(theFB, "basef", CreateFloat(theEnv, 2.7));
		FBPutSlotCLIPSInteger(theFB, "basei", CreateInteger(theEnv, 2));
		FBAssert(theFB);
		FBDispose(theFB);

		rules_fired = Run(theEnv, -1);



		Fact* n = GetNextFact(theEnv, NULL);
		while (n) {
			post_run_facts++;
			if (load_rule_fired != 0) {
				load_rule_fired = strncmp(n->whichDeftemplate->header.name->contents, "functions", 9);
				if (load_rule_fired == 0) {
					GetSlotError gse = GetFactSlot(n, "loaded", &returnValue);
					if (returnValue.integerValue->contents != 1) {
						load_rule_fired = 1;
					}
				}
			}
			if (math_rule_fired != 0) {
				math_rule_fired = strncmp(n->whichDeftemplate->header.name->contents, "maths", 6);
				if (math_rule_fired == 0) {
					GetSlotError gse = GetFactSlot(n, "cubedi", &returnValue);
					if (returnValue.integerValue->contents != 2 * 2 * 2) {
						math_rule_fired += 1;  // whatever, just note the error
					}
					gse = GetFactSlot(n, "cubedf", &returnValue);
					double expectedf = 2.7 * 2.7 * 2.7;
					if (returnValue.floatValue->contents - expectedf > 0.1 || returnValue.floatValue->contents - expectedf < -0.1) {
						math_rule_fired += 1;  // whatever, just note the error
					}
				}
			}
			n = GetNextFact(theEnv, n);
		}
		
		FactModifier* theFM = CreateFactModifier(theEnv, theFact);
		FMPutSlotString(theFM, "action", "unload");
		FMModify(theFM);
		FMDispose(theFM);

		int unloading_in_usetriggers_reload = Run(theEnv, -1);
		
		//Bsave(theEnv, "dan.bclp");
		//Bload(theEnv, "dan.bclp");
		destroy_success = DestroyEnvironment(theEnv);
	}

	if (theEnv &&  /* environment works */
		build_result == 0 && /* build worked */
		rules_fired == 2 && /* should fire the stdout print and the quacking facts */
		load_rule_fired == 0 && /* this is the check that the expected fact slot is quack */
		math_rule_fired == 0 && /* this is the check that the expected fact slot is quack */
		post_run_facts == 2 && /* the rules should have removed the intermediate facts */
		destroy_success /* teardown should have reported complete without errors */) {
		return 0;
	}
	else {
		return -1;
	}
}



int main() {
	return see_if_it_works();
}
