#include "clips.h"
#include <stdbool.h>


void StringHandler(
	Environment * env,
	UDFContext * udfc,
	UDFValue * out)
{
	UDFValue theArg;
	// Retrieve the first argument.
	if (!UDFFirstArgument(udfc, STRING_BIT | SYMBOL_BIT, &theArg))
	{
		return;
	}
	// Fix the string the argument.
	if (theArg.header->type == STRING_TYPE)
	{
		out->lexemeValue = CreateString(env, "nailed it bruh");
	}
}

void UserFunctions(
	Environment* env)
{
	AddUDFError adderr = AddUDF(env, "StringHandler", "sy", 1, 1, "sy", StringHandler, "StringHandler", NULL);
}


int main(
	int argc,
	char* argv[])
{
	Environment* theEnv = NULL;
	FactBuilder* theFB = NULL;
	Deftemplate* persona = NULL;
	CLIPSValue returnValue;
	int rules_fired = 0;
	bool destroy_success = false;
	BuildError  build_result = 0;
	int new_rule_fired = -1;
	int post_run_facts = 0;
	theEnv = CreateEnvironment();
	if (theEnv) {

		
		build_result = Build(theEnv, ""
			"(deftemplate messages"
			"    (slot bruh (type STRING))"
			"    (slot bruhb (type STRING))"
			")");
		build_result += Build(theEnv, ""
			"(defrule sending"
			"   ?d <- (messages (bruh ?bi))"
			"   =>"
			"   (modify ?d "
			"          (bruhb (StringHandler ?bi)) "
			"   )"
			" )");

		Reset(theEnv);
		
		theFB = CreateFactBuilder(theEnv, "messages");
		FBPutSlotCLIPSLexeme(theFB, "bruh", CreateString(theEnv, "hi there"));
		FBAssert(theFB);
		FBDispose(theFB);
		
		rules_fired = (int)Run(theEnv, -1);
		
		Fact* n = GetNextFact(theEnv, NULL);
		while (n) {
			post_run_facts++;
			new_rule_fired = strncmp(n->whichDeftemplate->header.name->contents, "messages", 5); // animal must still be there
			GetSlotError gse = GetFactSlot(n, "bruhb", &returnValue);
			if(!gse){
                if (strncmp(returnValue.lexemeValue->contents, "nailed it", 9) != 0) {
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