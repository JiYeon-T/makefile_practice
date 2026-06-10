cmake_minimum_required(VERSION 3.20)
project(ch9 VERSION 1.9)

aux_source_directory(${PROJECT_SOURCE_DIR} SRC_LIST)
message(STATUS "\n\nSRC_LIST:" ${SRC_LIST} "\n")


# 通过源文件生成可执行文件
add_executable(${PROJECT_NAME} ${SRC_LIST})


# 编译第三方库模块, 这里面可以有很多个库
add_subdirectory(${PROJECT_SOURCE_DIR}/third_party)

# 添加静态库
target_link_libraries(${PROJECT_NAME} PUBLIC 
    opus
)

# 没有 target_link_directories, 指定要库文件所在头文件的的路径
target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_BINARY_DIR}
    ${PROJECT_SOURCE_DIR}/third_party/include
)

message("\n\nINCLUDE_DIRECTORIES:" ${INCLUDE_DIRECTORIES})
