cmake_minimum_required(VERSION 3.2)
project(test VERSION 1.7)

message(STATUS "third_party")
message("")

#add_executable(${PROJECT_NAME} test.cpp)

#message("${PROJECT_SOURCE_DIR}")
aux_source_directory(${PROJECT_SOURCE_DIR} SRC_LIST)

# 生成静态库
# 生成的 .a 文件在 root cmake 的 build/third_party 目录下面
add_library(test STATIC ${SRC_LIST})