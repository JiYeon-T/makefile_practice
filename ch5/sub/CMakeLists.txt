cmake_minimum_required(VERSION 3.23.0)
project("sub")

message("")
message(STATUS "CMakeExpSub")

# default on
option(TEST_OPTION "test option" OFF)

if(DEFINED TEST_OPTION)
	message(STATUS "TEST_OPTION defined")
else()
	message(STATUS "TEST_OPTION un-defined")
endif()

if(TEST_OPTION)
	message(STATUS "TEST_OPTION:ON")
else()
	message(STATUS "TEST_OPTION:OFF")
endif()
