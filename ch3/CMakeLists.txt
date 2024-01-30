cmake_minimum_required(VERSION 3.2)
project(static_lib_test VERSION 1.3)
# 编译复杂项目,有多个源文件以及模块时

# 打印信息
message("project source dir:" ${PROJECT_SOURCE_DIR})
message("project dest dir:" ${PROJECT_BINARY_DIR})
message("")

# 根据输入文件, 生成对应的 .h 文件
configure_file(Ch3Configure.h.in Ch3Configure.h)

# 设置是否使用静态库的选项, 默认不使用
option(USE_STATIC_LIB "default use static library?" OFF)
message("USE_STATIC_LIB:${USE_STATIC_LIB}")


# 添加文件路径
include_directories(
    #${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include
)

# add compile options
#add_compile_options(-pg)
#message("COMPILE_OPTIONS=${COMPILE_OPTIONS}")

# 表示对子文件夹项目进行cmake编译
add_subdirectory(third_party/math)

# 搜索要编译的外部的源文件
file(GLOB SRC_LIST src/*.cpp src/*.c)
message("SRC_LIST:" ${SRC_LIST})
message("")


# 根据 ${USE_STATIC_LIB} 选择如何编译库中的源文件
if(USE_STATIC_LIB)
# 将所有的 MYMATH 库有关的源文件先收集起来
aux_source_directory(
    ${PROJECT_SOURCE_DIR}/third_party/math
    ${PROJECT_SOURCE_DIR}/third_party/math/src
    MYMATH_SRC_LIST
)
message("lib MYMATH_SRC_LIST:" ${MYMATH_SRC_LIST})
message("")
# 编译静态库 MyMath, 最终生成 libMyMath.a
add_library(MyMath STATIC
    ${MYMATH_SRC_LIST}
)
# 包含库的头文件目录
include_directories(
    ${PROJECT_SOURCE_DIR}/third_party/math/include
)
#链接库文件
#target_link_libraries( ${PROJECT_NAME} MYMATH)
else()
# 使用递归添加源文件的方式
#file(GLOB_RECURSE SRC_LIST
    #${PROJECT_SOURCE_DIR}/third_party/math/src
#    *.c
#)
# 添加 MyMath 库的源文件到变量 MYMATH_SRC_LIST, 一起编译
aux_source_directory(${PROJECT_SOURCE_DIR}/third_party/math/src
    # 这里必须直接使用变量名, 而不能使用变量的值的方式
    MYMATH_SRC_LIST
)
message("no lib MYMATH_SRC_LIST:" ${MYMATH_SRC_LIST})
message("")
# 添加 MyMath 头文件搜索路径
include_directories(
    ${PROJECT_SOURCE_DIR}/third_party/math/include
)
# elseif()
endif()


message("CMAKE_PROJECT_INCLUDE:${CMAKE_PROJECT_INCLUDE}")
# 获取所有的头文件按搜索路径
get_property(dirs DIRECTORY ${CMKAE_SOURCE_DIR} 
    PROPERTY INCLUDE_DIRECTORIES
)
message("dirs:${dirs}")
message("INCLUDE_DIRECTORIES:${INCLUDE_DIRECTORIES}")
# 从源文件生成可执行文件
# 将源文件 SRC_LIST 和目标可执行文件链接起来
add_executable(${PROJECT_NAME}_bin main.cpp 
    ${SRC_LIST}
    ${MYMATH_SRC_LIST}
)

# 添加头文件路径
target_include_directories(${PROJECT_NAME}_bin
    PUBLIC 
    ${PROJECT_BINARY_DIR}
)