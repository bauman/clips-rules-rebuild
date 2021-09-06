#include "clips.h"
#include <stdbool.h>

int main(
	int argc,
	char* argv[])
{
	void* theEnv = NULL;
	int rules_fired = 0;
	bool destroy_success = false;
	int build_result = 0;

	theEnv = CreateEnvironment();
	if (theEnv) {
		build_result = Build(theEnv, "(defrule hello"
			"   =>"
			"  (printout t \"Hello World.\" crlf)"
			"  (printout t \"DLL Example.\" crlf)"
			"  (printout t \"Hit return to end.\" crlf)"
			" )");

		Reset(theEnv);
		rules_fired = Run(theEnv, -1);
		destroy_success = DestroyEnvironment(theEnv);
	}
	
	if (theEnv && build_result == 0 && rules_fired == 1 && destroy_success) {
		return 0;
	}
	else {
		return -1;
	}
}