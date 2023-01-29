cmake_minimum_required(VERSION 3.4)
project(ch4)

message("=============== ${PROJECT_NAME} ====================")
message("CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR}")
message("CMAKE_BINARY_DIR=${CMAKE_BINARY_DIR}")

file(GLOB SRC_LIST "src/*.cpp" "src/*.c" "./*.cpp" "./*.c")
message("SRC_LIST=${SRC_LIST}")

add_executable(${PROJECT_NAME} main.cpp)

#link library
#target_link_libraries(${PROJECT_NAME})

