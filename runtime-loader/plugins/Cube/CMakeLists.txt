# Cube -- the simple example plugin.
#
# Exports two CLIPS UDFs (Cube, Square) from one library, which is what makes it
# useful to the regression tests: unloading one function of a multi-function
# library must not unmap it out from under its sibling (F1).
#
# `cube2` is a SECOND library built from the same source, so it exports the same
# symbol names from a different file -- exactly what the cross-library
# name-collision tests (F4) need: two genuine libraries claiming the name "Cube".
#
# Both are plain C with no architecture-specific content; see ../IsOdd for the
# assembly-backed example.

add_library(cube SHARED Cube.c)
target_link_libraries(cube clips)

add_library(cube2 SHARED Cube.c)
target_link_libraries(cube2 clips)

if (WIN32)
	set_target_properties(cube  PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
	set_target_properties(cube2 PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif ()

# Build into the runtime-loader binary dir, not this subdirectory: the tests load
# plugins by bare relative filename from their working directory (which is that
# dir). See the comment at the add_subdirectory() call in ../../CMakeLists.txt.
set_target_properties(cube cube2 PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY "${RUNTIME_LOADER_PLUGIN_OUTPUT_DIR}"
	RUNTIME_OUTPUT_DIRECTORY "${RUNTIME_LOADER_PLUGIN_OUTPUT_DIR}")
