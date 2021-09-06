cmake_minimum_required(VERSION 3.3)
project(clips)


option(static-cli "statically compile CLI" OFF)
option(build-631 "build clips-6.31 and clipspy 0.3.3 version" OFF)

if (build-631)
	INCLUDE_DIRECTORIES(/usr/include/ core-6.31/ )
	LINK_DIRECTORIES(/usr/lib64/)
	add_subdirectory ("core-6.31")
else()
	INCLUDE_DIRECTORIES(/usr/include/ core-6.40/ )
	LINK_DIRECTORIES(/usr/lib64/)
	add_subdirectory ("core-6.40")
endif()


enable_testing()


if (build-631)
	# there are no 6.31 tests 
else()
	add_subdirectory ("test-core-6.40")
endif()
