add_executable(uthash-string-example example.c)
add_executable(uthash-deep-example example2.c)
add_executable(uthash-uuid-example example_uuid.c)

target_link_libraries(uthash-uuid-example uuid4-static)
