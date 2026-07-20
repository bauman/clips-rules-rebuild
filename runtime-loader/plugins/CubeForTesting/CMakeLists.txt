# CubeForTesting -- a TEST FIXTURE, not an example plugin.
#
# Exports `Cube` with a deliberately WRONG result (n^3 + 1000). It exists only so
# tests/hot_update.c can prove a hot update really happened: the test replaces the
# loaded library file with this build and checks the observed answer changes. A
# behaviourally identical build would make a genuine reload indistinguishable from
# one that silently kept the old library mapped.
#
# Do not copy this directory as a starting point -- use ../Cube (plain C) or
# ../IsOdd (architecture-specific assembly). Also distinct from the `cube2` target
# in ../Cube, which is a byte-identical copy used for the name-collision tests.

add_library(cube_for_testing SHARED CubeForTesting.c)
target_link_libraries(cube_for_testing clips)

if (WIN32)
	set_target_properties(cube_for_testing PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif ()

# Build alongside the test executables so the test can copy it by relative name
# (see the add_subdirectory() comment in ../../CMakeLists.txt).
set_target_properties(cube_for_testing PROPERTIES
	OUTPUT_NAME cubefortesting
	LIBRARY_OUTPUT_DIRECTORY "${RUNTIME_LOADER_PLUGIN_OUTPUT_DIR}"
	RUNTIME_OUTPUT_DIRECTORY "${RUNTIME_LOADER_PLUGIN_OUTPUT_DIR}")
