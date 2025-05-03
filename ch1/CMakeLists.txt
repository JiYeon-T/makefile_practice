# 设置 cmake 版本要求
cmake_minimum_required( VERSION 3.2)
# 设置项目名称以及版本号
# PROJECT_VERSION_MAJOR.PROJECT_VERSION_MINOR
project(Tutorial VERSION 3.2)
# message() 向终端打印日志:
# STATUS FATAL_ERROR, 类似于 log 等级?
# STATUS 前面会显示: --, 例如:下面打印输出为: -- PROJECT_VERSION:2.3 PROJECT_VERSION_PATCH:
# STATUS FATAL_ERROR: 会停止 cmake
message(STATUS "PROJECT_VERSION:${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR} PROJECT_VERSION_PATCH:${PROJECT_VERSION_PATCH}")
# message(FATAL_ERROR "a fatal error occur, force stop")

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
message(STATUS "c++ compiler version required:${CMAKE_CXX_STANDARD} version:${CMAKE_CXX_STANDARD_REQUIRED}")
# 功能:输出 \r\n, 可以直接用 "\n" 代替
message("")


# 添加变量:
# cmake 中的变量默认都是字符串类型,通过字符串组合的方式设置变量
# 添加编译时间, 编译者变量
set(${PROJECT_NAME}_COMPILE_DATE 20220611)
set(${PROJECT_NAME}_COMPILE_AUTH JiYeon)
message(STATUS "${PROJECT_NAME}_COMPILE_DATE:${${PROJECT_NAME}_COMPILE_DATE}")
message(STATUS "${PROJECT_NAME}_COMPILE_AUTH:${${PROJECT_NAME}_COMPILE_AUTH}\n")

# configure_file 使用:
# 通过头文件将版本号传递给源文件
# 构建时, 会在 ${PROJECT_BINARY_DIR} 目录下生成一个 TutorialConfig.h 文件
configure_file(TutorialConfig.h.in TutorialConfig.h)
# 由于配置文件将写入二进制树，需要将文件路径包含到搜索路径
#target_include_directories(${PROJECT_NAME} PUBLIC
#                           ${PROJECT_BINARY_DIR}    
#)

# TutorialConfig.h.in
# 源文件下创建 TutorialConfig.h.in 并添加以下内容，当 cmake 搜素到头文件时
# @Tutorial_VERSION_MAJOR@ 和 @Tutorial_VERSION_MINOR@ 将自动被替代
#define Tutorial_VERSION_MAJOR @Tutorial_VERSION_MAJOR
#define Turorial_VERSION_MINOR @Tutorial_VERSION_MINOR


# 打印 cmake 内置变量:
message(STATUS "cmake builtin var:")
message("PROJECT_SOURCE_DIR:${PROJECT_SOURCE_DIR}")
set(PROJECT_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)
message("PROJECT_BINARY_DIR:${PROJECT_BINARY_DIR}")
message("PROJECT_NAME:${PROJECT_NAME}")
message("CMAKE_CURRENT_SOURCE_DIR:${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)
message("CMAKE_CURRENT_BINARY_DIR:${CMAKE_CURRENT_BINARY_DIR}")
message("CMAKE_SOURCE_DIR:${CMAKE_SOURCE_DIR}")
message("CMAKE_BINARY_DIR:${CMAKE_BINARY_DIR}")
# 类似于标准库中的: __FILE__, __LINE__
message("CMAKE_CURRENT_LIST_FILE:${CMAKE_CURRENT_LIST_FILE}")
message("CMAKE_CURRENT_LIST_LINE:${CMAKE_CURRENT_LIST_LINE}")
# module
message("CMAKE_MODULE_PATH:${CMAKE_MODULE_PATH}")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
message("CMAKE_MODULE_PATH:${CMAKE_MODULE_PATH}")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)
message("EXECTUABLE_OUTPUT_PATH:${EXECUTABLE_OUTPUT_PATH}")
#library
set(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
message("LIBRARY_OUTPUT_PATH:${LIBRARY_OUTPUT_PATH}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
message("CMAKE_ARCHIVE_OUTPUT_DIRECTORY:${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
message("CMAKE_LIBRARY_OUTPUT_DIRECTORY:${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
message("CMAKE_RUNTIME_OUTPUT_DIRECTORY:${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
set(EXECUTABLE_OUT_PATH ${CMAKE_SOURCE_DIR}/build)
message("EXECUTABLE_OUT_PATH:${EXECUTABLE_OUT_PATH}\n")

# version control
message("PROJECT_VERSION_MAJOR:${PROJECT_VERSION_MAJOR}")
message("PROJECT_VERSION_MINOR:${PROJECT_VERSION_MINOR}")
message("PROJECT_VERSION_PATCH:${PROJECT_VERSION_PATCH}\n")

# 列表类型的变量, 该变量有多个值, 中间用 ; 分隔
set(test_list_var This is a test list variable)
message("test_list_var:${test_list_var}")
message("CMAKE_SYSTEM_PROCESSOR:${CMAKE_SYSTEM_PROCESSORS}\n")

# 编译选项
message("BUILD_SHARED_LIBS:${BUILD_SHARED_LIBS}")
message("CMAKE_C_FLAGS:${CMAKE_C_FLAGS}")
message("CMAKE_CXX_FLAGS:${CMAKE_CXX_FLAGS}")

# 设置编译选项
set(CMAKE_C_FLAGS -g)
set(CMAKE_CXX_FLAGS -g)
message("after CMAKE_C_FLAGS:${CMAKE_C_FLAGS}")
message("after CMAKE_CXX_FLAGS:${CMAKE_CXX_FLAGS}\n")


# add directorectory
#include_directories(
#    &{PROJECT_SOURCE_DIR}/include
#)

# 通过源文件生成可执行文件, 生成的可执行文件名称:Tutorial_bin
add_executable(${PROJECT_NAME}_bin main.cpp)

# 由于配置文件将写入二进制树，需要将文件路径包含到搜索路径
target_include_directories(${PROJECT_NAME}_bin PUBLIC
                           ${PROJECT_BINARY_DIR}
)

# 多行注释
#[[
abc
]]

# cmake --help 可以选择不同的参数 以及不同平台的编译工具
# cmake -G "Unix Makefiles" ../
# make









