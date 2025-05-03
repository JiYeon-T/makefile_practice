cmake_minimum_required(VERSION 3.23)
# root CMake
project(lib_test VERSION 1.0.0)

# 添加子目录
add_subdirectory(math)

#link_libraries(math_test)

# 生成可执行文件
add_executable(${PROJECT_NAME}_bin main.c)

# 库链接到可执行文件
target_link_libraries(${PROJECT_NAME}_bin PUBLIC math_test)

# 指定头文件搜索目录
target_include_directories(${PROJECT_NAME}_bin PUBLIC
    math
    math/include
)

