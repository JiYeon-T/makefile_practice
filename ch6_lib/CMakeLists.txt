cmake_minimum_required(VERSION 3.23)
# root CMake
project(lib_test VERSION 1.0.0)

# 添加子目录
#add_subdirectory(libtest)

#link_libraries(math_test)

# 生成可执行文件
add_executable(main main.c)

# 库链接到可执行文件
target_link_libraries(main PUBLIC math_test)
# 指定头文件搜索目录
target_include_directories(main PUBLIC libtest)

#target_link_libraries(main PUBLIC math_test)