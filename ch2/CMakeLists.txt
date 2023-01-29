cmake_minimum_required(VERSION 3.4)
project(ch2)

# 编译复杂项目,有多个源文件以及模块时, 通过变量对源文件以及目标文件进行管理

# 打印信息
message("sourcedir:" ${CMAKE_SOURCE_DIR})
message("destination:" ${CMAKE_BINARY_DIR})
message("")

# 添加文件路径(设置包含的路径)
include_directories(
    #${CMAKE_CURRENT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include
)

# add compile options
#add_compile_options(-pg)
#message("COMPILE_OPTIONS=${COMPILE_OPTIONS}")

# (1)添加库文件
#add_library(TEST SHARED ${PROJECT_SOURCE_DIR}/src/test.cpp ) # 生成 libTest.dll
# (2)或者 aux_source_directory(directory variable)
# 发现一个目录下下的所有文件, 将其保存在 变量中
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)
# 如果不是在这个 cmake 中编译生成这个库, 而是直接链接 .a 文件的话, 会报错:
#  cannot find -ltest, 这是找不到静态库??
message("found source file : ${SRC_LIST}" )
message("")
add_library(test STATIC ${SRC_LIST}) # 生成 libtest.a(libtest.lib)
#add_library(test SHARED ${SRC_LIST}) # 生成 libtest.so(libtest.dll)
# (3)或者
#file(GLOB SRC_LIST "src/*.cpp" "src/*.c")
#message("found:" ${SRC_LIST})
#message("")
#add_library(TEST STATIC ${SRC_LIST})

# 生成可执行文件
add_executable(${PROJECT_NAME} main.cpp)

# 将可执行文件和库进行链接
#target_link_libraries( ${PROJECT_NAME} test)
# 不在 root CMakeLists 中生成 .a 文件，通过第三方获取 .a 的方法
#target_link_libraries(${PROJECt_NAME} -ltest)

# 使用 Linux 类的编译选项, 所以生成 .a 以及 .so 文件
# cmake -G "Unix Makefiles" ../ 
# make

