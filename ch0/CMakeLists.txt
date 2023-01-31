cmake_minimum_required(VERSION 3.4.1)


# 添加一个库, 根据 native-lib.cpp 生成一个 native-lib 动态库
add_library(
    native-lib
    SHARED
    native-lib.cpp
)

# 查找系统库:
#这里查找的是系统日志库默认会到 skd/ndk 路径下面去找比如：sdk\ndk-bundle\platforms\android-28\arch-arm\usr\lib
find_library(
    log-lib
    log
)

# 设置依赖的库, 第一个参数必须是依赖的模块, 顺序不能改
target_link_libraries(
    native-lib
    ${log-lib}
)

