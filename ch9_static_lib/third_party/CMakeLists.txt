cmake_minimum_required(VERSION 3.20)
project(opus VERSION 1.0)

# 添加 Opus 库中的源文件
# 这里的 PROJECT_SOURCE_DIR 指的是 project opus 的 cmake 所在的目录
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)

# 添加头文件搜索路径
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# 打印 INCLUDE_DIRECTORIES 
#get_property(dirs DIRECTORY ${CMAKE_SOURCE_DIR}
#    PROPERTY INCLUDE_DIRECTORIES
#)
#message("dirs:${dirs}")


message("SRC_LIST:${SRC_LIST}")
message("INCLUDE_DIRECTORIES:${INCLUDE_DIRECTORIES}")

# 生成静态库 libopus.a
add_library(${PROJECT_NAME} STATIC ${SRC_LIST} )

# 同时拷贝头文件到 root cmake 的 build 目录下，这样 root cmake 只需要添加 ${RPJECT_BINARY_DIR} 就可以实现头文件搜索了


# 移植库的时候如何改为调用自己的接口呢
# 比如 malloc -> service_malloc()
# free -> service_free()

