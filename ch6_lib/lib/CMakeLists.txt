cmake_minimum_required(VERSION 3.23)
project(math_test)

# add source file
message("project path:${CMAKE_CURRENT_SOURCE_DIR}")
FILE(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/math_test.c)
message("SRC_LIST:${SRC_LIST}")

# add header file
set(PUBLIC_HEADERS
	${CMAKE_CURRENT_SOURCE_DIR}/include/math_test.h
)

# copy header files
file(COPY ${PUBLIC_HEADER} DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/lib")
# 
add_library(math_test STATIC ${SRC_LIST})
 