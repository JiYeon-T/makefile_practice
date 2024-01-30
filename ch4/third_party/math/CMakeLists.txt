# cmake_minimum_required(VERSION 2.8)
project(math)
# TODO:
# 有个问题:子模块的编译文件会保存在当前文件, 而不是整个项目的 build 文件, 产生了多余的垃圾


message("")
message(STATUS "===================== math  module start ================")

# math 子模块编译成静态库
message("PROJECT_SOURCE_DIR:" ${PROJECT_SOURCE_DIR})
message("PROJECT_BINARY_DIR:" ${PROJECT_BINARY_DIR})

aux_source_directory(
    # ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}
    MATH_SRC_LIST
)

# 生成 libmath.a
add_library(math STATIC
    ${MATH_SRC_LIST}
)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}
)

message(STATUS "===================== math  module end ================")
message("")