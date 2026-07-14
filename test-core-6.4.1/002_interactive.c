#include "clips.h"

int main(
	int argc,
	char* argv[])
{
	void* theEnv = NULL;
	theEnv = CreateEnvironment();


	int bi = Build(theEnv, "(defrule hello"
		"   =>"
		"  (printout t \"Hello World.\" crlf)"
		"  (printout t \"DLL Example.\" crlf)"
		"  (printout t \"Hit return to end.\" crlf)"
		"  (readline))");
	int r = Reset(theEnv);
	int rr = Run(theEnv, -1);
	int d = DestroyEnvironment(theEnv);

	
	int i = 0;
	i++;
	return i;
}