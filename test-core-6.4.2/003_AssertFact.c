#include "clips.h"
#include <stdbool.h>

int main(
	int argc,
	char* argv[])
{
	Environment* theEnv = NULL;
	int rules_fired = 0;
	bool destroy_success = false;
	int build_result = 0;
	int new_rule_fired = -1;
	int post_run_facts = 0;
	theEnv = CreateEnvironment();
	if (theEnv) {
		build_result = Build(theEnv, "(defrule printquack"
			"   (duck)"
			"   =>"
			"   (assert (printed))"
			"   (printout t \"Duck Says Quack.\" crlf)"
			" )");
		build_result += Build(theEnv, "(defrule assertquack"
			"   ?d <- (duck)"
			"   ?p <- (printed)"
			"   =>"
			"   (retract ?d)"
			"   (retract ?p)"
			"   (assert (quack))"
			" )");
		Reset(theEnv);
		Fact *f = AssertString(theEnv, "(duck)");
		
		rules_fired = Run(theEnv, -1);
		
		Fact* n = GetNextFact(theEnv, NULL);
		while (n) {
			post_run_facts++;
			new_rule_fired = strncmp(n->whichDeftemplate->header.name->contents, "quack", 5);
			n = GetNextFact(theEnv, n);
		}

		destroy_success = DestroyEnvironment(theEnv);
	}
	
	if (theEnv &&  /* environment works */
		build_result == 0 && /* build worked */
		rules_fired == 2 && /* should fire the stdout print and the quacking facts */
		new_rule_fired == 0 && /* this is the check that the expected fact is quack */ 
		post_run_facts == 1 && /* the rules should have removed the intermediate facts */ 
		destroy_success /* teardown should have reported complete without errors */) {
		return 0;
	}
	else {
		return -1;
	}
}