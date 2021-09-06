add_definitions("-DBLOAD_AND_BSAVE")
add_definitions("-DDEFRULE_CONSTRUCT")
add_definitions("-DDEFFACTS_CONSTRUCT")
add_definitions("-DDEFTEMPLATE_CONSTRUCT")


INCLUDE_DIRECTORIES(../core-6.40/)




add_executable(001_Env_and_assert  001_Env_and_assert.c)
target_link_libraries(001_Env_and_assert clips-static )
add_test(001_Env_and_assert 001_Env_and_assert)

# test 002 includes interactive terminal and omitted from automated tests
#add_executable(002_interactive  002_interactive.c)
#target_link_libraries(002_interactive clips-static )
#add_test(002_interactive 002_interactive)

add_executable(003_AssertFact  003_AssertFact.c)
target_link_libraries(003_AssertFact clips-static )
add_test(003_AssertFact 003_AssertFact)


add_executable(004_TemplateFact  004_AssertFactTemplate.c)
target_link_libraries(004_TemplateFact clips-static )
add_test(004_TemplateFact 004_TemplateFact)


if (WIN32)
	# tests that only work on windows

else ()
	#tests that only work on posix
endif()


