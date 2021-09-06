#include "clips.h"
#include <stdbool.h>

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
			"(deftemplate animal"
			"    (slot name (type STRING))"
			"    (slot says (type SYMBOL))"
			"    (slot eats (type SYMBOL))"
			"    (slot fixed (type SYMBOL) (default no))"
			")");

		build_result += Build(theEnv, "(defrule printquack"
			"   (animal (name \"duck\") (fixed no))"
			"   =>"
			"   (assert (printed))"
			"   (printout t \"Duck Says Quack.\" crlf)"
			" )");
		build_result += Build(theEnv, "(defrule assertquack"
			"   ?d <- (animal (name \"duck\"))"
			"   ?p <- (printed)"
			"   =>"
			"   (retract ?p)"
			"   (modify ?d (says quack) (fixed yes))"
			" )");
		
		Reset(theEnv);
		
		
		animal = FindDeftemplate(theEnv, "animal");  // should do a null check on this
		DeftemplateSlotNames(animal, &returnValue);


		theFB = CreateFactBuilder(theEnv, "animal");
		FBPutSlotCLIPSLexeme(theFB, "name", CreateString(theEnv, "duck"));
		FBPutSlotCLIPSLexeme(theFB, "eats", CreateSymbol(theEnv, "snacks"));
		FBAssert(theFB);
		FBDispose(theFB);
		
		rules_fired = Run(theEnv, -1);
		
		Fact* n = GetNextFact(theEnv, NULL);
		while (n) {
			post_run_facts++;
			new_rule_fired = strncmp(n->whichDeftemplate->header.name->contents, "animal", 6); // animal must still be there
			GetSlotError gse = GetFactSlot(n, "says", &returnValue);
			new_rule_fired += strncmp(returnValue.lexemeValue->contents, "quack", 5);
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