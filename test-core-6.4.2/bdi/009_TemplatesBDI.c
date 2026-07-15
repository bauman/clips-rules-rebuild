#include "clips.h"
#include <stdbool.h>
#include <time.h>
#include "uuid/uuid4.h"

#define PERSONA_TEMPLATE_NAME "persona"
#define SUBJECT_TEMPLATE_NAME "subject"
#define LOCATION_TEMPLATE_NAME "location"
#define CERTAINTY_TEMPLATE_NAME "certainty"
#define RELATIONSHIP_TEMPLATE_NAME "relationship"
#define SOURCE_TEMPLATE_NAME "source"
#define KNOWN_TEMPLATE_NAME "known"
#define ARGUMENT_TEMPLATE_NAME "argument"
#define CONTENT_TEMPLATE_NAME "content"
#define PRIMARY_TEMPLATE_NAME "primary"
#define PROPOSITION_TEMPLATE_NAME "proposition"
#define BELIEF_TEMPLATE_NAME "belief"
#define ID_FIELD "id"
#define NAME_FIELD "name"
#define CHECKED_FIELD "checked"
#define SEARCH_FIELD "search"
#define SEARCH_VALUE_FIND "find"



typedef enum {
    TARGET_PERSONA,  // something than can have its own beliefs
    TARGET_SUBJECT  // something which cannot have beliefs
} TargetType_t;

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


static CLIPSLexeme* find_uuid(Environment *theEnv,
                              const char *deftemplateName,
                              const char * search){
    if (!search){
        return NULL;
    }
    FactBuilder *theFB = NULL;
    Deftemplate *template = NULL;
    template = FindDeftemplate(theEnv, deftemplateName);
    if (!template){
        return NULL;
    }
    theFB = CreateFactBuilder(theEnv, deftemplateName);
    FBPutSlotCLIPSLexeme(theFB, NAME_FIELD, CreateSymbol(theEnv, search));
    FBPutSlotCLIPSLexeme(theFB, SEARCH_FIELD, CreateSymbol(theEnv, SEARCH_VALUE_FIND));
    Fact *theFact = FBAssert(theFB);
    FBDispose(theFB);
    long long int rules_fired = Run(theEnv, -1);
    CLIPSValue value = {0};

    FactSlotValue(theEnv, theFact, ID_FIELD, &value);
    Retract(theFact);  // need to retract this so future searches on it will work
    if (rules_fired <= 0){
        return NULL;
    }
    switch (value.header->type) {
        case SYMBOL_TYPE:
            //printf("%s \n", value.lexemeValue->contents);
            return value.lexemeValue;
            break;
        case STRING_TYPE:
            return value.lexemeValue;
            break;
        case INTEGER_TYPE:
            // no longer supported
            break;
        case FLOAT_TYPE:
            // not a supported format
            break;
        case FACT_ADDRESS_TYPE:
            // not a supported format
            break;
        case INSTANCE_TYPE_CODE: // If the type is INSTANCE_NAME
            // not a supported format
            break;
        default:
            break;
    }
    return NULL;
}

static inline CLIPSLexeme * create_uuid(Environment *theEnv){
    char uuidholder[UUID4_LEN] = {0};
    uuid4_generate(uuidholder);
    CLIPSLexeme *result = CreateSymbol(theEnv, uuidholder);
    return result;
}

static CLIPSLexeme * locate_or_create_uuid(
        Environment *theEnv,
        const char *deftemplateName,
        const char * search
        ){
    CLIPSLexeme *result = NULL;
    result = find_uuid(theEnv, deftemplateName, search);
    if (!result){
        result = create_uuid(theEnv);
    }
    return result;
}

static bool add_belief(Environment *theEnv,
                       const char * persona,  // who believes it
                       const char * target,   // persona target of the belief
                       const char * relation, // where is target related to persona
                       const char * location, // location where the target is
                       const char * reason,
                       TargetType_t tt){
    FactBuilder *theFB = NULL;

    CLIPSLexeme* fredID = locate_or_create_uuid(theEnv, PERSONA_TEMPLATE_NAME, persona); //CreateSymbol(theEnv, uuidholder);
    theFB = CreateFactBuilder(theEnv, PERSONA_TEMPLATE_NAME);
    FBPutSlotCLIPSLexeme(theFB, NAME_FIELD, CreateSymbol(theEnv, persona));
    FBPutSlotCLIPSLexeme(theFB, ID_FIELD, fredID);
    FBAssert(theFB);
    FBDispose(theFB);

    CLIPSLexeme* clownID = NULL;
    if (tt == TARGET_PERSONA){
       clownID = locate_or_create_uuid(theEnv, PERSONA_TEMPLATE_NAME, target); //CreateSymbol(theEnv, uuidholder);
        theFB = CreateFactBuilder(theEnv, PERSONA_TEMPLATE_NAME);
        FBPutSlotCLIPSLexeme(theFB, NAME_FIELD, CreateSymbol(theEnv, target));
        FBPutSlotCLIPSLexeme(theFB, ID_FIELD, clownID);
        FBAssert(theFB);
        FBDispose(theFB);
    } else {
        clownID = locate_or_create_uuid(theEnv, SUBJECT_TEMPLATE_NAME, target); //CreateSymbol(theEnv, uuidholder);
        theFB = CreateFactBuilder(theEnv, SUBJECT_TEMPLATE_NAME);
        FBPutSlotCLIPSLexeme(theFB, NAME_FIELD, CreateSymbol(theEnv, target));
        FBPutSlotCLIPSLexeme(theFB, ID_FIELD, clownID);
        FBAssert(theFB);
        FBDispose(theFB);
    }

    // persona allowed to unconditionally believe another persona
    CLIPSLexeme* parkID = locate_or_create_uuid(theEnv, LOCATION_TEMPLATE_NAME, location);  // CreateSymbol(theEnv, uuidholder);
    theFB = CreateFactBuilder(theEnv, LOCATION_TEMPLATE_NAME);
    if (location){
        FBPutSlotCLIPSLexeme(theFB, NAME_FIELD, CreateSymbol(theEnv, location));
    }
    FBPutSlotCLIPSLexeme(theFB, ID_FIELD, parkID);
    FBAssert(theFB);
    FBDispose(theFB);

    CLIPSLexeme* certainID = locate_or_create_uuid(theEnv, CERTAINTY_TEMPLATE_NAME, reason);  // CreateSymbol(theEnv, uuidholder);
    theFB = CreateFactBuilder(theEnv, CERTAINTY_TEMPLATE_NAME);
    FBPutSlotCLIPSLexeme(theFB, NAME_FIELD, CreateSymbol(theEnv, reason));
    FBPutSlotCLIPSLexeme(theFB, ID_FIELD, certainID);
    FBAssert(theFB);
    FBDispose(theFB);


    CLIPSLexeme* sourceID = create_uuid(theEnv);
    theFB = CreateFactBuilder(theEnv, SOURCE_TEMPLATE_NAME);
    FBPutSlotCLIPSLexeme(theFB, CERTAINTY_TEMPLATE_NAME,certainID);
    FBPutSlotCLIPSLexeme(theFB, ID_FIELD, sourceID);
    FBAssert(theFB);
    FBDispose(theFB);


    CLIPSLexeme* relationshipID = locate_or_create_uuid(theEnv, RELATIONSHIP_TEMPLATE_NAME, relation); //CreateSymbol(theEnv, uuidholder);
    theFB = CreateFactBuilder(theEnv, RELATIONSHIP_TEMPLATE_NAME);
    FBPutSlotCLIPSLexeme(theFB, NAME_FIELD, CreateSymbol(theEnv, relation));
    FBPutSlotCLIPSLexeme(theFB, ID_FIELD, relationshipID);
    FBAssert(theFB);
    FBDispose(theFB);


    // --------------------------------------------------------------
    // these 3 are tied together
    CLIPSLexeme* knownID = create_uuid(theEnv);
    CLIPSLexeme* contentID = create_uuid(theEnv);
    theFB = CreateFactBuilder(theEnv, KNOWN_TEMPLATE_NAME);
    FBPutSlotCLIPSLexeme(theFB, CONTENT_TEMPLATE_NAME, contentID);
    FBPutSlotCLIPSLexeme(theFB, SOURCE_TEMPLATE_NAME, sourceID);
    FBPutSlotCLIPSLexeme(theFB, ID_FIELD, knownID);
    FBAssert(theFB);
    FBDispose(theFB);


    CLIPSLexeme* argumentID = create_uuid(theEnv);
    theFB = CreateFactBuilder(theEnv, ARGUMENT_TEMPLATE_NAME);
    FBPutSlotCLIPSLexeme(theFB, KNOWN_TEMPLATE_NAME, knownID);
    if (tt == TARGET_PERSONA){
        FBPutSlotCLIPSLexeme(theFB, PERSONA_TEMPLATE_NAME, clownID);
    } else {
        FBPutSlotCLIPSLexeme(theFB, SUBJECT_TEMPLATE_NAME, clownID);
    }
    FBPutSlotCLIPSLexeme(theFB, LOCATION_TEMPLATE_NAME, parkID);
    FBPutSlotCLIPSLexeme(theFB, ID_FIELD, argumentID);
    FBAssert(theFB);
    FBDispose(theFB);

    theFB = CreateFactBuilder(theEnv, CONTENT_TEMPLATE_NAME);
    FBPutSlotCLIPSLexeme(theFB, RELATIONSHIP_TEMPLATE_NAME, relationshipID);
    FBPutSlotCLIPSLexeme(theFB, ARGUMENT_TEMPLATE_NAME, argumentID);
    FBPutSlotCLIPSLexeme(theFB, ID_FIELD, contentID);
    FBAssert(theFB);
    FBDispose(theFB);
    //--------------------------------------------------------------

    CLIPSLexeme* primaryID = create_uuid(theEnv);
    theFB = CreateFactBuilder(theEnv, PRIMARY_TEMPLATE_NAME);
    FBPutSlotCLIPSLexeme(theFB, KNOWN_TEMPLATE_NAME, knownID);
    FBPutSlotCLIPSLexeme(theFB, ID_FIELD, primaryID);
    FBAssert(theFB);
    FBDispose(theFB);


    CLIPSLexeme* propositionID = create_uuid(theEnv);
    theFB = CreateFactBuilder(theEnv, PROPOSITION_TEMPLATE_NAME);
    FBPutSlotCLIPSLexeme(theFB, PRIMARY_TEMPLATE_NAME, primaryID);
    FBPutSlotCLIPSLexeme(theFB, ID_FIELD, propositionID);
    FBAssert(theFB);
    FBDispose(theFB);


    CLIPSLexeme* beliefID = create_uuid(theEnv);
    theFB = CreateFactBuilder(theEnv, BELIEF_TEMPLATE_NAME);
    FBPutSlotCLIPSLexeme(theFB, PERSONA_TEMPLATE_NAME, fredID);
    FBPutSlotCLIPSLexeme(theFB, PROPOSITION_TEMPLATE_NAME, propositionID);
    FBPutSlotCLIPSInteger(theFB, CHECKED_FIELD, CreateInteger(theEnv, 0));
    FBPutSlotCLIPSLexeme(theFB, ID_FIELD, beliefID);
    FBAssert(theFB);
    FBDispose(theFB);

    return true;
}

static long long int  run_consistency_check(Environment *theEnv){
    long long int rules_fired = 0;
    FactBuilder *theFB = NULL;
    Fact *reason = NULL;
    theFB = CreateFactBuilder(theEnv, "runpurpose");
    FBPutSlotCLIPSLexeme(theFB, "reason", CreateSymbol(theEnv, "consistency"));
    reason = FBAssert(theFB);
    FBDispose(theFB);
    rules_fired = Run(theEnv, -1);
    Retract(reason);  // retract the reason for running so we can run again later
    return rules_fired;
}
static BuildError load_everything(Environment *theEnv){
    BuildError  build_result = 0;
    build_result = Build(theEnv, ""
                                 "(deftemplate belief"
                                 "    (slot id (type SYMBOL))"
                                 "    (slot persona (type SYMBOL))"
                                 "    (slot proposition (type SYMBOL))"
                                 "    (slot truth (type INTEGER))"
                                 "    (slot checked (type INTEGER))"
                                 "    (slot time (type INTEGER))"
                                 "    (slot search (type SYMBOL))"
                                 ")");
    build_result += Build(theEnv, ""
                                  "(deftemplate runpurpose"
                                  "    (slot reason (type SYMBOL))"
                                  ")");
    build_result += Build(theEnv, ""
                                  "(deftemplate intention"
                                  "    (slot id (type SYMBOL))"
                                  "    (slot persona (type SYMBOL))"
                                  "    (slot proposition (type SYMBOL))"
                                  "    (slot time (type INTEGER))"
                                  "    (slot search (type SYMBOL))"
                                  ")");
    build_result += Build(theEnv, ""
                                  "(deftemplate secondary"
                                  "    (slot id (type SYMBOL))"
                                  "    (slot perception (type SYMBOL))"
                                  "    (slot intention (type SYMBOL))"
                                  "    (slot belief (type SYMBOL))"
                                  "    (slot search (type SYMBOL))"
                                  ")");
    build_result += Build(theEnv, ""
                                  "(deftemplate primary"
                                  "    (slot id (type SYMBOL))"
                                  "    (slot known (type SYMBOL))"
                                  "    (slot behavior (type SYMBOL))"
                                  "    (slot search (type SYMBOL))"
                                  ")");
    build_result += Build(theEnv, ""
                                  "(deftemplate proposition"
                                  "    (slot id (type SYMBOL))"
                                  "    (slot primary (type SYMBOL))"
                                  "    (slot secondary (type SYMBOL))"
                                  "    (slot search (type SYMBOL))"
                                  ")");

    build_result += Build(theEnv, ""
                                  "(deftemplate source"
                                  "    (slot id (type SYMBOL))"
                                  "    (slot certainty (type SYMBOL))"
                                  "    (slot level (type INTEGER))"
                                  "    (slot time (type INTEGER))"
                                  "    (slot search (type SYMBOL))"
                                  ")");


    build_result += Build(theEnv, ""
                                  "(deftemplate content"
                                  "    (slot id (type SYMBOL))"
                                  "    (slot relationship (type SYMBOL))"
                                  "    (slot argument (type SYMBOL))"
                                  "    (slot time (type INTEGER))"
                                  "    (slot search (type SYMBOL))"
                                  ")");
    build_result += Build(theEnv, ""
                                  "(deftemplate argument"
                                  "    (slot id (type SYMBOL))"
                                  "    (slot known (type SYMBOL))"
                                  "    (slot persona (type SYMBOL))"
                                  "    (slot location (type SYMBOL))"
                                  "    (slot subject (type SYMBOL))"
                                  "    (slot search (type SYMBOL))"
                                  ")");
    build_result += Build(theEnv, ""
                                  "(deftemplate action"
                                  "    (slot id (type SYMBOL))"
                                  "    (slot activity (type SYMBOL))"
                                  "    (slot location (type SYMBOL))"
                                  "    (slot subject (type SYMBOL))"
                                  "    (slot search (type SYMBOL))"
                                  ")");
    build_result += Build(theEnv, ""
                                  "(deftemplate perception"
                                  "    (slot id (type SYMBOL))"
                                  "    (slot persona (type SYMBOL))"
                                  "    (slot proposition (type SYMBOL))"
                                  "    (slot time (type INTEGER))"
                                  "    (slot search (type SYMBOL))"
                                  ")");
    build_result += Build(theEnv, ""
                                  "(deftemplate behavior"
                                  "    (slot id (type SYMBOL))"
                                  "    (slot persona (type SYMBOL))"
                                  "    (slot action (type SYMBOL))"
                                  "    (slot time (type INTEGER))"
                                  "    (slot search (type SYMBOL))"
                                  ")");
    build_result += Build(theEnv, ""
                                  "(deftemplate behavior"
                                  "    (slot id (type SYMBOL))"
                                  "    (slot persona (type SYMBOL))"
                                  "    (slot action (type SYMBOL))"
                                  "    (slot time (type INTEGER))"
                                  "    (slot search (type SYMBOL))"
                                  ")");

    build_result += Build(theEnv, ""
                                  "(deftemplate known"
                                  "    (slot id (type SYMBOL))"
                                  "    (slot content (type SYMBOL))"
                                  "    (slot source (type SYMBOL))"
                                  "    (slot time (type INTEGER))"
                                  "    (slot search (type SYMBOL))"
                                  ")");

    build_result += Build(theEnv, ""
                                  "(deftemplate persona"
                                  "    (slot id (type SYMBOL))"
                                  "    (slot name (type SYMBOL))"
                                  "    (slot created (type INTEGER))"
                                  "    (slot search (type SYMBOL))"
                                  ")");
    build_result += Build(theEnv, ""
                                  "(deftemplate activity"
                                  "    (slot id (type SYMBOL))"
                                  "    (slot name (type STRING))"
                                  "    (slot created (type INTEGER))"
                                  "    (slot search (type SYMBOL))"
                                  ")");
    build_result += Build(theEnv, ""
                                  "(deftemplate subject"
                                  "    (slot id (type SYMBOL))"
                                  "    (slot name (type SYMBOL))"
                                  "    (slot created (type INTEGER))"
                                  "    (slot search (type SYMBOL))"
                                  ")");
    build_result += Build(theEnv, ""
                                  "(deftemplate location"
                                  "    (slot id (type SYMBOL))"
                                  "    (slot name (type SYMBOL))"
                                  "    (slot created (type INTEGER))"
                                  "    (slot search (type SYMBOL))"
                                  ")");
    build_result += Build(theEnv, ""
                                  "(deftemplate relationship"
                                  "    (slot id (type SYMBOL))"
                                  "    (slot name (type SYMBOL))"
                                  "    (slot created (type INTEGER))"
                                  "    (slot search (type SYMBOL))"
                                  ")");
    build_result += Build(theEnv, ""
                                  "(deftemplate certainty"
                                  "    (slot id (type SYMBOL))"
                                  "    (slot name (type SYMBOL) (default UNKNOWN))"
                                  "    (slot created (type INTEGER))"
                                  "    (slot search (type SYMBOL))"
                                  ")");

    build_result += Build(theEnv, "(defrule beliefchecktargetpersona"
                                  "   (runpurpose (reason consistency))"
                                  "   ?belief <- (belief (id ?bid) (persona ?pid) (proposition ?propid) (checked 0))"
                                  "   (persona (id ?pid) (name ?pname) (search nil))"
                                  "   (proposition (id ?propid) (primary ?primaryid))"
                                  "   (primary (id ?primaryid) (known ?knownid))"
                                  "   (known (id ?knownid) (content ?contentid) (source ?sourceid))"
                                  "   (content (id ?contentid) (relationship ?relid) (argument ?argumentid) )"
                                  "   (source (id ?sourceid) (certainty ?certaintyid))"
                                  "   (argument (id ?argumentid) (persona ?targetpersona) (location ?targetlocation))"
                                  "   (persona (id ?targetpersona) (name ?targetpersonaname) (search nil))"
                                  "   (location (id ?targetlocation) (name ?targetlocationname) (search nil))"
                                  "   (relationship (id ?relid) (name ?relname))"
                                  "   (certainty (id ?certaintyid) (name ?certaintyname))"
                                  "   =>"
                                  "   (modify ?belief"
                                  "      (checked 1)"
                                  "   )"
                                  "   (printout t crlf \"persona \"   ?pname  \" believes argument (persona) \"  ?targetpersonaname \" is \" ?relname \"  \" ?targetlocationname \" because \" ?certaintyname crlf)"
                                  " )");
    build_result += Build(theEnv, "(defrule beliefchecktargetsubject"
                                  "   (runpurpose (reason consistency))"
                                  "   ?belief <- (belief (id ?bid) (persona ?pid) (proposition ?propid) (checked 0))"
                                  "   (persona (id ?pid) (name ?pname) (search nil))"
                                  "   (proposition (id ?propid) (primary ?primaryid))"
                                  "   (primary (id ?primaryid) (known ?knownid))"
                                  "   (known (id ?knownid) (content ?contentid) (source ?sourceid))"
                                  "   (content (id ?contentid) (relationship ?relid) (argument ?argumentid) )"
                                  "   (source (id ?sourceid) (certainty ?certaintyid))"
                                  "   (argument (id ?argumentid) (subject ?targetsubject) (location ?targetlocation))"
                                  "   (subject (id ?targetsubject) (name ?targetsubjectname) (search nil))"
                                  "   (location (id ?targetlocation) (name ?targetlocationname) (search nil))"
                                  "   (relationship (id ?relid) (name ?relname))"
                                  "   (certainty (id ?certaintyid) (name ?certaintyname))"
                                  "   =>"
                                  "   (modify ?belief"
                                  "      (checked 1)"
                                  "   )"
                                  "   (printout t crlf \"persona \"   ?pname  \" believes argument (subject) \"  ?targetsubjectname \" is \" ?relname \"  \" ?targetlocationname \" because \" ?certaintyname crlf)"
                                  " )");
    Build(theEnv, "(defrule locate-persona"
                  "   ?p <- (persona (name ?pname&~nil) (search find))"
                  "   (persona (id ?pid) (name ?pname&~nil) (search nil))"
                  "   =>"
                  "    (modify ?p"
                  "        (id ?pid)"
                  "        (search found)"
                  "    )"
                  "   (printout t \"looking for persona uuid for \"  ?pname crlf)"
                  " )");
    Build(theEnv, "(defrule locate-location"
                  "   ?p <- (location (name ?name) (search find))"
                  "   (location (id ?id) (name ?name) (search nil))"
                  "   =>"
                  "    (modify ?p"
                  "        (id ?id)"
                  "        (search found)"
                  "    )"
                  "   (printout t \"looking for location uuid for \"  ?name crlf)"
                  " )");
    Build(theEnv, "(defrule locate-relationship"
                  "   ?p <- (relationship (name ?name&~nil) (search find))"
                  "   (relationship (id ?id) (name ?name&~nil) (search nil))"
                  "   =>"
                  "    (modify ?p"
                  "        (id ?id)"
                  "        (search found)"
                  "    )"
                  "   (printout t \"looking for relationship uuid for \"  ?name crlf)"
                  " )");
    Build(theEnv, "(defrule locate-certainty"
                  "   ?p <- (certainty (name ?name&~nil) (search find))"
                  "   (certainty (id ?id) (name ?name&~nil) (search nil))"
                  "   =>"
                  "    (modify ?p"
                  "        (id ?id)"
                  "        (search found)"
                  "    )"
                  "   (printout t \"looking for certainty uuid for \"  ?name crlf)"
                  " )");

//     Build(theEnv, ""
//                   "(defrule sending"
//                   "   ?d <- (messages (bruh ?bi))"
//                   "   =>"
//                   "   (modify ?d "
//                   "          (bruhb (StringHandler ?bi)) "
//                   "   )"
//                   " )");

    return build_result;
}

static long long int loop_facts(Environment *theEnv){
    long long int rules_fired;
    CLIPSValue returnValue;
    long long int post_run_facts=0;
    Fact* n = GetNextFact(theEnv, NULL);
    while (n) {
        post_run_facts++;
            if (strncmp(n->whichDeftemplate->header.name->contents, "belief", 6) == 0){
                PrintFact(theEnv, "stdout", n, true, false, NULL);
                printf("\n\n");
            }
//            PrintFact(theEnv, "stdout", n, true, false, NULL);
//            printf("\n\n");
        rules_fired = strncmp(n->whichDeftemplate->header.name->contents, "certain", 5); // animal must still be there
        GetSlotError gse = GetFactSlot(n, "id", &returnValue);
        if (gse){
            rules_fired = -1000;
        }
        n = GetNextFact(theEnv, n);
    }
    return post_run_facts + rules_fired;
}

int main(
	int argc,
	char* argv[])
{

    uuid4_init();

    Environment* theEnv = NULL;
	long long int rules_fired = 0;
    long long int new_rule_fired = 0;
	bool destroy_success = false;
    BuildError build_result;
	int post_run_facts = 0;
	theEnv = CreateEnvironment();
	if (theEnv) {
        build_result = load_everything(theEnv);
        if(build_result != BE_NO_ERROR){exit(1);}
        Reset(theEnv);

        add_belief(theEnv, "bro", "friendo", "within", "store", "told", TARGET_PERSONA);

        add_belief(theEnv, "bro", "ball", "within", "red_box",  "seen", TARGET_SUBJECT);
        add_belief(theEnv, "bro", "red_box", "within", "store",  "seen", TARGET_SUBJECT);
        add_belief(theEnv, "bro", "store", "within", "mall", "map", TARGET_SUBJECT);
        add_belief(theEnv, "bro", "mall", "within", "city", "map", TARGET_SUBJECT);

//        add_belief(theEnv, "sis", "bro", "implicit",NULL, "bro", TARGET_PERSONA);  // believes bro implicitly
//        add_belief(theEnv, "sis", "bird", "at", "game", "heard", TARGET_SUBJECT);
//        add_belief(theEnv, "sis", "friendo","at", "game", "heard", TARGET_SUBJECT);

        rules_fired = run_consistency_check(theEnv);
        post_run_facts = loop_facts(theEnv);


		destroy_success = DestroyEnvironment(theEnv);
	}
	if (destroy_success && rules_fired >= 1 && post_run_facts >= 1){
        return 0;
    } else {
        return 1;
    }
}