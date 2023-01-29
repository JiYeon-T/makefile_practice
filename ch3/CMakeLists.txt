cmake_minimum_required(VERSION 3.2)
project(ch3 VERSION 1.3)
# 编译复杂项目,有多个源文件以及模块时

# 打印信息
#message("sourcedir:" ${CMAKE_SOURCE_DIR})
#message("destination:" ${CMAKE_BINARY_DIR})
#message("")

configure_file(ch3Configure.h.in ch3Configure.h)

# 设置是否使用静态库的选项
option(USE_STATIC_LIB "default use static library" OFF)
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

# 搜索要编译的源文件
file(GLOB SRC_LIST src/*.cpp src/*.c)
#message("SRC_LIST:" ${SRC_LIST})

if(USE_STATIC_LIB)
# 添加静态库

#链接库文件
#target_link_libraries( ${PROJECT_NAME} MYMATH)
else()
# 使用递归添加源文件的方式
#file(GLOB_RECURSE SRC_LIST
    #${PROJECT_SOURCE_DIR}/third_party/math/src
#    *.c
#)
# 添加指定目录下的源文件 到变量 SRC_LIST
aux_source_directory(${PROJECT_SOURCE_DIR}/third_party/math/src
    # 这里必须直接使用变量名, 而不能使用变量的值的方式
    SRC_LIST
)
# 添加头文件搜索路径
#message("PROJECT_SOURCE_DIR:${PROJECT_SOURCE_DIR}")
include_directories(
    ${PROJECT_SOURCE_DIR}/third_party/math/include
)
#elseif()
endif()

message("SRC_LIST:${SRC_LIST}")
message("CMAKE_PROJECT_INCLUDE:${CMAKE_PROJECT_INCLUDE}")
# 获取所有的头文件按搜索路径
get_property(dirs DIRECTORY ${CMKAE_SOURCE_DIR} 
    PROPERTY INCLUDE_DIRECTORIES
)
message("dirs:${dirs}")
message("INCLUDE_DIRECTORIES:${INCLUDE_DIRECTORIES}")
# 从源文件生成可执行文件
# 将源文件 SRC_LIST 和目标可执行文件链接起来
add_executable(${PROJECT_NAME} main.cpp ${SRC_LIST}) 



# 链接头文件
target_include_directories(${PROJECT_NAME} PUBLIC 
    ${PROJECT_BINARY_DIR}
)