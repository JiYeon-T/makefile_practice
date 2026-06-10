
# 本文来源：码农网
# 本文链接：https://www.codercto.com/a/81311.html

cmake_minimum_required(VERSION 3.4.1)
project(cmake_base_test)

# 添加一个库, 根据 native-lib.cpp 生成一个 native-lib 动态库
# add_library(
#     native-lib
#     SHARED
#     native-lib.cpp
# )

# 查找系统库:
#这里查找的是系统日志库默认会到 skd/ndk 路径下面去找比如：sdk\ndk-bundle\platforms\android-28\arch-arm\usr\lib
# find_library(
#     log-lib
#     log
# )

# 设置依赖的库, 第一个参数必须是依赖的模块, 顺序不能改
# target_link_libraries(
#     native-lib
#     ${log-lib}
# )

# 《cmake 基础语法》:
# 1.CMake源文件
# CMake源文件包含命令、注释、空格和换行;
# 已CMakeLists.txt命名或者以.cmake为扩展名;
# 可以通过add_subdirectory()命令把子目录的CMake源文件添加进来;
# CMake源文件中所有有效的语句都是命令，可以是内置命令或者自定义的函数或宏命令;

# 2. CMake变量
# cmake 中所有的变量都是 string 类型, 可以使用 set() 和 unset() 来声明或者移除一个变量
# 变量的引用使用 ${val}, (变量名是大小写敏感的)
message("\n\n\n===== cmake test begin =====")
# set(name 123)
# message("name:" ${name})
# unset(name)
# message("name:" ${name})

# 3. CMake列表
# 列表也是字符串,但是可以有多个值:
# set(name_list xxx.c yyy.cpp zzz.h ooo.hpp ppp.java)
# message("name_list:" ${name_list})

# 4.Cmake操作符
# 类型	名称
# 一元	EXIST,COMMAND,DEFINED
# 二元	EQUAL,LESS,LESS_EQUAL,GREATER,GREATER_EQUAL,STREQUAL,STRLESS,STRLESS_EQUAL,STRGREATER,STRGREATER_EQUAL,VERSION_EQUAL,VERSION_GREATER,VERSION_GREATER_EQUAL,MATCHES
# 逻辑	NOT,AND,OR
# 这些操作符都是大小写敏感的。优先级带括号的>一元>二元>逻辑

# 布尔常量值
# 类型	值
# true	1,ON,YES,TRUE,Y,非0的值
# false	0,OFF,FALSE,N,IGNORE,NOTFOUUND,空字符串，以-NOTFOUND结尾的字符串
# 5.条件命令
# set(if_tab OFF)
# set(elseif_tab ON)
# if(${if_tab})
#     message("if")
# elseif(${elseif_tab})
#     message("elseif")
# else()
#     message("else")
# endif()

#6.循环命令
# while(表达式) 
# endwhile(表达式) 
# break()可以跳出整个循环。
# continue()可以跳出当前循环。
# set(val_a "")
# while(NOT val_a STREQUAL "XXX")
#     set(val_a "${val_a}XXX")
#     message("val_a:" ${val_a})
#     # break()
# endwhile()

# 7.循环遍历
# 第一种：foreach(循环变量 参数1 参数2…)
# endforeach(循环变量)。
# break()可以跳出整个循环。
# continue()可以跳出当前循环


# TODO:
# https://www.codercto.com/a/81311.html
















message("===== cmake test end =====\n\n\n")


