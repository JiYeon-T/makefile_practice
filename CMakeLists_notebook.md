

### CMakeList 学习笔记

TODO:
1. https://www.codercto.com/a/81311.html
2. 在这个仓库, 创建一个用于学习 shell 的分支;


cmake 是一个跨平台、开源的构建系统。它是一个集软件构建、测试、打包于一身的软件。它使用与平台和编译器独立的配置文件来对软件编译过程进行控制。



# TODO:

cmake 学习:
cmake 官方文档:
https://cmake.org/cmake/help/latest/command/add_library.html#command:add_library
https://cmake.org/cmake/help/latest/index.html#
https://cmake.org/cmake/help/latest/module/ExternalProject.html



##### 0. cmake

- 在Android Studio2.2和以上版本，构建原生库的默认 工具 是CMake。
- CMake 是一个跨平台的构建工具，可以使用简洁的语句来描述所有平台的安装(编译过程)。能够输出各种各样的makefile或者 project 文件(**也可以生成其他格式的编译脚本**)。CMake 并不直接构建出最终的软件，而是产生其他工具脚本比如: makefile，然后在依据这个工具的构建方式使用。
- CMake 是一个比 make 更高级的编译配置工具，它可以根据不同的平台，不同的编译器，生成相应的 makefile 或者 vcproj 项目，从而达到跨平台的目的。
  **Android Studio** 利用 CMake 生成的是 **ninja**。ninja 是一个小型的关注速度的构建系统。我们一般不需要关心 ninja 的脚本，只需要知道怎么配置CMake就行了。
- CMake是一个跨平台的支持产出各种不同的构建建脚本的一个工具。

##### b.cmake 源文件

- CMake 源文件包含命令、注释、空格和换行
-  CMakeLists.txt 命名或者以 .cmake 为扩展名
- 可以通过 add_subdirectory() 命令把子目录（子模块）的 CMake 源文件添加进来
- CMake源文件中所有有效的语句都是命令，可以是内置命令或者自定义的函数或宏命令。



##### 1.windows下没有生成可执行文件的解决方法:

```cmake
cmake_minimum_required(VERSION 2.8)
project(demo VERSON 1.0.0) # 设置项目名称以及软件版本号
add_executable(main main.c)
```

然后:

```shell
# 没有 makefile
cmake ..
# 删除 cmakecache.txt
# cmake --help
cmake -G "Unix Makefiles" ../ 	# 会生成 makefile,
cmake -G "Unix Makefiles" -B ./build -S ./
# 编译器选择问题
# windows 下编译，如果不显式指定 "Unix Makefiles", 很可能会选择到 VC 编译器， MSVC， 导致生成了解决方案；cmake --help 可以查看支持的编译工具
# 实在不行就修改环境变量,只保留:D\cmake\bin; D:\MinGW\bin
make
```

**还需要清理：CMakeCache.txt**

**build 最好先删除一下(cd build && rm -rf *)，然后再编译**

```shell
cmake -G "Unix Makefiles" -DTEST_OPTION=OFF ../
cmake -G "Unix Makefiles" -DTEST_OPTION=ON ../
```





##### 2. 基础语法

cmake 内置变量：

```cmake
cmake_minimum_version_required(3.5)
project(demo) # 会自动引入两个变量 PEROJECT_BINARY_DIR 和 PROJECT_SOURCE_DIR
message("This is a cmakelists test project") # 打印

# 打印一些常见 CMakeLists 内置变量(预定义变量)
message("PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}") # 源文件路径, 工程的根目录有
message("PROJECT_BINARY_DIR = ${PROJECT_BINARY_DIR}") # 输出路径，运行 cmake 命令的目录，通常是 ${PROJECT_SOURCE_DIR}/build
message(${PROJECT_NAME})
message("CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}") # 当前处理的 CMakeLists.txt 所在的路径
message("4.CMAKE_CURRRENT_BINARY_DIR = ${CMAKE_CURRRENT_BINARY_DIR}") # 当前编译生成的文件存放目录
# __FILE__, __LINE__
message("5.CMAKE_CURRENT_LIST_FILE = ${CMAKE_CURRENT_LIST_FILE}") # 当前所在文件
message("6.CMAKE_CURRENT_LIST_LINE = ${CMAKE_CURRENT_LIST_LINE}") # 当前所在的行
# 模块化编程
message("7.CMAKE_MODULE_PATH = ${CMAKE_MODULE_PATH}") # 定义自己的 cmake 模块所在的路径，SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)，然后可以用INCLUDE命令来调用自己的模块
message("8.CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
message("9.EXECUTABLE_OUTPUT_PATH = ${EXECUTABLE_OUTPUT_PATH}") # 重新定义目标二进制可执行文件的存放位置
message("10.LIBRARY_OUTPUT_PATH = ${LIBRARY_OUTPUT_PATH}") # 重新定义目标链接库文件的存放位置
message("11.PROJECT_NAME = ${PROJECT_NAME}")
message("12.PROJECT_VERSION_MAJOR = ${PROJECT_VERSION_MAJOR}")
message("13.PROJECT_VERSION_MINOR = ${PROJECT_VERSION_MINOR}")
message("14.PROJECT_VERSION_PATCH = ${PROJECT_VERSION_PATCH}")
message("15.CMAKE_SYSTEM = ${CMAKE_SYSTEM}")
message("16.CMAKE_SYSTEM_NAME = ${CMAKE_SYSTEM_NAME}")
message("17.CMAKE_SYSTEM_VERSION = ${CMAKE_SYSTEM_VERSION}")
message("18.BUILD_SHARED_LIBS = ${BUILD_SHARED_LIBS}")
message("19.CMAKE_C_FLAGS = ${CMAKE_C_FLAGS}")
message("20.CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS}")
message("21.CMAKE_SYSTEM_PROCESSOR   = ${CMAKE_SYSTEM_PROCESSOR}")
```



**设置编译类型**

```cmake
add_executable(demo demo.cpp) # 由源码生成可执行文件
add_library(common STATIC util.cpp)	# 生成静态库
add_library(common SHARED util.cpp) # 生成动态库(共享库)
```

在Linux下生成：

demo # 可执行文件

libcommon.a	 # 生成的静态库文件名

libcommon.so # 生成的动态库文件名

在windows下生成：

demo.exe

common.lib

common.dll



**指定编译需要包含的源文件**

```cmake
# 要生成的库文件名称:demo_lib
add_library(demo_lib demo.cpp test.cpp util.cpp)
```

- aux_source_directory(DIRECTORY  VARIABLE)

```cmake
# 发现目录 DIRECTORY   下所有源文件并将列表保存在变量 VARIABLE 中
aux_source_directory(. SRC_LIST) # 搜索当前目录下的所有 .cpp 文件
add_library(demo $(SRC_LIST)) # 生成静态库
```

- 自定义文件搜索规则（类似于正则表达式）

```Cmake
file(GLOB SRC_LIST "*.cpp" "protocol/*.cpp") # 搜索源文件
add_library(demo $(SRC_LIST)) # 所有源文件参与编译
# 或者
file(GLOB SRC_LIST "*.cpp")
file(GLOB SRC_PROTOCOL_LIST "protocol/*.cpp") # 添加当前目录下的文件到 SRC_LIST
add_library(demo $(SRC_LIST) $(SRC_PROTOCOL_LIST))
# 或者
file(GLOB_RECURSE SRC_LIST "*.cpp") # 递归搜索
file(GLOB SRC_PROTOCOL RELATIVE "protocol" "*.cpp") # 相对路径搜索
# 或者
aux_source_directory(. SRC_LIST) # 可以添加指定路径下的源文件到 SRC_LIST
aux_source_directory(protocol SRC_PROTOCOL_LIST)
add_library(demo $(SRC_LIST) $(SRC_PROTOCOL_LIST))
```



##### 多文件编译方法，不使用库的方式

**直接将 .c 文件与 .cpp 文件一起进行编译，编译可以通过，但是链接会提示找不到定义，这地方还需要再研究研究**

```cmake
aux_source_directory(. SRC_LIST)
add_directory(./include)
add_executable(${RPOJECt_NAME} main.cpp ${SRC_LIST}) 
# 或者 add_executable(${PROJECT_NAME} main.cpp a.cpp b.cpp c.cpp) # 直接将 .c 文件与 .cpp 文件一起进行编译，编译可以通过，但是链接会提示找不到定义，这地方还需要再研究研究
```



**查找系统指定的库文件**

find_libray(VARIABLE  NAME  PATH)

查找到指定的预编译库，并将他的路径保存在变量中，默认路径是系统包含的系统库，因此如果是NDK的公共库则只需要指定库的 name 即可。

```Cmake
find_library(LOG_LIB # 查找到的库的名字保存到变量 LOG_LIB
			log # 库的名字
)
```



**设置包含的路径**

```cmake
# 设置库头文件:
include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/include # 添加路径
	${SRC_LIST}/include
)
# 获取编译选项包含头文件路径的方法：
# 获取所有的头文件按搜索路径
get_property(dirs DIRECTORY ${CMKAE_SOURCE_DIR} 
    PROPERTY INCLUDE_DIRECTORIES
)
message("dirs:${dirs}")
# 或者直接
message("INCLUDE_DIRECTORIES:${INCLUDE_DIRECTORIES}")
```

- Linux下还可以通过下面这种方式设置包含的目录

```cmake
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I{CMAKE_CURRNET_SOURCE_DIR}")
```

设置编译选项:CMAKE_CXX_FLAGS与add_compile_options的区别？？?

---

**设置编译选项:CMAKE_CXX_FLAGS与add_compile_options的区别**

- add_compile_options()

```cmake
if(CMAKE_COMPILER_IS_GNUCXX)
	add_compile_options(-std=c++11) # 如果编译器是GCC， 则加入C++11标准， 设置GCC 以及 g++ 等其它编译器都加入C++11标准，当使用gcc 编译器的时候会报警告
	message(STATUS "optional:-std=c++11")
else()
	message("unknow compiler")
endif(CMAKE_COMPILER_IS_GNUCXX)
```

- set 系统变量 CMAKE_CXX_FLAGS

```cmake
if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}") # 直接设置 G++ 编译器的编译选项
	message(STATUS "optional:-std:c++11")
if(CMAKE_COMPILER_IS_GNUCXX)
else()
endif()
```



**设置链接库的搜索目录**

```cmake
link_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/libs
)
```

- Linux下还可以通过如下方式设置链接包含的目录

```cmake
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLSGS} -L${CMAKE_CURRENT_SOURCE_DIR}/libs")
```



**设置 target 需要链接的库(动态库、静态库)**

```cmake
target_link_libraries( demo # 要链接的目标文件
	${LOG_LIB} # 需要链接的库文件
)
```

windows：系统会根据链接库目录，搜索xxx.lib文件

Linux：会搜索 xxx.so 以及 xxx.a 文件，优先搜索 xxx.so文件

- 指定链接动态库或者静态库

```cmake
target_link_libraries(demo ${CMAKE_CURRENT_SOURCE_DIR}/libs/libface.a)
target_link_libraries(demo ${CMAKE_CURRENT_SOURCE_DIR}/libs/libface.so)
```

- 指定要链接的文件的路径

```cmake
# (1)使用 target_include_directories()
target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_BINARY_DIR}
    ${PROJECT_SOURCE_DIR}/third_party/include
)
# (2)使用 link_directories()
link_directories(demo libface.a) # 链接静态库
link_directories(demo libface.so) # 链接动态库
# (3)使用 include_directories()
include_directories(
    ${PROJECT_BINARY_DIR}
    ${PROJECT_SOURCE_DIR}/third_party/include
)
```

- 指定链接多个库

```cmake
target_link_libraries(demo
	${CMAKE_CURRENT_SOURCE_DIR}/libs/libface.a
	boost_system.a
	boost_thread
	pthread
)
```



##### 3. cmake  变量

cmake 中的变量都是 STRING 类型, 可以使用 set() 和 unset() 来设置一个变量, 或者移除一个变量;

```cmake
set(<variable> <value>… [PARENT_SCOPE])
# 设置变量 
# set(test_var abc)
# message(STATUS ${test_var})
# 删除变量
# unset(test_var)
# message(STATUS ${test_var})
# 列表也是字符串，可以把列表看成一个特殊的变量，它有多个值
# set(test_var "a;b;c;d;e;f;g")
# set(test_var a b c d e f g)
# message(STATUS "test_var: ${test_var}")
```

将变量variable设置为值<value>…，变量variable的作用域为调用set命令的函数或者当前目录，如果使用了 **PARENT_SCOPE ** 选项，**意味着该变量的作用域会传递到上一层（也就是上一层目录或者当前函数的调用者，如果是函数则传递到函数的调用者，如果是目录则传递到上一层目录），并且在当前作用域该变量不受带PARENT_SCOPE选项的set命令的影响**（如果变量之前没有定义，那么在当前作用域仍然是无定义的；如果之前有定义值，那么值和之前定义的值保持一致）。

```cmake
set(SRC_LIST main.cpp test.cpp face.cpp head.cpp util.cpp) # 设置变量
add_executable(demo ${SRC_LIST}) # 生成可执行文件
```

- set 追加设置变量的值

```cmake
# 设置变量
set(SRC_LIST main.cpp)
# SRC_LIST 变成一个列表, 在原来的基础上添加 test.cpp
set(SRC_LIST ${SRC_LIST} test.cpp)
# 编译生成可执行文件爱呢 demo_bin
add_executable(demo_bin ${SRC_LIST})
```

- list 追加或者删除变量的值

使用 list 关键字对 list 类型的变量进行管理:

```cmake
set(SRC_LIST main.cpp) # 设置变量
list(APPEND SRC_LIST test.cpp) # 追加元素
list(REMOVE_ITEM SRC_LIST main.cpp) # 删除元素 main.cpp
list(REMOVE_ITEM SRC_LIST ${REMOVE_LIST}) # 删除 SRC_LIST 中的 REMOVE_LIST 包含的所有元素
add_executable(demo ${SRC_LIST})
```



##### 3.条件控制

- if...elseif...else...endif

```cmake
if(expression)
if(not exp)
if(var1 AND var2)
if(var1 OR var2)
if(COMMAND cmd) # 如果 cmd 是命令就为真
if(EXISTS dir) # 如果目录或者文件存在为真
if(EXISTS file)
if(file1 IS_NEWER_THAN file2) # 当 file1 比 file2
if(IS_DIRECTORY dir) # 当 dir 为目录时为真
if(DEFINED var) # var 已经被定义时为真
if(var MATCHES regex)  # var 可以是字符串或者变量, 如果匹配正则表达式为真
if(${var} MATCHES regex)
if(string MATCHES regex)
```



##### 4.cmake 运算符

这些操作符都是大小写敏感的。**优先级带括号的 > 一元 > 二元 > 逻辑**

```cmake
# 一元运算符
EXIST, COMMAND, DEFINED
# 二元运算符
EQUAL, LESS, LESS_EQUAL, GREATER, GREATER_EQUAL, STREQUAL, STRLESS, STRLESS_EQUAL
STRGREATER, STRGREATER_EQUAL, VERSION_EQUAL, VERSION_GREATER, VERSION_GREATER_EQUAL, MATCHES
# 逻辑运算符
NOT, AND, OR
```

- bool 常量值

| 类型    | 值                                        |
| ----- | ---------------------------------------- |
| true  | 1,ON,YES,TRUE,Y,非0的值                     |
| false | 0,OFF,FALSE,N,IGNORE,NOTFOUUND,空字符串，以-NOTFOUND结尾的字符串 |

- 数字比较

```cmake
if(variable LESS string)
if(string LESS string)
if(variable GREATER number)
if(string GREATER number)
if(variable EQUAL number)
if(string EQUAL number)
```

- 字母表顺序比较 STRLESS

```cmake
if(variable STRLESS string) # STRLESS string
if(string STRLESS string)
if(variable STRGREATER number)
if(string STRGREATER number)
if(variable STREQUAL number)
if(string STREQUAL number)
```



##### 5. 条件命令

test1

```cmake
if(expression)
	set(var ON)
elseif()
	set(var OFF)
else
	message(WARNING "expression:${expression}")
endif()
```



test2

```cmake
if(MSVC)
	set(LINK_LIBS common)
else()
	set(boost_thread boost_log.a boost_system.a)
endif()

target_link_libraries(demo ${LINK_LIBS})

# 或者
if(UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fpermissive -g")
else()
	add_definitions(-D_SCL_SECURE_NO_WARNINGS
		D_CRT_SECURE_NO_WARNINGS
		-D_WIN32_WINNT=0x601
		-D_WINSOCK_DEPRECATED_NO_WARNINGS
	)
endif()

if(${CMAKES_BUILD_TYPE} MATCHES "debug")
	#...
else()
	...
endif()
```



- while...endwhile()

while(表达式) endwhile(表达式) 

break()可以跳出整个循环

continue()可以跳出当前循环。

```cmake
while(condition)
	...
endwhile()
```

test2:

```cmake
set(a "")
while(NOT a STREQUAL "debug")
	set(a "${a}_debug")
	message(STATUS "a=${a}")
endwhile()
```



- foreach()...endforeach()

格式 1:

foreach(循环变量 参数1 参数2…) 

endforeach(循环变量)

break()可以跳出整个循环

continue()可以跳出当前循环

```cmake
foreach(item 1 2 3 ab cd ef gh)
    message("item = ${item}")
endforeach(item)
```

格式 2:

foreach(循环变量 RANGE total) 

endforeach(循环变量)

循环范围从 0 到 total

```cmake
foreach(item RANGE 10)
	message("item = ${item}")
endforeach(item)
```

格式 3:

foreach(循环变量 RANGE start stop step) 

endforeach(循环变量)。

循环变量从 start 到 stop，每次增量为 step

```cmake
foreach(item RANGE 0 10 2)
	message("item = ${item}")
endforeach(item)
```

格式 4:

foreach(循环变量 IN LISTS 列表)

endforeach(循环变量)

```cmake
set(list_var 0 1 2 3 4 5 6 7 8 9 10)
foreach(item IN LISTS list_var)
	message("item = ${item}")
endforeach(item)
```

test2:

```cmake
foreach(loop_var RANGE start stop [step])
	...
endforeach(loop_var)
# 例如:
foreach(ix RANGE 1 10 1) # 1 - 10, step=1
	message(${ix})
endforeach()
```



##### 6. 自定义函数

自定义函数命令格式：function( 函数名称 [arg1[arg2[arg3]]]) endfunction( )

函数命令调用：name(实参列表)

ARGC：表示传入产出的个数

ARGV: 表示所有参数列表

ARGV0: 第一个参数 

ARGV1: 第二个参数 

ARGV2: 第三个参数

```cmake
function(func x y z)
	message("call function func")
	message("x = ${x}")
	message("y = ${y}")
	message("z = ${z}")
	message("ARGC = ${ARGC}")
	message("ARGV0 = ${ARGV0}, ARGV1 = ${ARGV1}, ARGV2 = ${ARGV2}")
endfunction(func)
func(1, 2, 3)
```

test2:

```cmake
# 打印函数传入的所有参数
function(test_func x y z)
	message(STATUS "ARGV list")
	foreach(item RANGE 0 ${ARGC} 1)
		message("ARGV${item} = ${ARGV${item}}")
	endforeach(item)
endfunction(test_func)
test_func(1, 2, 3)
```

##### 7. 自定义宏命令

自定义宏命令格式：macro( [arg1[arg2[arg3]]]) endfunction( )

宏命令用：name(实参列表)

计算机科学里的宏（Macro)，是一种批量批处理的称谓。一般说来，宏是一种规则或模式，或称语法替换

```cmake
macro(test_macro x y z)
	message("call macro")
	message("x = ${x}")
	message("y = ${y}")
	message("z = ${z}")
endmacro(test_macro)
test_macro(1, 2, 3)
```



##### 8. 打印信息

```cmake
message("hello")
message(${HELLO})
message(STATUS "abc") # -- abc
message(WARNING "this is a warning message") # 产生警告
message(FATAL_ERROR "this build has many error") # 会导致编译失败
```



##### 9. cmake 作用域

全局层：cache变量在整个项目范围可见，一般在 set 定义变量时，指定 CACHE 参数就能定义为 cache变量

目录层：在当前目录 CMakeLists.txt 中定义，以及在该文件包含的其他 cmake 源文件中定义的变量

函数层：在命令函数中定义的变量，属于函数作用域内的变量



##### 4.包含其它cmake文件

```cmake
include(./common.cmake) # 指定包含文件的全路径
include(def) # 在搜索路径中搜索 def.cmake文件
# 设置 include 的搜索路径
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
```



##### 5.环境变量

```cmake
# 使用环境变量
$ENV{Name}
# 写入环境变量
set(ENV{Name} value) # 注意这里没有 $ 符号
```



##### 6系统信息(CMAKE 内置变量)

```cmake
CMAKE_MAJOR_VERSION:cmake 主版本号
CMAKE_MINOR_VERSION:cmake 次版本号
CMAKE_PATCH_VERSION:cmake 补丁版本号
CMAKE_SYSTEM: 系统名称, 如:Linux-2.6.22
CMAKE_SYSTEM_NAME:如Linux
CMAKE_SYSTEM_VERSION:如:2.6.22
CMAKE_SYSTEM_PROCESSOR:处理器名称, 如:i686
UNIX:在所有的类UNIX平台下该值为TRUE, 包括 OSX 和 cygwin
WIN32:在所有的win32平台下该值为TRUE, 包括 cygwin
```

- 文件输出位置

```cmake
set(EXECUTABLE_OUT_PATH [out_path] ${CMAKE_SOURCE_DIR}/runtime) # 设置可执行文件的输出路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/runtime) # 设置可执行文件的输出路径

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/archive) # 设置默认静态库的输出文件夹
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/library) # 设置存放动态库的输出文件夹

set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/library) # 默认存放库文件的位置，如果产生的是静态库并且没有指定 CMAKE_ARCHIVE_OUTPUT_DIRECTORY 则存放在该目录下;动态库如果没有指定 CMAKE_LIBRARY_OUTPUT_DIRECTORY 则存放在该目录下;
```



##### 7.编译选项(开关选项)

- BUILD_SHARED_LIBS:主要用来控制默认的库的编译方式，如果不进行设置，add_libraries(

  ）有没有指定的情况下，会默认生成静态库。如果 set(BUILD_SHARED_LIBS ON) 则会默认生成动态库

```cmake
set(BUILD_SHARED_LIBS_ON) # 默认生成动态库
```

- CMAKE_C_FLAGS:设置C编译选项，也可以通过指令 **add_definitions()**添加；
- CMAKE_CXX_FLAGS:设置C++编译选项，可以通过 **add_definitions() **添加

```cmake
set(CMAKE_CXX_FLAGS "-Wall std=c++11")
# 或者
add_definitions(-DENABLE_DEBUG -DABC)
```



##### 8.参考具体简单项目实例

add_definitions 主要用于

```cmake
if(WINRT)
	add definitions(-DWINrT -DNO_GETENV)
	if(CMAKE_SYSteM_NAME MATCHES WindowsPhone)
		set(WINRT PHONE TRUE)
		add_definitions(-DWINRT_PHONE)
	elseif(CMAKE_SYSTEM_NAME MATCHES WindowsStore)
		set(WINRT STORE TRUE)
		add_definitions(-DWINRT_STORE)
	endif()
endif()
```

编译时：

```shell
cmake ../opencv-3.4.1 -DWITH_GTK_2_X=ON -DCMAKE_INSTALL_PREFIX=/usr/local -DWITH_cUBAS=1 -DWITH_OPENMP=ON
```

**其中 -D 后面的参数就是控制程序流向**

**（1）更改别人代码时使用，即不对源码进行破坏，又可以添加自己的功能。之前都是在程序中通过 #define 实现，有了这个之后就可以直接在编译的时候进行选择。具体的，可以通过 add_definitions() 函数控制代码的开启与关闭**

**使用时（构建项目时）：通过添加不同的参数控制宏开启和关闭**

我们可以通过-D选择来设置EXECUTABLE_OUTPUT_PATH的值，也是编译的文件的输出目录：

```shell
cmake -D EXECUTABLE_OUTPUT_PATH=“another_output” …
```

这样，我们就给 CMakeLists.txt 编译脚本传递了新的 EXECUTABLE_OUTPUT_PATH 值。

eg2:

CMakeLists.txt

```cmake
OPTION(TEST_DEBUG "option for debug" OFF)
# 完全不用这样，本身就会定义一个宏 TEST_DEBUG 了，，在 C 文件中可以直接使用，不用再显示的定义了
if(TEST_DEBUG)
	add_definitions(-DTEST_DEBUG)
endif()
# 或者endif(TEST_DEBUG)
```

程序中这样使用：

test.c

```c
#ifdef TEST_DEBUG
..
#else
..
#endif
```

运行构建项目的时候：

```shell
cmake -DUSE_MACRO=on .. # 打开
cmake -DUSE_MACRO=off .. # 关闭
```

直接 cmake:会使用主工程中的值，即使子项目定义了 ON, 主项目定义了 OFF, 仍然是 OFF 状态；

![img](C:\Users\qz\AppData\Local\Temp\企业微信截图_16538257762897.png)

组建工程：

```
cmake -DTEST_OPTION=OFF ..
cmake -DTEST_OPTION=ON
```

执行 cmake 之后，参数的值会被保存在 CMakeCache.txt 中



##### 9.CMake添加编译选项通常有以下两种方法：

NOTE: 使用 gprof 工具可以分析一段 C++ 代码的运行时间，工程是 Cmake 创建的，要使用 gprof 就要在代码编译时加入 -pg 选项，cmake 添加编译选项通常有以下两种方法

- add_compile_options

用来配置当前目录和子目录的所有目标文件的 compile options。 如果有一个库需要让所有的目标文件链接的时候，使用此命令非常方便。所有添加的 options 可以通过 **COMPILE_OPTIONS** 属性查看。add_compile_options作用范围太广，一般很少使用。

```cmake
add_compile_options(-pg)
message(STATUS "CMAKE_CXX_FLAGS=$(CMAKE_CXX_FLAGS)")
message("COMPILE_OPTIONS=${COMPILE_OPTIONS}")
```

- set(CMAKE_CXX_FLAG -pg)

配置所有 C++ 目标文件的 flags, 可以传递一些参数，比如 warnings 的等级， 使用的 C++ 标准等。 对 C 的目标文件没有作用，因此用户可谓两种文件配置不同的 flags。

```cmake
set(CMAKE_CXX_FLAGS -pg)
message(STATUS "CMAKE_CXX_FLAgS = ${CMAKE_CXX_FLAGS}")
```

NOTE:

**(1)对于某些编译选项，如：-fPIC 两种方法都可以生效，但调用 add_compile_options 方法时，CMAKE_CxX_FLAGS 不会被改变；但对于某些选项如： -pg ，可以通过修改 CMAKE_CXX_FLAGS 生效，但调用 add_compile_options 无效**

**(2)对于一个目标文件，cmake 会收集 CMAKE_CXX_FLAGS 和 COMPILE_OPTIONS 属性作为最终的 flags**



##### OPTION

用法：

```cmake
OPTION(<variable> "help_text" [value]) 
# value 定义选项默认状态，一般是 ON 或者 OFF, 除去 ON 之外, 其它所有值都认为是 OFF
```



##### 11.主工程与子工程之间的关系





##### 12. 编译链接静态库与动态库实例

这次分享的宗旨是——让大家学会创建与使用静态库、动态库，知道静态库与动态库的区别，知道使用的时候如何选择。这里不深入介绍静态库、动态库的底层格式，内存布局等，有兴趣的同学，推荐一本书**《程序员的自我修养——链接、装载与库》**。

- 有源码的，直接编译成本项目的静态库

静态库，本质就是把很多的库中的源文件编译成 .o 文件，然后

Linux:使用 ar 工具

Windows：使用 lib.exe

添加编号和检索(便于查找和检索)，打包成一个 .a 文件，

```shell
# -c:仅编译生成 StaticMath.o 文件, 不进行链接
g++ -c -o StaticMath.cpp 
ar -crv libstaticmath.a StaticMath.o
```

大一点的项目使用 makefile(cmake 等工程管理工具)来生成静态库**有源码的情况**；

```cmake
add_library(log STATIC ${SRC_LIST})
```

(1) Linux 使用静态库: 只需要在编译的时候，指定静态库的搜索路径(-L 选项)，指定静态库名（不需要lib 前缀和.a 后缀）**同样的，也可以使用 makefile 来实现** ；

(2) windows 使用静态库:

```shell
# -L 指定要链接库的搜索路径
# -l 指定库的名字
# -I 指定库头文件目录 include_directories(./include ${INCLUDE_PATH})
g++ TestStaticLibrary.cpp -L../StaticLibrary -lstaticmath
```

添加依赖库：

**新建文件夹 MathFunctions, 并在该文件夹下添加头文件 MathFunctions.h 和 源文件 mysqrt.cpp ，在该文件夹下添加 CMakeLists.txt 文件，并在其中填写如下内容：**

```cmake
add_library(MathFunctions mysqrt.cpp) # 生成静态库 libMathFunctions.a
```

为库添加使用需求：

```cmake
target_compile_definitions()
target_compile_options()
target_include_directires() # 编译时搜索的的文件路径
target_link_libraries()
# 例如：
target_indlcude_directories(MathFunctions INTERFACE 
	# INTERFACE: consumer （使用库的人）需要使用它，producer （制作库的人）不需要使用它
	{CMAKE_CURRNET_SOURCE_DIR}
)
```



- 没有源码，第三方提供静态库(.a)以及头文件(.h)

```cmake
# 这种情况仍然直接使用 add_library() 包含库文件即可???????
```



**静态库缺点：**

（1）每一个程序运行都会拷贝一份库出来，占用内存过大；

（2）不利于程序更新，游戏更新，所有程序都需要重新编译，打包，下载；全量更新，相当于重新下载；

- 动态库

动态库在程序编译时并不会被链接到目标代码中，而是在程序运行时才会被载入。

（1）不同应用程序调用相同的库，那么在内存里只有一个共享库的实例，避免了内存浪费问题；

（2）更新时，只需要动态库即可，增量更新；



##### 13. 使用 CMakeLists.txt 来写测试例程，通过 cmake 中的宏控实现

需要写测试用例（在 cmake 中添加）：

```cmake
# ctest.exe --help
ctest.exe Tutorial.exe # 
```



##### 15.CMakeLists.txt 命令解析

建一个C++工程后，我们创建一个CMakeLists.txt文件

```cmake
# 最低版本支持
cmake_minimum_required(VERSION 3.4.1)
# 第一个参数传入一个目录的路径， . 代表查找当前目录所有源文件，并将云文件名称列表保存到第二个参数变量DIR_SRC，不查找子目录
aux_source_directory(. DIR_SRCS)
# 添加一个库或者导入预编译的库
# 可以是有源码(生成一个库)或者没有源码(直接导入预先编译好的库)
add_library(
	native-lib
	SHARED
	native-lib.cpp
)
#
find_library(
	log-lib
	log
)
# 将若干个库文件链接到目标文件
target_link_libraries(
	test_bin # 最终的二进制可执行文件
	native-lib
	${log-lib}
)
```

**add_library()添加一个库或者导入预编译的库**

- 添加一个有源代码的库：

添加一个库文件，名称为

指定STATIC, SHSRED, MODULE参数来指定库的类型

STATIC:静态库；

SHARED:动态库；

MODULE:在使用 dyld 的系统中有效，如果不支持 dyld 等同于 SHARED

EXCLUDE_FORM_ALL:表示该库不会被默认构建

sorece1 sorece2….sourceN用来指定库的源文件

```cmake
add_library(<name> [STATIC|SHARED|MODULE][EXCLUDE_FROM_ALL] source1 source2...sourceN)
```

- 导入预编译的库

添加一个已存在的预编译的库名为

一般配合set_target_properties使用

```cmake
add_library(<name> <SHARED|STATIC|MODULE|UNKNOWN> IMPORTED)
```

test1:

```cmake
add_library(test_lib SHARED IMPORTED)
set_target_properties(
	test_lib # 指明目标库的名称
	# 指明要设置的参数库路径
	# /${ANDROID_ABI}/libtestlib.so # 导入库的路径
	PROPERTIES IMPORTED_LOCATION
)
```



##### 16. 命令

```cmake
# 将所有需要编译的源代码放到一个列表中
set(SOURCE_FIlES main.cpp test.cpp a.cpp b.cpp ....)
```



- include_directories() 设置头文件目录，相当于g++选项中的-l参数

```cmake
#可以用相对路径或者绝对路径，也可以使用自定义的变量值
include_directories(./include ${MY_INCLUDE})
```



- add_executable() 添加可执行文件

```cmake
add_executable(test_bin ${SRC_LIST})
```



- target_link_libraries() 将若干个库文件链接到目标文件，链接的顺序应该符合 gcc 链接顺序规则。

```cmake
target_link_libraries(test_bin lib1 lib2 lib3...)
```

**如果出现互相依赖的静态库，CMake会允许依赖图中包含循环依赖**, 

比如:

```
add_library(A STATIC a.c)
add_library(B STATIC b.c)
target_link_libraries(A B)
target_link_libraries(B A)
add_executable(main main.c)
target_link_libraries(main A)
```

被链接的库放在依赖它的库的后面，即如果上面的命令中lib1依赖于lib2,lib2又依赖于lib3，则在前面的命令中，必须严格按照lib1 lib2 lib3的顺序排列否则会报错



- add_definitions() 添加编译参数。为当前路径以及子目录文件假如有 D 引入的 define flag

```cmake
add_definitions(-DFOO -DDEBUG)
# 相当于定义了 #define FOO
# define DEBUG
```

- add_subdirectory() 如果当前目录下还有子目录时，可以使用add_subdirectory,子目录中也需要包含有CMakeLists.txt

```cmake
# sub_dir:指定包含CMakeLists.txt和源码文件的子目录的位置 
# binary_dir:是输出路径，一般可以不指定 
add_subdirectory(sub_dir [binary_dir])
```

- set_directory_properties() 设置某个路径的一种属性

```cmake
set_directory_properties(PROPERITIES prop1 value1 prop2 value2)
# prop1, prop2 取值范围INCLUDE_DIRECTORIES,LINK_DIRECTORIES,INCLUDE_REGULAR_EXPRESSION,ADDITIONNAL_MAKE_CLEAN_FILES
# value1, value2
```

- set_property() 在给定的作用域内设置一个命名的属性

```cmake
set_property(<GLOBAL | DIRECTORY [dir] |
TARGET [target...] |
SOURCE [src1...] |
TEST [test1...] |
CACHE [entry1 ...]>
[APPENT]
PROPERTY <name> [value...])
#PROPERTY 参数是必须的；第一个参数决定了属性可以影响的作用域：
#GLOBAL:全局作用域
#DIRECTORY:默认当前路径，也可以用[dir]指定路径
#TARGET:目标作用域，可以是0个或多个已有目标
#SOURCE:源文件作用域，可以是0个或多个源文件,源文件只对同目录有用
#TEST:测试作用域，可以是0个或多个已有的测试
#CACHE:必须指定0个或多个cache中已有的条目
#如果源文件很多，把所有文件一个一个加入很麻烦，可以使用 aux_source_directory() 命令或 file() 命令，会查找指定目录下的所有源文件，然后将结果存进指定的变量名中。
aux_source_directory(. SRC_LIST) # #查找当前目录多有源文件 并将名称到存到 ${SRC_LIST} 中，不能查找子目录
# 也可以使用
file(GLOB SRC_LIST *.c *.cpp) # 查找当前目录下的所有源文件，然后将结果存进指定的变量名中。
```

- add_library() **多目录多源文件处理**

主目录：主目录中的 CMakeList.txt 中添加 add_subdirectory(child_lib) 命令，指明本项目包含一个子项目 child_lib 并在target_link_libraries() 指明本项目所需要链接一个名为 child_lib 的库

子目录：子目录 child 中创建 CMakeLists.txt ，这里 child 编译为共享库

主目录：

```cmake
cmake_minimum_required(VERSION 3.4.1)
aux_source_directory(. SRC_LIST) # 当前目录所有源文件添加到列表 ${SRC_LIST}
add_subdirectory(child) # 添加子目录 child 目录下的 CMakeLists.txt
# 这里使用共享库
add_library(
	native_lib
	SHARED
	${SRC_LIST}
)
# 链接目标文件与共享库
target_link_libraries(native_lib child)
```

子目录 child 中的 CMakeLists.txt:

```cmake
cmake_minimum_required(VERSION 3.4.1)
# ${SRC_LIST} 的作用域仅在当前的 CMakeLists.txt
aux_source_directory(. SRC_LIST) # 当前目录所有源文件添加到列表 ${SRC_LIST}
# 生成动态库 native_lib
add_library(native_lib
	SHARED
	${SRC_LIST}
)
```

- **项目中添加预先编译好的库文件**

假如项目中引入了 libimported-lib.so

 假如项目中引入了libimported-lib.so

(1) 使用add_library() 命令:

第一个参数是模块名，

第二个参数 SHARED 表示动态库（如果是静态库则修改为 STATIC），

第三个参数IMPORTED表示以导入的形式添加

(2) 添加 set_target_properties() 命令设置导入路径属性到 target_link_libraries() 命令参数中，表示 native-lib 需要连接 imported-lib 模块

方法1：

```cmake
cmake_minimum_required(VERSION 3.4.1)
add_library(
	imported-lib
	SHARED # 如果是静态库则修改为 STATIC
	IMPORTED # 使用IMPORTED标志告诉CMake 只希望将库导入到项目中
)
#参数分别为库、属性、导入地址、库所在地址
set_target_properties(
	imported-lib
	PROPERTIES
	IMPORTED_LOCATION
	<路径>/libimported-lib.so
)

# 导入 native-lib 库, native-lib 有源代码, 自己生成库文件
add_library(
	native-lib
	SHARED
	${DIR_SRCS}
)
target_link_libraries(native-lib imported)
```

方法2:

**为了确保CMake可以在编译时定位头文件，使用include_directories()，相当于g++选项中的-l参数。这样就可以使用#include<xx.h>，否则需要使用#include”path/xx.h”(相对路径)**

```cmake
cmake_minimum_required(VERSION 3.4.1)
# 设置头文件目录
# 相当于: g++ -I/usr/include，添加头文件搜索目录
include_directories(<文件目录>)
# 设置编译选项选项
# 相当于 g++ -L/usr/lib，添加库文件所在目录
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -L[.so动态库所在目录]") # C
set(CMAKE_CXX_FLAG "${CMAKE_CXX_FLAGS} -L[.so动态库所在目录]") # C++
add_library(
	native-lib
	SHARED
	${SRC_LIST}
)
target_link_libraries(native-lib imported)
```

build.gradle配置:

```xml
android { 
	defaultConfig { 
		externalNativeBuild { 
			cmake { 
				//使用编译器clang/gcc 
				//cmake默认就是gnustl_static 
				arguments "-DANDROID_TOOLCHAIN=clang","-DANDROID_STL=gnustl_static" 
				//指定cflags和cppflags，效果和cmakelist使用一样 cppFlags "" cppFlags "" 
				//指定需要编译的cpu架构 
				abiFilters "armeabi-v7a" 
			} 
		} 
	} 
	externalNativeBuild { 
		cmake { 
			path "src/main/cpp/CMakeLists.txt" 
			version "3.10.2" 
		} 
	} 
}

```

**例子:一个简单的 C++ 项目写 CMakeLists.txt**

使用AndoridStudio新建一个C++项目，系统会为我们建好一个CmakeLists.txt文件

移植一个音频驱动库 -> ch0

https://www.codercto.com/a/81311.html



##### 17. 文件操作 file文件操作命令

```cmake
#将message写入filename文件中，会覆盖文件原有内容
file(WRITE filename "message")
#将message写入filename文件中，会追加在文件末尾
file(APPEND filename "message")
#从filename文件中读取内容并存储到var变量中，如果指定了numBytes和offset
#则从offset处开始最多度numBytes个字节
#另外如果指定了HEX参数，则内容会以十六进制形式存储在var变量中
file(READ filename var [LIMIT numBytes] [OFFSET offset] [HEX])
#重命名文件
file(RENME <oldname> <newname>)
#删除文件 等于rm命令
file(REMOVE [file1...])
#根据指定url下载文件
#timeout超市事件；下载状态会保存到status中；
#下载日志会被保存到log;
#sum指定多下载文件预期的MD5值
#如果指定hi自定进行比对，
#如果不一致则返回一个错误：SHOW_PROGRESS
#进度信息会以状态信息的形式被打印出来
file(DOWNLOAD url file [TIMEOUT timeout] [STATUS status] [LOG log] [EXPECTED_MD5 sum]
[SHOW_PROGRESS])
#创建目录
FILE(MAKE_DIRECTORY [dir1 dir2 ...])
#会把path转换为以unix的/开头的cmake风格路径保存在result总
file(TO_CMAKE_PATH pathresult)
#会把cmake风格的路径转换为本地路径风格window下用“\” unix下用“/”
file(TO_NATIVE_PATH path result)
#将会为所有匹配查询表达式的文件生成一个文件list
#并将该list存储进变量variable里面
#如果一个表达式指定了RELATIVE,返回的结果
#将会是相对于给定路径的相对路径
#查询表达式例子：*.cxx,*.vt?
#NOTE:按照官方文档说法，不建议使用file的GLOB指令来收集工程的源文件。
file(GLOB variable [RELATIVE path] [globbing expressions])
```

