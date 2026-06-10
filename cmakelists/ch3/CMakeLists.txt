cmake_minimum_required(VERSION 3.2)
project(static_lib_test VERSION 1.3)
# 编译复杂项目,有多个源文件以及模块时

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_FLAGS -g)
message("CMAKE_CXX_FLAGS:" ${CMAKE_CXX_FLAGS})

set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
message("PROJECT_SOURCE_DIR:" ${PROJECT_SOURCE_DIR})

# 打印信息
message("project source dir: ${PROJECT_SOURCE_DIR}")
message("project dest dir:${PROJECT_BINARY_DIR}\n")

# 根据输入文件, 生成对应的 .h 文件
configure_file(Ch3Configure.h.in Ch3Configure.h)

# TODO: option 为什么没有生效???
# 添加是否使用静态库的选项, 默认不使用
option(USE_STATIC_LIB "default use static library?" OFF)
message("USE_STATIC_LIB:${USE_STATIC_LIB}")

# add compile options
#add_compile_options(-pg)
#message("COMPILE_OPTIONS=${COMPILE_OPTIONS}")

# 表示对子文件夹中的项目进行cmake编译(子模块中包含 CMakeLists.txt)
add_subdirectory(third_party/math)
add_subdirectory( third_party/history)

# 搜索要编译的外部的源文件(收集该目录下所有的源文件到变量 ${SRC_LIST} 中)
file(GLOB SRC_LIST src/*.cpp src/*.c)
message(STATUS "SRC_LIST:" ${SRC_LIST} "\n")

# 根据 ${USE_STATIC_LIB} 选择如何编译库中的源文件
if(USE_STATIC_LIB)
    # 方法1:将所有的 MYMATH 库有关的源文件先收集起来
    aux_source_directory(
        ${PROJECT_SOURCE_DIR}/third_party/math/src
        MYMATH_SRC_LIST
    )

    message("MYMATH_SRC_LIST:" ${MYMATH_SRC_LIST})
    message(STATUS "generate static lib")
    # 编译静态库 mymath, 最终生成 libmymath.a
    add_library(mymath STATIC
        ${MYMATH_SRC_LIST}
    )
    # 方法2:在子 makefile 中收集文件, 将该模块编译成库
else()
    # 使用递归添加源文件的方式
    # file(GLOB_RECURSE SRC_LIST
    #     ${PROJECT_SOURCE_DIR}/third_party/math/src
    #    *.c
    # )
    # 添加 MyMath 库的源文件到变量 MYMATH_SRC_LIST, 一起编译
    aux_source_directory(${PROJECT_SOURCE_DIR}/third_party/math/src
        # 这里必须直接使用变量名, 而不能使用变量的值的方式
        MYMATH_SRC_LIST
    )
    message("does not generate lib MYMATH_SRC_LIST:" ${MYMATH_SRC_LIST} "\n")
# elseif()

endif()

# message("CMAKE_PROJECT_INCLUDE:" ${CMAKE_PROJECT_INCLUDE})

# message("CMAKE_PROJECT_INCLUDE:" ${CMAKE_PROJECT_INCLUDE})
# 获取所有的头文件按搜索路径
get_property(dirs DIRECTORY ${CMKAE_SOURCE_DIR} 
    PROPERTY INCLUDE_DIRECTORIES
)
message(STATUS "include dirs:" ${dirs} )
message("INCLUDE_DIRECTORIES:" ${INCLUDE_DIRECTORIES} "\n")

# 从源文件生成可执行文件
# 将源文件 SRC_LIST 和目标可执行文件链接起来
if(USE_STATIC_LIB)
    add_executable(${PROJECT_NAME}_bin main.cpp 
        ${SRC_LIST}
    )
    #链接库文件
    target_link_libraries( ${PROJECT_NAME}_bin 
        mymath
    )
else()
    add_executable(${PROJECT_NAME}_bin main.cpp 
        ${SRC_LIST}
        ${MYMATH_SRC_LIST} # 库中的源文件一起编译
    )
endif()

# 添加 ${SRC_LIST} 头文件路径
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    # 库文件
    ${PROJECT_SOURCE_DIR}/third_party/math/include
    ${PROJECT_SOURCE_DIR}/third_party/history
)

# history 都生成静态库
target_link_libraries( ${PROJECT_NAME}_bin 
    history
)

# 添加头文件路径
target_include_directories(${PROJECT_NAME}_bin
    PUBLIC 
    ${PROJECT_BINARY_DIR} # 生成的 config.h 文件路径
)


