#### 学习Makefile
TODO:
1.《跟我一起学makefile》 陈浩
https://haoel.blog.csdn.net/article/details/2886



**学习路线:**

makefile 基础语法 -> makefile include -> makefile 函数 -> makefile 编译动态库和静态库以及链接 -> makefile shell -> makefile 多文件多项目(大型项目需要模块化管理)



##### 1.makefile 的自动推导

```shell
# 没有 makefile 文件, make 工具的自动推导
make first_make	
# g++ first_make.cpp -o first_make 
```

有 makefile 时,手动编译的版本

```makefile
#makefile的格式
target : prerequisites
　　command　　//任意的shell 命令
#eg:
first_make:first_make.cpp
	g++ first_make.cpp -o first_make

```

**NOTE:**

1）会自动根据目标 和 依赖文件的时间戳，判断是否需要重新编译;

2)

3)



##### 2.通常代码是按照不同的模块来进行管理的

Linux 中直接使用 thread 库, 会报错，需要显式的引入thread 库;

```makefile
first_make:first_make.cpp
	g++ first_make.cpp -o first_make -lpthread -std=c++11 #C++11 标准 thread 库
```

##### 3.多文件编译

```makefile
first_make:first_make.cpp xdata.cpp
	g++ first_make.cpp xdata.cpp -o first_make -lpthread -std=c++11
# 把 xdata.cpp 也一起编译进来
# 在当前文件中寻找 .h 文件, -> 后面再: 添加头文件路径
```

##### 4.引入头文件目录



##### 5.gcc编译器的可选参数

```shell
-c #只编译,不链接
-g #gdb
-0[0, 1, 3] #优化级别
-Dn[=definition] #向代码中传递宏定义
-Idir #在编译源文件时，添加一个搜索头文件的额外目录，可以是多个 dir
-I/usr/local/include # eg:

-Ldir #在编译源文件时,增加一个搜索库文件的额外目录
-L/usr/local/lib

-llibary #在编译链接文件时，添加一个额外的库:liblibary.so，
-lpthread #eg: 

-Wwarning #允许产生 warnging 类型的信息,显示警告，最终版本会关闭警告
-Wall # 显示所有警告
-Werror # 警告错误对待, 会导致编译报错
```

查看 gcc 的工作流程:预处理 -> 编译 -> 汇编 -> 链接

```shell
# 预处理 -E, 添加头文件进来, 替换宏定义等
g++ -E test.cpp > test_gcc.ii
# 编译 -S, 生成 test_gcc.s 汇编文件
g++ -S test_gcc.ii
# 汇编 -c, 生成 test_gcc.o 目标文，不进行链接
g++ -c test_gcc.s
# 链接, -o 生成 test 可执行文件
g++ -o test test_gcc.o
```

##### 6.使用变量的原因

```shell
# 不同编译平台使用的命令可能不同，为了增加 makefile 的可移植性，尽量使用变量的方式
#eg: windows 编译c++：cl test.cpp
#Linux:g++ test.cpp
#可以使用这种方式
$(CXX) -o test test.cpp
# 这样，修改的时候，只需要修改最前面 CXX 变量的定义即可
```

##### 7.makefile

(1)显式规则

(2)隐式规则

```makefile
$^ #依赖,不重复
$@ #目标
```



(3)变量定义

makefile中的变量类似于C语言中的宏定义，字符串类型

```makefile
#(1)系统自带变量
$^ #依赖,不重复
$@ #目标
@ #不显示编译过程中的命令执行
- #失败之后不影响下一行代码的执行
@#	#代码端里面的注释, 不可以直接放在行末，必须重启一行
#代码段里面的注释可以 @#
#@ 不显示编译过程中的命令

#(2)自己手动定义变量
#= :=?= += 的区别
#https://www.cnblogs.com/adorkable/p/13576987.html
#= 读取完整个文件以后再把变量展开
#:= 就是直接赋值, 不看后边的
#？= 如果不存在就赋值 存在就什么都不干
#+= 追加赋值
CC=$(var)
# CC=abc
var=abc
TARGET=first_make
LIBS=-lpthread
OBJS=first_make.o xdata.o
CXXFLAGS=-I./include	#系统自带变量寻找文件的路径
#eg:
#添加 类似于字符串
cc=def
cc+=abc	#def abc

#(3)自动推理
$(TARGET):first_make.cpp
	$(CXX) $^ -o $@ -lpthread -std=c++11
$(TARGET):first_make.o xdata.o
	#自动推导 .o 文件
#添加包含文件进行编译
g++ -o first_make first_make.cpp xdata.cpp -I./include -std=c++11 -lpthread
```

举个栗子:

```makefile
#如果使用直接赋值, DIR目录下还什么都没有
DIR:=/home/uname/project/output
FILES=$(shell find $(DIR) -type f)

all:build1 build2 install
	@echo "done"
	
install:
	$(foreach out, $(FILES), $(call xx, $(strip $(out))))
#假设DIR文件夹本来是空的，build1和build2过程会在DIR文件夹下产生文件（这里省略了build1和build2的具体内容），由于我们FILES变量使用的是延迟展开赋值，直到install过程的命令中才使用了这个变量，因此FILES变量会在这里进行展开，结果就是DIR下的所有文件。
#如果FILES变量使用立即展开赋值，那么在一开始FILES就被展开了，此时还没有尽心build1、build2以及install的步骤，DIR下面是空的，所以FILES变量也为空。
```



(4)文件指示

(5)注释

```makefile
#first_make
first_make:first_make.cpp
	$(CXX) $^ -o $@ -lpthread -std=c++11
```

##### 8.gcc 编译动态链接库（运行的时候才可以确定地址）

```shell
-fPIC	#位置无关的代码
-shared	#
g++ -shared -FPIC mylib.cpp -o libmylib.so
g++ test.cpp -lmylib -L/root/cpp -I/root/include
#!bin/sh
LD_LIBRART_PATH=./
export LD_LIBRARY_PATH=./
./test
#静态库
ar -crv libmylib.a mylib.o
```



