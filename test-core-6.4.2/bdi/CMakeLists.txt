add_subdirectory(uuid)
add_subdirectory(uthash)

add_executable(009_STRING_BDI 009_TemplatesBDI.c)
target_link_libraries(009_STRING_BDI clips-static uuid4-static)
add_test(009_STRING_BDI 009_STRING_BDI)
