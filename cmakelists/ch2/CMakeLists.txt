cmake_minimum_required(VERSION 3.4)
project(many_source_test VERSION 0.1)

# 编译复杂项目,有多个源文件以及模块时, 通过变量对源文件以及目标文件进行管理

# 打印信息 CMAKE_SOURCE_DIR/PROJECT_SOURCE_DIR 默认是当前 CmakeLists.txt 所在目录
message(STATUS "source file dir:" ${CMAKE_SOURCE_DIR})
message(STATUS "destination file dir:" ${CMAKE_BINARY_DIR})
message("project source dir:" ${PROJECT_SOURCE_DIR} "\n")

# 添加文件路径(设置包含的路径), 用于源文件包含在其他目录中的头文件时的目录声明
include_directories(
    #${CMAKE_CURRENT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include
)

# add compile options
# add_compile_options(-pg)
# message("COMPILE_OPTIONS=${COMPILE_OPTIONS}")

# 当有多个源文件时进行编译的方法:
# (1)逐个添加源文件
# 生成 libTest.dll
# add_library(Test SHARED 
#     ${PROJECT_SOURCE_DIR}/src/test.cpp 
#     ${PROJECT_SOURCE_DIR}/src/mymath.cpp
# )

# (2)或者 aux_source_directory(directory list_variable)
# 发现一个目录下下的所有文件(.c/.cpp 文件, 其他后缀文件不搜索), 将其保存在变量 SRC_LIST 中
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)
# 如果不是在这个 cmake 中编译生成这个库, 而是直接链接 .a 文件的话, 会报错:
#  cannot find -ltest, 这是找不到静态库??
message("found source file list: ${SRC_LIST}\n")

# 将这些源文件编译生成一个静态库, 生成 libtest.a(libtest.lib)
# add_library(test STATIC ${SRC_LIST})
# 生成 libtest.so(Linux) / libtest.dll(windows)
# add_library(test SHARED ${SRC_LIST})

# (3)通过 file(GLOB) 函数将所有的源文件进行收集
#file(GLOB SRC_LIST "src/*.cpp" "src/*.c")
#message("found SRC_LIST:" ${SRC_LIST})
#add_library(TEST STATIC ${SRC_LIST})


# 直接将所有的源文件放在一起生成可执行文件生成可执行文件
# add_executable(${PROJECT_NAME}_bin main.cpp ${SRC_LIST})


# 生成可执行文件
# add_executable(${PROJECT_NAME}_bin main.cpp)
# 将可执行文件和之前编译生成静态库库 libtest.a/libtest.so 进行链接
# target_link_libraries( ${PROJECT_NAME}_bin test)
# 不在 root CMakeLists 中生成 .a 文件，通过第三方获取到的 .a 的链接方法
#target_link_libraries(${PROJECT_NAME}_bin -ltest)

# 使用 Linux 类的编译选项, 所以生成 .a 以及 .so 文件
# cmake -G "Unix Makefiles" ../ 
# make

