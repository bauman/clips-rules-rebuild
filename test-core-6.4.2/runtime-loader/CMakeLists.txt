INCLUDE_DIRECTORIES(../../core-6.4.2/ include)


if (WIN32)
	# tests that only work on windows
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
	
	add_library(cube SHARED plugins/Cube.c)
	target_link_libraries(cube clips)

	add_library(dispatchloader SHARED loader.cpp )
	add_library(dispatchlocker SHARED locker.cpp )

	add_library(dispatcher SHARED dispatcher.c)
	target_link_libraries(dispatcher dispatchlocker)
	target_link_libraries(dispatcher dispatchloader)
	target_link_libraries(dispatcher clips)

	add_executable(testdispatch tests/test.c)
	target_link_libraries(testdispatch clips)
	target_link_libraries(testdispatch dispatchlocker)
	target_link_libraries(testdispatch dispatchloader)
	target_link_libraries(testdispatch dispatcher)
	add_test(testdispatch testdispatch)
	add_dependencies(testdispatch cube)  # cube is loaded at runtime (LoadLibrary), not linked

	# no rpath on windows: copy clips.dll next to the test exe so testdispatch and the
	# dispatch/cube DLLs it pulls in can resolve it at load time
	add_custom_command(TARGET testdispatch POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:clips> $<TARGET_FILE_DIR:testdispatch>)

else ()
	#tests that only work on posix
	add_library(cube SHARED plugins/Cube.c)
	target_link_libraries(cube clips)

	add_library(dispatchloader SHARED loader.cpp )
	target_link_libraries(dispatchloader dl)

	add_library(dispatchlocker SHARED locker.cpp )
	target_link_libraries(dispatchlocker pthread)


	add_library(dispatcher SHARED dispatcher.c)
	target_link_libraries(dispatcher dispatchlocker)
	target_link_libraries(dispatcher dispatchloader)
	target_link_libraries(dispatcher clips)

	add_executable(testdispatch tests/test.c)
	target_link_libraries(testdispatch clips)
	target_link_libraries(testdispatch dispatchlocker)
	target_link_libraries(testdispatch dispatchloader)
	target_link_libraries(testdispatch dispatcher)
	add_test(testdispatch testdispatch)
	add_dependencies(testdispatch cube)  # cube is loaded at runtime (dlopen), not linked

endif()

