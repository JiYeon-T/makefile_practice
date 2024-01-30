cmake_minimum_required(VERSION 3.4)
project(many_source_test VERSION 0.1)

# 编译复杂项目,有多个源文件以及模块时, 通过变量对源文件以及目标文件进行管理

# 打印信息
message("")
message("source dir:" ${CMAKE_SOURCE_DIR})
message("destination dir:" ${CMAKE_BINARY_DIR})
message("project source dir:" ${PROJECT_SOURCE_DIR})
message("")

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
# 发现一个目录下下的所有文件, 将其保存在变量 SRC_LIST 中
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)
# 如果不是在这个 cmake 中编译生成这个库, 而是直接链接 .a 文件的话, 会报错:
#  cannot find -ltest, 这是找不到静态库??
message("found source file : ${SRC_LIST}")
message("")
# 将这些源文件编译生成一个静态库, 生成 libtest.a(libtest.lib)
# add_library(test STATIC ${SRC_LIST})
# 生成 libtest.so(libtest.dll)
#add_library(test SHARED ${SRC_LIST})
# (3)通过 file(GLOB) 函数将所有的源文件进行收集
#file(GLOB SRC_LIST "src/*.cpp" "src/*.c")
#message("found SRC_LIST:" ${SRC_LIST})
#message("")
#add_library(TEST STATIC ${SRC_LIST})


# 直接将所有的源文件放在一起生成可执行文件生成可执行文件
add_executable(${PROJECT_NAME}_bin main.cpp ${SRC_LIST})

# 生成可执行文件
# add_executable(${PROJECT_NAME} main.cpp})
# 然后将可执行文件和之前编译生成的库进行链接
# target_link_libraries( ${PROJECT_NAME} test)
# 不在 root CMakeLists 中生成 .a 文件，通过第三方获取 .a 的方法
#target_link_libraries(${PROJECt_NAME} -ltest)

# 使用 Linux 类的编译选项, 所以生成 .a 以及 .so 文件
# cmake -G "Unix Makefiles" ../ 
# make

