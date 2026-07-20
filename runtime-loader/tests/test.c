
#include "clips.h"
#include "dispatcher.h"
#include "run_bounded.h"


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
	SaveScope ss = LOCAL_SAVE;

	theEnv = CreateEnvironment();
	if (theEnv) {
		
		Reset(theEnv);
		build_result = setup_dispatcher(theEnv);
		build_result = setup_dispatcher(theEnv);

		if (build_result != BE_NO_ERROR) {
			return -1;
		}
		theFB = CreateFactBuilder(theEnv, "functions");
#ifdef WIN32
		FBPutSlotCLIPSLexeme(theFB, "library", CreateString(theEnv, "cube.dll"));
#elif defined(__APPLE__)
        FBPutSlotCLIPSLexeme(theFB, "library", CreateString(theEnv, "./libcube.dylib"));
#else
        FBPutSlotCLIPSLexeme(theFB, "library", CreateString(theEnv, "./libcube.so"));
#endif
		FBPutSlotCLIPSLexeme(theFB, "function", CreateString(theEnv, "Cube"));
		Fact * theFact = FBAssert(theFB);
		FBDispose(theFB);
		

		rules_fired = run_bounded(theEnv, 10, 6, "load Cube");
		Save(theEnv, "test-save-state.clp");

		build_result = Build(theEnv, ""
			"(deftemplate maths"
			"    (slot basei (type INTEGER))"
			"    (slot basef (type FLOAT))"
			"    (slot cubedf (type FLOAT))"
			"    (slot cubedi (type INTEGER))"
			"    (slot complete (type SYMBOL) (default FALSE))"
			")");

		build_result += Build(theEnv, ""
			"(defrule dothemath"
			"   ?d <- (maths (basei ?bi) (basef ?bf) (complete FALSE))"
			"   =>"
			"   (modify ?d "
			"          (cubedf (Cube ?bf)) "
			"          (cubedi (Cube ?bi))"
			"          (complete TRUE)"
			"   )"
			" )");
		
		theFB = CreateFactBuilder(theEnv, "maths");
		FBPutSlotCLIPSFloat(theFB, "basef", CreateFloat(theEnv, 2.7));
		FBPutSlotCLIPSInteger(theFB, "basei", CreateInteger(theEnv, 2));
		FBAssert(theFB);
		FBDispose(theFB);

		SaveFacts(theEnv, "test-save-facts-0.clp", ss);
		rules_fired = run_bounded(theEnv, 10, 6, "dothemath");



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
					gse = GetFactSlot(n, "complete", &returnValue);
					if (strcmp(returnValue.lexemeValue->contents, "TRUE") != 0) {
						math_rule_fired += 1;  // rule didn't set the completion marker
					}
				}
			}
			n = GetNextFact(theEnv, n);
		}
		
		FactModifier* theFM = CreateFactModifier(theEnv, theFact);
		FMPutSlotString(theFM, "action", "unload");
		FMModify(theFM);
		FMDispose(theFM);
		SaveFacts(theEnv, "test-save-facts-1.clp", ss);
		/* Unloading a function that is still in use bounces through several rules:
		   unloadlib -> unloader-unable-to-delete (which re-arms the fact for load)
		   -> loadlib -> loader-already-defined. So this one legitimately fires more
		   than a plain load; the cap is correspondingly larger but still finite. */
		int unloading_in_usetriggers_reload = run_bounded(theEnv, 12, 8, "unload-in-use triggers reload");
		if (unloading_in_usetriggers_reload < 0) { return -1; }
		SaveFacts(theEnv, "test-save-facts-2.clp", ss);
		//Bsave(theEnv, "dan.bclp");
		//Bload(theEnv, "dan.bclp");
		destroy_success = DestroyEnvironment(theEnv);
	}

	if (theEnv &&  /* environment works */
		build_result == 0 && /* build worked */
		rules_fired == 1 && /* should fire the cube rule exactly once */
		load_rule_fired == 0 && /* strncmp result (0 found the rule fire) */
		math_rule_fired == 0 && /* strncmp result (0 found the rule fire) */
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
