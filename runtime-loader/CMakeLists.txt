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

# --- example plugins ---
# Each plugin owns its own build rules, so a plugin directory is a self-contained,
# copyable template (sources + CMakeLists). This file only decides WHICH plugins
# are included; how each one is built lives with it.
#
#   Cube  -- plain C, exports Cube + Square; also builds cube2 from the same source
#            so two distinct libraries export the same names (name-collision tests).
#   IsOdd -- assembly-backed; picks a per-(arch, toolchain) core and builds nothing
#            on architectures it has no core for.
#
# Because a plugin may decline to build, detect it afterwards with `if (TARGET x)`:
# targets are global across directories, whereas variables set in a subdirectory do
# not propagate back to this scope.
#
# Plugins must BUILD INTO THIS DIRECTORY, not their own. The tests load them at
# runtime by bare relative filename (tests/plugin_names.h -> "./libcube.so"), which
# resolves against the test's working directory -- which ctest sets to the binary
# dir of wherever add_test() was called, i.e. here. Letting each plugin build into
# its own subdirectory silently breaks every plugin-loading test on POSIX. (Windows
# masks this: the DLLs are copied next to each test exe below, via generator
# expressions that resolve the target wherever it lives.) Variables DO propagate
# down into subdirectories, so the plugins read this one.
set(RUNTIME_LOADER_PLUGIN_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}")
add_subdirectory(plugins/Cube)
add_subdirectory(plugins/CubeForTesting)
add_subdirectory(plugins/IsOdd)

# --- standalone CLI application ---
add_executable(runtime-clips app/main.c)
target_link_libraries(runtime-clips dispatcher clips)

# --- pre-1.0 packaging: shared-library version + install-tree rpath ---
# Version the shared dispatcher so it carries a SONAME (libdispatcher.so.1 on ELF)
# / a compatibility+current version (on Mach-O), the basis for ABI-tracked upgrades.
# VERSION is the release version; SOVERSION is the ABI version consumers link
# against -- bump SOVERSION only on an ABI break. Set to the intended first stable
# release (1.0); adjust both if the project versions the pre-1.0 line as 0.x.
set_target_properties(dispatcher PROPERTIES VERSION 1.0.0 SOVERSION 1)

# Make the INSTALLED binaries resolve their sibling shared libs without the caller
# exporting DYLD_LIBRARY_PATH / LD_LIBRARY_PATH. The install-names are already
# @rpath/* (CMake's default), but CMake strips the build-tree rpaths on install and
# adds nothing -- so an installed runtime-clips currently finds neither
# libdispatcher nor libclips. Give the consumers a loader-relative rpath to the
# install libdir (runtime-clips is in bin/, dispatcher + libclips in lib/); relative
# (@loader_path / $ORIGIN) keeps the install relocatable across prefixes. Windows
# has no rpath (DLLs are copied beside the exe / found via PATH), so skip it there.
if (APPLE)
	set_target_properties(runtime-clips PROPERTIES INSTALL_RPATH "@loader_path/../lib")
	set_target_properties(dispatcher    PROPERTIES INSTALL_RPATH "@loader_path")
elseif (NOT WIN32)
	set_target_properties(runtime-clips PROPERTIES INSTALL_RPATH "$ORIGIN/../lib")
	set_target_properties(dispatcher    PROPERTIES INSTALL_RPATH "$ORIGIN")
endif ()

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

# setup_dispatcher must build every hardcoded construct: guards the BuildError
# propagation fix (a malformed construct surfaces as a non-zero return) AND checks
# each rule/template exists by name (catches silent same-name replacement, the F4
# bug class). No plugin needed -- never loads a library.
add_executable(test_setup_constructs tests/setup_constructs.c)
target_link_libraries(test_setup_constructs dispatcher clips)
add_test(test_setup_constructs test_setup_constructs)

# F4 race hardening: two libraries claiming the same name concurrently must yield
# exactly one winner + the other refused (-4), never a misrouted success. Needs
# cube + cube2 and threads.
add_executable(test_concurrent_name_collision tests/concurrent_name_collision.cpp)
target_link_libraries(test_concurrent_name_collision dispatcher clips Threads::Threads)
add_test(test_concurrent_name_collision test_concurrent_name_collision)
add_dependencies(test_concurrent_name_collision cube cube2)

# load-failure diagnosis: a bad library path yields -3, a real library missing the
# requested symbol yields -6 (previously both were an ambiguous -3). Needs cube for
# the real-library / missing-symbol and positive-control cases.
add_executable(test_load_failure_codes tests/load_failure_codes.c)
target_link_libraries(test_load_failure_codes dispatcher clips)
add_test(test_load_failure_codes test_load_failure_codes)
add_dependencies(test_load_failure_codes cube)

# The two-tier lifecycle: unload is a non-destructive BOUNCE (library released,
# wrapper kept, succeeds even while defrules reference the function, reload
# revives the same wrapper); cleanup is the explicit teardown that retires the
# name, and is refused until the caller removes the referencing constructs.
add_executable(test_bounce_cleanup tests/bounce_cleanup.c)
target_link_libraries(test_bounce_cleanup dispatcher clips)
add_test(test_bounce_cleanup test_bounce_cleanup)
add_dependencies(test_bounce_cleanup cube)

# The payoff case: physically overwrite a plugin's library file between an unload
# and a load and prove the running rule base picks up the NEW code without any
# rule being rebuilt. Needs cube (v1) and cube_for_testing (a different implementation of
# the same exported name) to make the swap observable.
add_executable(test_hot_update tests/hot_update.c)
target_link_libraries(test_hot_update dispatcher clips)
# Unlike every other test, this one manipulates the plugin FILES (fopen/rename) as
# well as loading them. Those two resolve differently: LoadLibrary/dlopen find a
# plugin next to the executable, but fopen resolves against the CURRENT WORKING
# DIRECTORY. ctest defaults that to the binary dir of wherever add_test was called
# -- which on multi-config generators (MSBuild) is NOT where the binaries are:
# they go in a per-config subdirectory (runtime-loader/Release/). So pin the
# working directory to the executable's own directory: the same place on
# single-config generators, the per-config dir on multi-config ones.
#
# NOTE the add_test(NAME ... COMMAND ...) signature is required here -- its
# WORKING_DIRECTORY evaluates generator expressions, whereas the WORKING_DIRECTORY
# set via set_tests_properties() does NOT (it would be written to
# CTestTestfile.cmake literally).
add_test(NAME test_hot_update
	COMMAND test_hot_update
	WORKING_DIRECTORY "$<TARGET_FILE_DIR:test_hot_update>")
add_dependencies(test_hot_update cube cube_for_testing)
if (MSVC)
	# fopen/rename are the point of this test; MSVC's _s variants are not portable.
	target_compile_definitions(test_hot_update PRIVATE _CRT_SECURE_NO_WARNINGS)
endif ()

# End-to-end test of the assembly-backed IsOdd plugin -- only where that plugin has
# an assembly core for this architecture (see plugins/IsOdd/CMakeLists.txt).
if (TARGET isodd)
	add_executable(test_isodd tests/isodd.c)
	target_link_libraries(test_isodd dispatcher clips)
	add_test(test_isodd test_isodd)
	add_dependencies(test_isodd isodd)
endif ()

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
	add_custom_command(TARGET test_setup_constructs POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:clips> $<TARGET_FILE_DIR:test_setup_constructs>)
	add_custom_command(TARGET test_concurrent_name_collision POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:clips> $<TARGET_FILE_DIR:test_concurrent_name_collision>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:cube>  $<TARGET_FILE_DIR:test_concurrent_name_collision>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:cube2> $<TARGET_FILE_DIR:test_concurrent_name_collision>)
	add_custom_command(TARGET test_load_failure_codes POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:clips> $<TARGET_FILE_DIR:test_load_failure_codes>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:cube>  $<TARGET_FILE_DIR:test_load_failure_codes>)
	add_custom_command(TARGET test_bounce_cleanup POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:clips> $<TARGET_FILE_DIR:test_bounce_cleanup>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:cube>  $<TARGET_FILE_DIR:test_bounce_cleanup>)
	add_custom_command(TARGET test_hot_update POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:clips>   $<TARGET_FILE_DIR:test_hot_update>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:cube>    $<TARGET_FILE_DIR:test_hot_update>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:cube_for_testing> $<TARGET_FILE_DIR:test_hot_update>)
	# test_isodd exists only where the IsOdd plugin has an assembly core for this
	# architecture; it LoadLibrary's isodd.dll at runtime, so copy that too.
	if (TARGET isodd)
		add_custom_command(TARGET test_isodd POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:clips> $<TARGET_FILE_DIR:test_isodd>
			COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:isodd> $<TARGET_FILE_DIR:test_isodd>)
	endif ()
	add_custom_command(TARGET runtime-clips POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:clips> $<TARGET_FILE_DIR:runtime-clips>)
endif ()

# --- install the first-class app + library ---
install(TARGETS runtime-clips DESTINATION bin)
install(TARGETS dispatcher DESTINATION lib)
install(TARGETS dispatcher-static DESTINATION lib/static)
install(FILES include/dispatcher.h include/loader.h include/locker.h
	DESTINATION include/runtime-loader)
