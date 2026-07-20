# runtime-loader — a first-class CLIPS runtime plugin system.
#
# Promoted from test-core-6.4.2/runtime-loader. Builds:
#   * dispatcher / dispatcher-static — a reusable library (libdispatcher) that
#     implements runtime dlopen/LoadLibrary plugin loading and UDF dispatch
#     (LoadDispatch / UnLoadDispatch / Dispatch + the `functions` template/rules),
#   * cube            — an example plugin (kept named `cube`: test-core-6.4.2's
#                       Windows 007b_win test depends on this target),
#   * runtime-clips   — a standalone CLI that embeds CLIPS with the loader
#                       pre-registered (see app/main.c),
#   * testdispatch    — the regression test (CTest).
#
# Built against the in-tree core-6.4.2 (the primary published C library): links
# the `clips` shared target and includes ../core-6.4.2 for clips.h. Added by the
# top-level CMakeLists only when build-642 is ON.

INCLUDE_DIRECTORIES(../core-6.4.2/ include)

# locker.cpp relies on C++11 for the thread-safe once-init guarantees (atomics,
# std::mutex, and thread-safe local-static init). Require it explicitly rather
# than depending on the compiler's default dialect, which may be pre-C++11.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(DISPATCHER_SOURCES
	src/dispatcher.c
	src/loader.cpp
	src/locker.cpp)

# --- reusable library: shared + static ---
add_library(dispatcher SHARED ${DISPATCHER_SOURCES})
add_library(dispatcher-static STATIC ${DISPATCHER_SOURCES})
target_link_libraries(dispatcher clips)
target_link_libraries(dispatcher-static clips)

if (WIN32)
	set_target_properties(dispatcher PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
else ()
	# loader.cpp uses dlopen (dl); locker.cpp uses pthreads.
	target_link_libraries(dispatcher dl pthread)
	target_link_libraries(dispatcher-static dl pthread)
endif ()

# --- example plugin ---
add_library(cube SHARED plugins/Cube.c)
target_link_libraries(cube clips)
if (WIN32)
	set_target_properties(cube PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif ()

# A second shared library built from the same plugin source, so it exports the
# same symbols (Cube, Square) from a different file. Used by the name-collision
# test to exercise two genuine libraries claiming the same function name.
add_library(cube2 SHARED plugins/Cube.c)
target_link_libraries(cube2 clips)
if (WIN32)
	set_target_properties(cube2 PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif ()

# --- standalone CLI application ---
add_executable(runtime-clips app/main.c)
target_link_libraries(runtime-clips dispatcher clips)

# --- regression test ---
add_executable(testdispatch tests/test.c)
target_link_libraries(testdispatch dispatcher clips)
add_test(testdispatch testdispatch)
add_dependencies(testdispatch cube)  # cube is loaded at runtime (dlopen/LoadLibrary), not linked

# --- per-finding regression tests ---
# F1: unloading one function of a multi-function library must not unmap it for
#     its siblings. Needs the two-function cube plugin.
add_executable(test_multifunction_unload tests/multifunction_unload.c)
target_link_libraries(test_multifunction_unload dispatcher clips)
add_test(test_multifunction_unload test_multifunction_unload)
add_dependencies(test_multifunction_unload cube)

# F4: a function name loaded from one library is refused from another. Needs two
#     libraries (cube, cube2) that both export the name.
add_executable(test_name_collision tests/name_collision.c)
target_link_libraries(test_name_collision dispatcher clips)
add_test(test_name_collision test_name_collision)
add_dependencies(test_name_collision cube cube2)

# F2: unload is process-global; a second environment's Dispatch of a since-unloaded
#     function must fail safe (return FALSE), not crash or return garbage.
add_executable(test_cross_env_unload tests/cross_env_unload.c)
target_link_libraries(test_cross_env_unload dispatcher clips)
add_test(test_cross_env_unload test_cross_env_unload)
add_dependencies(test_cross_env_unload cube)

# F3: concurrent first-loads of the same library must load it exactly once. Hammers
#     PerformLoading from many threads and asserts one entry per library/function.
find_package(Threads REQUIRED)
add_executable(test_concurrent_load tests/concurrent_load.cpp)
target_link_libraries(test_concurrent_load dispatcher clips Threads::Threads)
add_test(test_concurrent_load test_concurrent_load)
add_dependencies(test_concurrent_load cube)

# setup_dispatcher must propagate a UDF-registration failure, not mask it. No
# plugins needed (never loads a library).
add_executable(test_udf_registration_failure tests/udf_registration_failure.c)
target_link_libraries(test_udf_registration_failure dispatcher clips)
add_test(test_udf_registration_failure test_udf_registration_failure)

# F7: unloading via an env that never loaded the function (no local deffunction)
#     must not crash on the NULL FindDeffunction result.
add_executable(test_unload_without_deffunction tests/unload_without_deffunction.c)
target_link_libraries(test_unload_without_deffunction dispatcher clips)
add_test(test_unload_without_deffunction test_unload_without_deffunction)
add_dependencies(test_unload_without_deffunction cube)

# F8: unloading a function not in the global table (never loaded, or already
#     unloaded) must set a defined result (-32), never leave `out` unset.
add_executable(test_unload_not_loaded tests/unload_not_loaded.c)
target_link_libraries(test_unload_not_loaded dispatcher clips)
add_test(test_unload_not_loaded test_unload_not_loaded)
add_dependencies(test_unload_not_loaded cube)
# the F8 failure mode is an unset UDFValue driving the rule loop forever (verified:
# with the fix reverted this test spins, it doesn't exit) -- cap it so a regression
# fails in seconds instead of hanging CI until ctest's default 1500s timeout.
set_tests_properties(test_unload_not_loaded PROPERTIES TIMEOUT 60)

if (WIN32)
	# no rpath on windows: copy clips.dll next to each exe, and the plugin DLLs
	# next to the test exes that LoadLibrary them at runtime, so they resolve.
	add_custom_command(TARGET testdispatch POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:clips> $<TARGET_FILE_DIR:testdispatch>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:cube>  $<TARGET_FILE_DIR:testdispatch>)
	add_custom_command(TARGET test_multifunction_unload POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:clips> $<TARGET_FILE_DIR:test_multifunction_unload>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:cube>  $<TARGET_FILE_DIR:test_multifunction_unload>)
	add_custom_command(TARGET test_name_collision POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:clips> $<TARGET_FILE_DIR:test_name_collision>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:cube>  $<TARGET_FILE_DIR:test_name_collision>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:cube2> $<TARGET_FILE_DIR:test_name_collision>)
	add_custom_command(TARGET test_cross_env_unload POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:clips> $<TARGET_FILE_DIR:test_cross_env_unload>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:cube>  $<TARGET_FILE_DIR:test_cross_env_unload>)
	add_custom_command(TARGET test_concurrent_load POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:clips> $<TARGET_FILE_DIR:test_concurrent_load>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:cube>  $<TARGET_FILE_DIR:test_concurrent_load>)
	add_custom_command(TARGET test_udf_registration_failure POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:clips> $<TARGET_FILE_DIR:test_udf_registration_failure>)
	add_custom_command(TARGET test_unload_without_deffunction POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:clips> $<TARGET_FILE_DIR:test_unload_without_deffunction>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:cube>  $<TARGET_FILE_DIR:test_unload_without_deffunction>)
	add_custom_command(TARGET test_unload_not_loaded POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:clips> $<TARGET_FILE_DIR:test_unload_not_loaded>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:cube>  $<TARGET_FILE_DIR:test_unload_not_loaded>)
	add_custom_command(TARGET runtime-clips POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:clips> $<TARGET_FILE_DIR:runtime-clips>)
endif ()

# --- install the first-class app + library ---
install(TARGETS runtime-clips DESTINATION bin)
install(TARGETS dispatcher DESTINATION lib)
install(TARGETS dispatcher-static DESTINATION lib/static)
install(FILES include/dispatcher.h include/loader.h include/locker.h
	DESTINATION include/runtime-loader)
