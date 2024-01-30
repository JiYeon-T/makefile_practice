cmake_minimum_required(VERSION 3.4)
project(sub_cmake_test VERSION 4.1)
# 两个子模块, 分别编译生成静态库, 在总的 cmakelist.txt 中链接, 包含头文件


message("=============== ${PROJECT_NAME} start ====================")
message("CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR}")
message("CMAKE_BINARY_DIR=${CMAKE_BINARY_DIR}")
message("PROJECT_SOURCE_DIR:" ${PROJECT_SOURCE_DIR})
message("PROJECT_BINARY_DIR:" ${PROJECT_BINARY_DIR})

# 收集源文件
# file(GLOB SRC_LIST "src/*.cpp" "src/*.c" "./*.cpp" "./*.c")
aux_source_directory(
    ${PROJECT_SOURCE_DIR}
    # ${PROJECT_SOURCE_DIR}/src
    SRC_LIST
)
message("SRC_LIST=${SRC_LIST}")

add_executable(${PROJECT_NAME}_bin
    main.cpp 
    ${SRC_LIST}
)

# 编译子模块
add_subdirectory(${PROJECT_SOURCE_DIR}/third_party/ulog)
add_subdirectory(${PROJECT_SOURCE_DIR}/third_party/math)

# 添加子模块头文件
# 方法1. target_include_directories
target_include_directories(
    ${PROJECT_NAME}_bin
    PUBLIC
    ${PROJECT_SOURCE_DIR}/third_parth/math
    ${PROJECT_SOURCE_DIR}/third_parth/ulog
)
# 方法2. include_directories
# include_directories(
#     ${PROJECT_SOURCE_DIR}/third_parth/math
#     ${PROJECT_SOURCE_DIR}/third_parth/ulog
# )

#link library
target_link_libraries(${PROJECT_NAME}_bin
    ulog
    math
)

message("=============== ${PROJECT_NAME} end ====================")

