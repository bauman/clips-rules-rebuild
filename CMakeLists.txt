cmake_minimum_required(VERSION 3.3)
project(clips)

if (WIN32)
	# windows needs this for dll/lib linking because windows
	set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}")
	set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}")
else()
	# nothing special needed for linux
endif()
INCLUDE_DIRECTORIES(/usr/include/ )
LINK_DIRECTORIES(/usr/lib64/)

option(static-cli "statically compile CLI" OFF)
option(build-631 "build clips-6.31 and clipspy 0.3.3 version" OFF)

if (build-631)
	add_subdirectory ("core-6.31")
else()
	add_subdirectory ("core-6.40")
endif()


enable_testing()


if (build-631)
	# there are no 6.31 tests
else()
	add_subdirectory ("test-core-6.40")
endif()

