# cmake_minimum_required(VERSION 2.8)
# 子模块 VERSION is not allowed
# project(ulog VERSION 0.1)
project(ulog)

message("")
message(STATUS "===================== ulog module start ================")

# ulog 子模块编译成静态库

message("PROJECT_SOURCE_DIR:" ${PROJECT_SOURCE_DIR})
message("PROJECT_BINARY_DIR:" ${PROJECT_BINARY_DIR})

aux_source_directory(
    # ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}
    ULOG_SRC_LIST
)

# 生成 libulog.a
add_library(ulog STATIC
    ${ULOG_SRC_LIST}
)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}
)

message(STATUS "===================== ulog module end ================")
message("")