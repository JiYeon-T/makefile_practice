cmake_minimum_required(VERSION 3.2)
project(MATH VERSION 1.0)

# 生成 libhistory.a 静态库

# set(CMAKE_CXX_FLAGS -g -Wall std=c++11)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_FLAGS -g)
# set(LIBRARY_OUTPUT_DIRECTORY $(CMAKE_BINARY_DIR))

# TODO:设置动态库输出路径没有生效???
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY $(CMAKE_BINARY_DIR))

message(STATUS "===== compile history Modules =====")
message(STATUS "history lib source path:" ${PROJECT_SOURCE_DIR})
# message("CMAKE_SOURCE_DIR:" ${CMAKE_SOURCE_DIR}) # ch3
# message("PROJECT_SOURCE_DIR:" ${PROJECT_SOURCE_DIR}) # thiry_party/history, 因为 history 也是一个 cmake 项目
message("CMAKE_BINARY_DIR:" ${CMAKE_BINARY_DIR})
message("PROJECT_BINARY_DIR:" ${PROJECT_BINARY_DIR}) # thiry_party/history, 因为 history 也是一个 cmake 项目


aux_source_directory( ${PROJECT_SOURCE_DIR}
    SRC_LIST
)

message("SRC_LIST:" ${SRC_LIST})

add_library(history STATIC ${SRC_LIST})
# TODO:
# add_library(history SHARED ${SRC_LIST})

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/include
)

# TODO:为什么这两个都是 NULL???
# 头文件路径还是要在总的 cmakelistx.txt 中添加
message("INCLUDE_DIRECTORIES:" ${INCLUDE_DIRECTORIES} "\n")
message("CMAKE_PROJECT_INCLUDE:" ${CMAKE_PROJECT_INCLUDE})

message("Use history module's CMakeLists.txt\n")
