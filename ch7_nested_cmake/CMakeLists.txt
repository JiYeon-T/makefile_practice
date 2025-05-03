cmake_minimum_required(VERSION 3.2)
project(nested_cmake VERSION 1.7)

message(STATUS "root cmake")
message("")

# 添加子模块路径编译
add_subdirectory(${PROJECT_SOURCE_DIR}/third_party)

add_executable(${PROJECT_NAME} main.cpp)