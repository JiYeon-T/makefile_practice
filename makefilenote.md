#### 学习Makefile
TODO:
1.《跟我一起学makefile》 陈浩
版权声明：本文为CSDN博主「haoel」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/haoel/article/details/2890
2. 代码重新拉一份, 把 7_compile_c_cpp/1/main.c add.cpp 重新拷贝一份, 然后再提交
3. ch13
4. c/cpp compile tool chain




**1.Makefile 中尽量不要写空格，免得带来不必要的麻烦**

**2.小心使用 make 的并行机制（-j 参数），如果多个 ar 命令在同一时间运行在同一个函数库打包文件上，那就有可能损坏这个函数库文件**

**学习路线:**

makefile 基础语法 -> makefile include -> makefile 函数 -> makefile 编译动态库和静态库以及链接 -> makefile shell -> makefile 多文件多项目(大型项目需要模块化管理)



##### 1.工作流程

https://haoel.blog.csdn.net/article/details/2887

1 找到第一个目标文件;

2.会自动根据目标 和 依赖文件的时间戳，判断是否需要重新编译，这就是为什么 clean 标签第一次编译的时候不会被运行的原因，makefile 可以显示指定目标文件 **make clean** 从而让 clean 后面的命令运行;

3.

- 变量

为了makefile的易维护，在makefile中我们可以使用变量。makefile的变量也就是一个字符串，理解成C语言中的宏可能会更好。

```makefile
OBJS = main.o kbd.o command.o display.o /
	   insert.o search.o files.o utils.o
```

- makefile 的自动推导

GNU 的 make 很强大，它可以自动推导文件以及文件依赖关系后面的命令，于是我们就没必要去在每一个 [.o] 文件后都写上类似的命令（cc -c main.c -o main.o）;

只要make看到一个[.o]文件，它就会自动的把[.c]文件加在依赖关系中，如果make找到一个whatever.o，那么whatever.c，就会是whatever.o的依赖文件。并且 cc -c whatever.c 也会被推导出来，于是，我们的makefile再也不用写得这么复杂。

```shell
# 没有 makefile 文件, make 工具的自动推导
main.o:main.c defs.h
# 优化为:
main.o:defs.h

#2:
g++ first_make.cpp -o first_make 
# 优化为:
make first_make	
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
#eg: 
# windows 编译c++：cl test.cpp
# Linux:g++ test.cpp
#可以使用这种方式
$(CXX) -o test test.cpp
# 这样，修改的时候，只需要修改最前面 CXX 变量的定义即可
```

##### 7.makefile 中的所有元素

(1) 显式规则

```makefile
edit:main.c defs.h
	cc -c main.c -o main.o
	cc -o edit main.o
```

(2) 隐式规则

make file 中的自动推导

```makefile
$^ #依赖,不重复
$@ #目标
```

(3) 变量定义

makefile中的变量类似于C语言中的宏定义，字符串类型

- 普通变量

传统的Makefile的变量名是全大写的命名方式

**变量会在使用它的地方精确地展开，就像C/C++中的宏一样，**

```makefile
CC = $(var)
# CC=abc
var = abc
TARGET = first_make
LIBS = -lpthread
OBJS = first_make.o xdata.o
CFLAGS = -I. -I./include
CXXFLAGS = -I. -I./include	#系统自带变量寻找文件的路径
#eg:
#添加 类似于字符串
cc=def
cc+=abc	#def abc
# 系统变量
MAKELEVEL # 个变量会记录了我们的当前 Makefile 的调用层数
SHELL
MAKEFLAGS

#= :=?= += 的区别
#https://www.cnblogs.com/adorkable/p/13576987.html
= # 读取完整个文件以后再把变量展开
:= # 就是直接赋值, 不看后边的（前面的变量不能使用后面的变量，只能使用前面已定义好了的变量。）
?= # 如果变量没有被定义过，那么变量 FOO 的值就是 “bar” ，如果 FOO 先前被定义过，那么这条语将什么也不做，
+= # 追加赋值
```

- 自动化变量: $^, $<, $@ 等(系统自带变量)

用于实现不依赖于具体文件名的命令，每一次解析时，都会是不同的目标和依赖文件

**自动化变量的意思是变量会把模式中所定义的一系列文件自动的挨个取出，直至所有的符合模式的文件都取完**

```makefile
target : prerequires
	command

$^ # prerequires, 所有的依赖文件集合，空格分隔, 自动去除其中重复的, 只保留一个
$? # 所有比目标新的依赖文件集合
# 如果希望只对更新过得依赖文件进行操作时, $? 在显示规则中比较好用
#e.g.
#lib : foo.o bar.o lose.o win.o
#	ar r lib $?
	# 仅对更新过得文件进行更新
$+ # 所有的依赖文件集合, 但是不去除重复的
$@ # target, 目标文件集合
$< # 依赖文件中当前的第一个，一个一个取出来的, 表示所有依赖文件的挨个值
$% # 仅当目标是函数库文件时, 表示规则中的依赖集合名
# 库文件: Unix:[.a], Windows:[.lib]，
# 目标文件不为库文件，其值为空
#e.g.
#foo.a : bar.o
#	$@ 表示 foo.a
#	$% 表示 bar.o
$* # 表示 % 及之前的部分
#e.g.
#依赖文件:dir/a.foo.b
#模式:a.%.b
#-> % 表示 dir/a.foo
# 尽量避免使用 $*, 
#如果没有指定模式 $* 为空; 如果依赖文件后缀是 make 可以识别的, eg.foo.c
# 那么 % 表示 foo
@ #不显示编译过程中的命令执行
- #失败之后不影响下一行代码的执行, 也许某些文件出现问题，但不要管，继续做后面的事
@#	#代码端里面的注释, 不可以直接放在行末，必须重启一行
#代码段里面的注释可以 @#
#@ 不显示编译过程中的命令
e.g.
@echo "不显示正在使用的 shell 命令"
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

e.g.

```makefile
# 生成的命令 bison -d %.y 生成 %.tab.c %.tab.h
%.tab.c %.tab.h : %.y
	bison -d $<

# foo 依赖于 parse.tab.o scan.o
foo : parse.tab.o scan.o
	$(CC) -o $@ $<
# scan.o 依赖于 parse.tab.h
scan.o : parse.tab.h
```

以上七个自动化变量中: $@ $< $% $* 在扩展时只会有一个文件，而 $^ $? $+ 都是一个额外文件列表

**这七个便来嗯还可以取得文件的目录名或是在当前目录下的符合模式的文件名，只要搭配上 D 或 F 即可，**

D - Directory

F - File

- $(@D)

```makefile
$(@D)
# 表示 $@ 的目录部分, 不以 / 为结尾
# 如果目录中不包含 /, 则 $(@D) 为 .
eg.
$@ : dir/foo.o -> $(@D): dir
$@ : foo.o -> $(@D) : .
```

- $(@F)

```makefile
# 文件部分
$@ : dir/foo.o -> $(@F): foo.o
# 相当于
$(notdir $@)
```

- $(*D)
- $(*F)
- $(%D)
- $(%F)
- $(<D)
- $(<F)
- $(^D)

所有依赖的目录部分

- $(^F)

所有依赖的文件部分

- $(+D)
- $(+F)
- $(?D)
- $(?F)

**这些变量一般都使用在 规则的命令中，且一般都是显式规则 和 静态模式规则，在隐含规则中没有定义**

- 可以取消内建的隐含规则，只要不再后面写命令就行

e.g.

```makefile
%.o : %.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) -D$(date)
#修改为：
%.o : %.c
```





---

- 变量中的变量

**要避免递归定义，导致 make 死循环**

```makefile
foo = $(bar)
bar = $(ugh)
ugh = Huh?
all:
	echo $(foo) # 输出:Huh?
e.g.
CFLAGS = $(INCLUDE_DIRS) -o
INCLUDE_DIRS = -Ifoo -Ibar
```

e.g. 件表达式和函数

```makefile
ifeq (${MAKELEVEL}, 0)
cur-dir 	:= $(shell pwd)
whoami		:= $(shell whoami)
host-type   := $(shell arch)
MAKE		:= $(MAKE) host-type=$(host-type) whoami=${whoami}
endif
```

- Makefile 中给一个变量赋值为空格

```makefile
nullstring :=
space := $(nullstring) #这里只有一个空格
space4 := $(nullstring)    # 4 spaces
```

**变量赋值后面不可以加空格**

**只支持行注释**

```makefile
 # directory to put the frobs indir这个变量的值是“/foo/bar”，后面还跟了4个空格，
 dir := /foo/bar      # end with 4 spaces
```

**如果我们这样使用这样变量来指定别的目录——“$(dir)/file”那么就完蛋了。**

- 变量的替换

```makefile
SRCS := a.c b.c c.c d.c
OBJS := $(SRCS:.c=.o) # 将变量 SRCS 中.c 结尾的换成 .o 结尾
```

- 变量之中嵌套变量

```makefile
x = y
y = z
a := $($(x)) # $(x) = y, $(y) = z, -> a = z
```

e.g.

```makefile
x = variable1
variable2 := Hello
y = $(subst 1, 2, $(x))
z = y
a := $($($(z)))
# subst 函数 将 $(x) 中的 1, 替换为 2
```

e.g. 变量组合

```makefile
first_second = Hello
a = first
b = second
# Hello
all = $($(a)_$(b))
```

e.g.

```makefile
a_objects := a.o b.o c.o
1_objects := 1.o 2.o 3.o
sources := $($(a1)_objects:.o=.c)
# 如果 $(a1)=1, sources:1.c 2.c 3.c
# 如果 $(a1)=a, sources:a.c b.c c.c
```

e.g. **函数与条件语句配合使用**

```makefile
ifdef do_sort
func := sort
else
func := strip
endif

bar := a d b q p c
foo := $($(func) $(bar))
```

e.g. “把变量的值再当成变量”这种技术，同样可以用在操作符的左边：

```makefile
dir = foo
$(dir)_sources := $(wildcard $(dir)/*.c) # foo_sources := $(wildcard foo/*.c)
define $(dir)_print
lpr $($(dir)_sources)
endif
```

- override 指示符

如果有变量是通常make的命令行参数设置的，那么Makefile中对这个变量的赋值会被忽略。

如果你想在Makefile中设置这类参数的值，那么，你可以使用“override”指示符。

**没有使用 override 的变量会被传入的参数覆盖，使用了 override 标识符的变量不会被传入的参数所覆盖**

```makefile
override <variable> = <value>
override <variable> := <value>
override <variable> += <more text>
# 多行变量/命令包
override define foo
bar
endef
```

使用方法

```shell
make variable1=abc variable2=def
```

- 多行变量

**因为命令需要以[Tab]键开头，所以如果你用define定义的命令变量中没有以[Tab]键开头，那么make就不会把其认为是命令。**

```makefile
# define指示符后面跟的是变量的名字，
# 而重起一行定义变量的值，
# 定义是以endef关键字结束。
# 其工作方式和“=”操作符一样。
# 变量的值可以包含函数、命令、文字，或是其它变量。
define two-lines-var
echo foo
echo $(bar)
endef
```

- 环境变量

make 运行时的系统环境变量可以在 make 开始运行时被载入到 Makefile 文件中，但是如果 Makefile 中已定义了这个变量，或是这个变量由 make 命令行带入，那么系统环境变量的值将被覆盖。

（如果make指定了“-e”参数，那么，系统环境变量将覆盖Makefile中定义的变量）
当make嵌套调用时（参见前面的“嵌套调用”章节），上层Makefile中定义的变量会以系统环境变量的方式传递到下层的Makefile中。

当然，默认情况下，只有通过命令行设置的变量会被传递。而定义在文件中的变量，如果要向下层Makefile传递，则需要使用exprot关键字来声明。

```makefile
# make -e # -e 会传递到子 makefile 中
```

- Makefile 中的**局部变量**

仅在当前的规则中有效

这个变量会作用到由这个目标所引发的所有的规则中去

```makefile
<target ..> : <variable-assignment>
<target ..> : override <ariable-assignment>
```

e.g.

```makefile
# 局部变量作用于优先与全局变量
prog : CFLAGS = -g
prog : prog.o foo.o bar.o
	$(CC) $(CFLAGS) prog.o foo.o bar.o
prog.o : prog.c
	$(CC) $(CFLAGS) prog.c
foo.o : foo.c
	$(CC) $(CFLGS) foo.c
bar.o : bar.c
	$(CC) $(CFLAGS) bar.c
# 在这个示例中，不管全局的$(CFLAGS)的值是什么，在prog目标，以及其所引发的所有规则中（prog.o foo.o bar.o的规则），$(CFLAGS)的值都是“-g”
```

- 模式变量

```makefile
# 所有的 [.o] 结尾的文件
%.o : CFLAGS = -o
	$(CC) $(CFLAGS) $@
```



##### 12 make 参数

```shell
make --help # 可以查看
```

e.g.

```shell
# 仅仅打印要执行的 shell 命令, 而不真正的输出可执行文件, 可以用于调试 makefile
make -n # --just-print, --dry-run, ==recon
make -i # --ignore-errors 忽略全局的所有 makefile 错误
make -k # --keep-going 如果某个规则中的命令出错了，就停止这个规则，继续执行其他规则
make -w # --print-directory 打印进入文件夹信息
# 当你使用“-C”参数来指定make下层Makefile时，“-w”会被自动打开的。如果参数中有“-s”（“--slient”）或是“--no-print-directory”，那么，“-w”总是失效的。
make -e # --environment-overrides, 系统环境变量覆盖 Makefile 中定义的环境变量
make -f # --file 指定 make 执行的 makefile 文件
make -t # --touch, (linux touch command), 更新目标文件的时间, 假装重新编译过，防止重新生成目标.
make -q # --question
make -W file # --what-if=<file>, --assume-new=<file>, --new-file=<file> print the current direcotry
make op -v # 书还粗 makefile 被执行时的信息, eg:$(DESKTOP_SESSION ), $(GDMSESSION)...
-b -m # 乎略其他版本
-B # --always-make # 总是认为需要重新编译(更新)目标文件
-C <dir> # --directory=<dir> 指定读取 makefile 的路径
-d=<option> # --debug=<option> 输出 make 的调试信息 有集中不同的级别可供选择:a, b, v, i, j, m， -d 相当于 --debug = a
-e # --venvironment-overrides
-I # 指定 makefile 的搜索路径
-j # --jobs=<jobsnum>同时运行命令的个数, 如果没有指定, 则能运行多少就运行多少;在 MS-DOS 中无效
-k # --keep-going 出错也继续, 不停止

-l # --load-average, --max-load=<load> make 运行命令的负载
-o <file> # --old-file=<file>, --assume-old=<file> 补充新生成的指定的 file, 即使这个目标的依赖文件新于它
-p # --print-data-base 输出 makefile 中的所有数据，包括所有的规则和变量。这个参数会让一个简单的 makefile 输出一堆信息
make -qp# 如果只想输出信息而不执行 makefile 的话, 可以使用 make -qp 命令
make -p -f /dev/null# 如果想查看执行 makefile 前的预设便来嗯和规则, 可以使用 make -p -f /dev/null, 这个参数输出的信息包含 makefile 文件名和行号, 便于调试
-q # --question 不运行命令, 也不输出， 仅仅是检查所指定的目标是否需要更新, 如果是 0 说明需要更新, 如果是 2 说明有错误发生
-r # --no-builtin-rules 禁止 make 使用隐含规则
-R # --no-builtin-variables 禁止 make 使用任何作用于变量上的隐含规则
-s # --silent, --quiet 在命令运行时,保护树命令的输出
-S # --no-keep-going, --stop 取消 '-k' 选项的作用。因为游戏额时候, make 的选项是从环境变量 MAKEFLAGS 中继承过来的, 所以可以在命令行中可以使用 -S 来取消 -k 的作用
-v # --version
-w # --print-directory 输出运行 makefile 之前和之后的信息, 对于调试嵌套 makefile 很有用
-W <file> # --what-if=<file>, --new-file=<file>, --assume-file=<file> 假定目标 <file> 需要更新, 如果和 -n 选项一起使用, 那么就和运行 touch 命令一样, 使 <file> 的修改时间为当前时间
--warn-undefined-variables # 如果 makefile 中使用了未定义的变量, 输出警告
```

- 如果 Makefile 中执行的命令后一部分依赖于前一步分，则要使用 ; 分隔，而不能写在两行

e.g.

```makefile
# 无效
exec:
	cd /home/qz/
	pwd
# 有效
exec:
	cd /home/qz; pwd # 打印 /home/qz, pwd 在 cd /home/qz 基础上执行
```







##### 13.文件指示

其包括了三个部分，

一个是在一个 Makefile 中引用另一个 Makefile ，就像C语言中的 include 一样；

另一个是指根据某些情况指定 Makefile 中的有效部分，就像 C 语言中的预编译#if一样；

还有就是定义一个多行的命令。

```makefile
include $(TOPDIR)/app/app.mk
include $(TOPDIR)/gui/gui.mk
include $(TOPDIR)/comm/comm.mk
```

(5)注释

Makefile中只有行注释

**注释必须顶格??????????**

**在Makefile中的命令，必须要以[Tab]键开始。**

```makefile
#first_make
first_make:first_make.cpp
# Makefile中的命令，必须要以[Tab]键开始
	$(CXX) $^ -o $@ -lpthread -std=c++11
```



- Makefile 的文件名不一定非要叫 Makefile, 也可以是其他eg: Makefile.Linux.....

```shell
# shell 中使用命令行指定 Makefile 文件
make -f Makefile.Linux
make --file Makefile.Linux
```

##### 7.包含其他 Makefile 文件

**我们可以在每个目录中都书写一个该目录的Makefile，这有利于让我们的Makefile变得更加地简洁，而不至于把所有的东西全部写在一个Makefile中，这样会很难维护我们的Makefile，这个技术对于我们模块编译和分段编译有着非常大的好处。**

在Makefile使用include关键字可以把别的Makefile包含进来，这很像C语言的#include，被包含的文件会原模原样的放在当前文件的 包含位置。

在include前面可以有一些空字符，但是绝不能是[Tab]键开始。

```makefile
include foo.make *.mk $(bar)
# 等价与
include foo.make a.mk b.mk e.mk f.mk
```

就好像 C/C++ 的 #include 指令一样。如果文件都没有指定绝对路径或是相对路径的话，make 会在当前目录下首先寻找，如果当前目录下没有找到，那么，make还会在下面的几个目录下找：

1、如果make执行时，有 “-I” 或 “--include-dir” 参数，那么make就会在这个参数所指定的目录下去寻找。
2、如果目录<prefix>/include（一般是：/usr/local/bin或/usr/include）存在的话，make也会去找。

如果有文件没有找到的话，make会生成一条警告信息，但不会马上出现致命错误。它会继续载入其它的文件，一旦完成makefile的读取，make会再重试这些没有找到，或是不能读取的文件，如果还是不行，make才会出现一条致命信息。

**如果希望没有找到，也继续执行后续操作，不理睬没有找到这个 Makefile 结果**

```makefile
# 忽略没有找到这个文件的错误, 继续后续操作
-include <filename>
# -> sinclude
```

**Makefile 中定义的系统环境变量 MAKEFILES 表示所有的 Makefile，尽量不要使用**

make 就两件事：

1. 文件的依赖关系;
2. 如何生成目标文件;

一般来说，定义在Makefile中的目标可能会有很多，但是第一条规则中的目标将被确立为最终的目标。如果第一条规则中的目标有很多个，那么，第一个目标会成为最终的目标。make所完成的也就是这个目标。

```makefile
foo.o : foo.c defs.h
	cc -c -g foo.c
# makefile 语法
targets:prerequisites
	command
	...
# or
targets:prerequisites; command
	command
	...
# 换行符 /
```

**Makefile 通常使用 /bin/sh 来执行命令**

命令解释脚本的寻找路径;

make 一般是使用环境变量 $(SHELL) 中所定义的系统 Shell 来执行命令，默认情况下使用 UNIX 的标准Shell——/bin/sh来执行命令。

但在MS-DOS下有点特殊，因为MS-DOS下没有SHELL环境变量，当然你也可以指定。如果你指定了UNIX风格的目录形式，

首先，make会在SHELL所指定的路径中找寻命令解释器，如果找不到，其会在当前盘符中的当前目录中寻找，如果再找不到，其会在PATH环境变量中所定义的所有路径中寻找。

MS-DOS中，如果你定义的命令解释器没有找到，其会给你的命令解释器加上诸如“.exe”、“.com”、“.bat”、“.sh”等后缀。

- 我们把这个Makefile叫做“**总控Makefile**”，**总控Makefile的变量可以传递到下级的Makefile中（如果你显示的声明），但是不会覆盖下层的Makefile中所定义的变量**，除非指定了“-e”参数。

- 如果你要传递所有的变量，那么，只要一个export就行了。后面什么也不用跟，表示传递所有的变量。
- 但是make命令中的有几个参数并不往下传递，它们是“-C”,“-f”,“-h”“-o”和“-W”（有关Makefile参数的细节将在后面说明， **如果不想使用 MAKEFLAGS 可以  cd subdir && (MAKE) MAKEFLAGS=**

这样就不会有 MAKEFLAGS 继承到 子Makefile 中;

子 Makefile:

```makefile
# 如果你要传递变量到下级Makefile中，那么你可以使用这样的声明：
export <variable ...>
# 如果你不想让某些变量传递到下级Makefile中，那么你可以这样声明：
unexport <variable ...>
# MAKEFLAGS 和 SHELL 这两个系统变量会被自动集成到 子 Makefile 中去
# 系统级别 MAKEFLAGS
```

e.g.

```makefile
export variable = value
# <=>
variable = value
export variable
# <=>
export variable := value
# <=>
variable := value
export variable
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

##### 9. 通配符

与 UNIX shell 中的一致

```makefile
*
?
[...]
~  
~/test : 表示用户目录下 $HOME 的 test 文件夹
~qz/test: 表示用户 qz 的 $HOME 目录下的 test 文件夹
```

e.g.

```makefile
print:*o
# $? 是一个自动化变量
	ipr -p $?
	touch print
```

e.g..

```makefile
objects = *.o # objects 的值就是 *.o
# 如果你要让通配符在变量中展开，也就是让objects的值是所有[.o]的文件名的集合
objects := $(wildcard *.o) 
```

- 关键字 wildcard，搜索当前目录下所有的 .o 文件

```makefile
SRCS += $(wildcard ./src/*.c)
SRCS += $(wildcard ./app/*.c)
```



- 搜索 路径

```makefile
# 搜索顺序:foo -> blish -> bar
vpath %.c foo
vpath % blish
vpath %.c bar
```

- 伪目标

```makefile
.PHONY:clean
clean:
	rm *.o temp
# 伪目标 .PHONY 依赖 clean
# 不管是否有 clean 这个文件, 都要运行 clean 对应的 command
```

伪目标一般没有依赖的文件。但是，我们也可以为伪目标指定所依赖的文件。伪目标同样可以作为“默认目标”，只要将其放在第一个。

```makefile
all : prog1 prog2 prog3
.PHONY : all
prog1 : prog1.o utils.o
	cc -o prog1 prog1.o utils.o
prog2 : prog2.o utils.o
	cc -o prog2 prog1.o utils.o
prog3 : prog3.o utils.o
	cc -o prog3 prog1.o utils.o
# all 依赖 三个目标文件, 所以每次都会一次生成三个目标文件 prog1 prog2 prog3 all
```

伪目标同样可以依赖于伪目标

```makefile
.PHONY:cleanall cleanobj cleandiff
cleanall:cleanobj cleandiff
	rm program
cleanobj :
	rm *.o
cleandiff:
	rm *.diff
#“make clean”将清除所有要被清除的文件。“cleanobj”和“cleandiff”这两个伪目标有点像“子程序”的意思。我们可以输入“make cleanall”和“make cleanobj”和“make cleandiff”命令来达到清除不同种类文件的目的。
make cleanall
make cleandiff
make cleanobj
```

- 多目标

用一个自动化变量“$@”（关于自动化变量，将在后面讲述），这个变量表示着目前规则中所有的目标的集合，

```makefile
bigoutpt littleoutput : text.g
	generate text.g -$(subst output, ,$@) > $@
# 等价于
bigout : text.g
	generate text.g -big > bigoutput
littleoutput : text.g
	generate text.g -little > littleoutput
# Makefile 函数
# -$(subst output,,$@)中的“$”表示执行一个Makefile的函数，函数名为subst，后面的为参数。关于函数，将在后面讲述。这里的这个函数是截取字符串的意思，“$@”表示目标的集合，就像一个数组，“$@”依次取出目标，并执于命令。
```

- 静态模式



```makefile
<targets ...> : <target-pattern> : <prereq-pqtterns...>

	<command>
	...
```

e.g. target -> [%].o -> [%].c

```makefile
objects = foo.o bar.o
all : $(objects)

$(objects) : %.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@
# 目标文件依赖 .o 文件, .o 文件依赖 .c 文件
# 而命令中的“$<”和“$@”则是自动化变量，
# “$<”表示所有的依赖目标集（也就是“foo.c bar.c”），
# “$@”表示目标集（也就是“foo.o bar.o”）。
# 于是，展开为:
foo.o : foo.c
	$(CC) -c $(FLAGS) foo.c -o foo.o
bar.o : bar.c
	$(CC) -c $(FLAGS) bar.c -o bar.o
```

**如果你的文件名中有“%”那么你可以使用反斜杠“/”进行转义，来标明真实的“%”字符。**

**如果我们的“%.o”有几百个，那种我们只要用这种很简单的“静态模式规则”就可以写完一堆规则，实在是太有效率了。“静态模式规则”的用法很灵活，如果用得好，那会一个很强大的功能。**

e.g.

```makefile
files = foo.elc bar.o lose.o

$(filter %.o, $(files)) : %.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@
$(filter %.elc, $(files)) : %.elc : %.el
	emacs -f batch-byte-compile $<
# 这个 makefile 什么意思 ?
# $(fileter %.o, $(files)) 掉用 Makefile 的 fileter 函数, 过滤 $(files), 只保留其中的 %.o 的文件
```

- 自动推导依赖性

大多数的C/C++编译器都支持一个“-M”的选项，即自动找寻源文件中包含的头文件，并生成一个依赖关系。例如，如果我们执行下面的命令：

```shell
cc -M main.c # 包含标准库的头文件
# output
# main.o : main.c defs.h
cc -MM main.c # 仅包含自己的头文件
```

因为这样一来，我们的Makefile也要根据这些源文件重新生成，让Makefile自已依赖于源文件？这个功能并不现实，不过我们可以有其它手段来迂回地实现这一功能。GNU组织建议把编译器为每一个源文件的自动生成的依赖关系放到一个文件中，**为每一个“name.c”的文件都生成一个“name.d”的Makefile文件，[.d]文件中就存放对应[.c]文件的依赖关系。**
e.g.

```makefile
# 为每个源文件生成依赖文件 .d 文件/.dep 文件
# %.dep : %.c
%.d: %.c
    @set -e; rm -f $@; /
    $(CC) -M $(CPPFLAGS) $< > $@.; /
    sed 's,/($*/)/.o[ :]*,/1.o $@ : ,g' < $@.> $@; /
    rm -f $@.
# 这个规则的意思是，所有的[.d]文件依赖于[.c]文件，
# “rm -f $@”的意思是删除所有的目标，也就是[.d]文件，
# 第二行的意思是，为每个依赖文件“$<”，也就是[.c]文件生成依赖文件，
# “$@”表示模式“%.d”文件，如果有一个C文件是name.c，那么“%”就是“name”
# ”意为一个随机编号，第二行生成的文件有可能是“name.d.12345”，
# 第三行使用sed命令做了一个替换，关于sed命令的用法请参看相关的使用文档。
# 第四行就是删除临时文件。
# 也就是
main.o : main.c defs.h
# 转成：
main.o main.d : main.c defs.h
```

于是，我们的[.d]文件也会自动更新了，并会自动生成了，当然，你还可以在这个[.d]文件中加入的不只是依赖关系，包括生成的命令也可一并加入，让每个[.d]文件都包含一个完赖的规则。一旦我们完成这个工作，接下来，我们就要把这些自动生成的规则放进我们的主Makefile中。我们可以使用Makefile的“include”命令，来引入别的Makefile文件（前面讲过），例如：

```makefile
sources = foo.c bar.c
include $(sources:.c=.d)
# 上述语句中的“$(sources:.c=.d)”中的“.c=.d”的意思是做一个替换，把变量$(sources)所有[.c]的字串都替换成[.d]，关于这个“替换”的内容，在后面我会有更为详细的讲述。
# 当然，你得注意次序，因为include是按次来载入文件，最先载入的[.d]文件中的目标会成为默认目标。

```
- sed 流式编辑器

**自动化运维，减少人机交互**

**做好备份，谨慎使用！！！**

```shell
# sed 的增删改查
# e.g. 查找具有 bash 权限的用户
sed -r -n '/bash/p' /etc/passwd
# /root 到 daemon 之间的用户
sed -r -n '/root/, /daemon/p' /etc/passwd
# line 5 - 8
sed -r -n '5, 8p' /etc/passwd
# 修改:a, i, c, 不加 -i 参数就不会修改源文件
sed -r -n '$a xxxxxx' /etc/passwd # 最后一行添加 xxxxxx
sed -r -n '$i xxxxxx' /etc/passwd # 插入 xxxxxx
sed -r -n '$c xxxxxx' /etc/passwd # 修改为 xxxxxx
# -i 参数会修改源文件, 慎用
sed -r -i '$a xxxxxx' /etc/passwd 
# 保险起见
sed -r -i '$a xxxxxx' /etc/passwd > a.txt
diff a.txt /etc/passwd # 确认无误后再 move
# 删除 delete, 添加 -i 生效
sed -r '/xxxx/d' /etc/passwd # -i
sed -r -n '$p' /etc/passwd # -n 和 p 配合使用
# 修改
# 查看 passwd 的认证方式
sed -r -n '/PasswordAuth/p' /etc/ssh/ssh_config
# 查看 port 和 passwd auth
sed -r -n '/Port/p' /etc/ssh/ssh_config
sed -r -e '/^#Port/s@.*@Port 65422@g' # 将 #Port 开头的 修改为 #Port 65422 
```



##### 10 Makefile 命令包

```makefile
# “run-yacc”是这个命令包的名字
define run-yacc
yacc $(firstword $^) # 运行 yacc 程序, 会生成 y.yab.c 文件
mv y.tab.c $@ # 修改生成的 y.tab.c 文件的名字
endef

# 使用
# 我们可以看见，要使用这个命令包，我们就好像使用变量一样。
# 在这个命令包的使用中，
# 命令包“run-yacc”中的“$^”就是“foo.y”，
# “$@”就是“foo.c”，
# make在执行命令包时，命令包中的每个命令会被依次独立执行
# 相当于对 foo.y 运行 yacc 程序, 最终生成 foo.c
foo.c : foo.y
	$(run-yacc)
```



##### 14. 条件判断

e.g. 条件编译

```makefile
lis_for_gcc = -lgnu
normal_libs =

foo : $(objects)

ifeq($(CC), gcc)
	$(CC) -o foo $(objects) $(libs_for_gcc)
else
	$(CC) -o foo $(objects) $(normal_libs)
endif
# 或者
if eq($(CC), gcc)
	libs = $(libs_for_gcc)
else
	libs = $(normal_libs)
endif

foo : $(objects)
	$(CC) -o foo $(objects) $(libs)
```

ifeq 的参数中也可以使用 参数中我们还可以使用make的函数

```makefile
# 使用 strip 函数
ifeq ($(strip $(foo)), )
```

**特别注意的是，make是在读取Makefile时就计算条件表达式的值，并根据条件表达式的值来选择语句，所以，你最好不要把自动化变量（如“$@”等）放入条件表达式中，因为自动化变量是在运行时才有的。**

```makefile
# ifdef只是测试一个变量是否有值，其并不会把变量扩展到当前位置。还是来看两个例子：
 bar =
 foo = $(bar)
 ifdef foo
 frobozz = yes
 else
 frobozz = no
 endif
# 示例二：
# 这里有点不太明白?????????????????
foo =
ifdef foo
frobozz = yes
else
frobozz = no
endif
# 第一个例子中，“$(frobozz)”值是“yes”，第二个则是“no”。
```

其他类似的命令

```makefile
ifeq(<arg1> <arg2>)
ifeq '<arg1>' '<arg2>'
ifeq "<arg1>" "<arg2>"
# ifneq, ifdef, ifndef
# e.g.
ifeq ($(CONFIG_APPS), y)
SRCS += $(TOPDIR)/apps/*.c
endif
```



##### 15.函数

Makefile 提供的函数, 使用函数来处理变量，返回值也可以作为变量使用。

函数与变量之间空格分割，变量之间逗号;

```makefile
$(<function> <arguments>)
# 或是
${<function> <arguments>}
# 函数和变量的括号最好一样，如使用“$(subst a,b,$(x))”这样的形式，而不是“$(subst a,b,${x})”的形式。因为统一会更清楚，也会减少一些不必要的麻烦。
```

- subst - subsitute

```makefile
# $(subst <from>, <to>, <text>)
comma := ,
empty := 
space := $(empty) $(empty)
foo := a b c
bar := $(subst $(space), $(comma), $(foo))
```

e.g.

```makefile
# Makefile 中尽量不要写空格，免得带来不必要的麻烦
$(subst ee, EE, "feet on the street") # f EEt on the strEEt
$(subst ee,EE,"feet on the street") # feet on the street
```

- patsubst - 模式字符串替换函数

```makefile
# 1.
dest = $(patsubst <pattern>,<replacement>,<text>)
# # 相当于
dest = $(var:<pattern>=<replacement>)
# 2.
dest = $(pathsubst %<suffix>,%<replacement>,$(var))
# # 相当于
dest = $(var:<suffix>=<replacement>)
```

- strip - 去字串中开头和结尾的空格

```makefile
objects = $(strip a.o b.o c.o )
```

- findstring - 查找字符串

```makefile
$(findstring <find>,<in>)
# 在 in 中查找 find, 如果找到返回 find, 找不到返回空
```

- filter - 过滤

```makefile
$(filter <pattern...>,<text>)
# 以 pattern 过滤 text 中的单词, 可以有多个模式
```

- filter-out - 反过滤，去除符合 pattern 的字符

```makefile
$(filter-out <pattern...>,<text>)
```

- sort - 升序排序

```makefile
$(sort <list>)
```

- word - 取单词函数

```makefile
$(word <n>,<text>)
# 取出第 n 个单词, 如果 n 比单词的总个数大, 那么返回空
# 从 1 开始计数
```

- wordlist - 取单词串函数

```makefile
$(wordlist <start_index>,<end_index>,<text>)
# start_index, end_index 都为数字
```

- words - 计算串中单词总个数

```makefile
$(words <text>)
# 如果要取出串中的最后一个单词
last_word = $(word $(words <text>),<text>)
```

- firstword - 得到串中的第一个单词

```makefile
$(firstword <text>)
# 可以使用 word 实现
$(word 1,<text>)
```

e.g.

make 使用 VPATH 变量来指定 “依赖文件” 的搜索路径，于是我们可以使用这个值来指定编译器对头文件的搜索路径参数 CFLAGS

```makefile
override CFLAGS += $(patsubst %,-I%,$(subst :, ,$(VPATH)))
# 如果 $(VAPTH) 是 "src:../header"
# 那么 $(pathsubst %,-I%,$(subst :, ,src:../header))
# 将返回 -Isrc -I../header
# 这正是 cc 或者 gcc 编译器需要的
```

**文件按操作函数**

- dir - 获取目录部分

```makefile
$(dir <names...>)
# 如果 names 中不存在 '/', 则返回当前目录
# 支持多个文件名
```

- notdir - 取出非目录部分（文件部分）

```makefile
$(notdir <names>)
# 返回最后一个 '/' 之后的部分
```

- suffix - 取文件名后缀

```makefile
$(suffix <names>)
# 如果 names 中的文件没有后缀, 则返回空
```

- basename - 取出文件名前缀

```makefile
$(basename <names>)
# 如果文件没有前缀，返回空
```

- addsuffix - 添加后缀

```makefile
$(addsuffix <suffix>,<names...>)
```

- addprefix - 添加前缀

```makefile
$(addprefix <prefix>,<names...>)
```

- join - 连接函数

```makefile
$(join <list1>,<list2>)
# list1 长度大于 list2, list1 多出来的单词个数保持原样
# list1 长度小于于 list2, list2 多出来的单词个数保持原样
```

**函数**

- foreach

```makefile
$(foreach <var>,<list>,<text>)
# list 中的每个值复制到 var 中, 然后执行 text, 
# 最后以空格分割，结果返回
```

- if

```makefile
$(if <condition>,<the-part>,<else-part>)
```

- call 作用类似于函数

```makefile
# 可以用来创建参数化的函数,
# 可以写一个表达式，定义许多需要传入的参数, 表达式中可以使用 $(1) $(2) $(3) 来使用传入的参数
# <expression> 的返回值就是 call 函数的返回值
$(call <expression>,<param1>,<param2>,<param3>,...)
e.g.
reverse = $(2) $(1)
$(call reverse,a,b)
# 返回 b a
```

- origin - 并不操作变量的值，仅仅告诉你变量是从哪里来的

```makefile
$(origin <variable>)
# 返回值
#undefined
"default"
"enviroment"
"file" # 定义在 Makefile 中的变量
"command line"
"override" # 是被 override 指示符重新定义的
"automatic" 
```

**假设一个 Makefile 包含一个定义文件 Make.def, 在 Make.def 中定义了一个 bletch, 而我们也有一个环境变量 bletch， 此时我们要判断一下，如果变量来自环境，就把它重新定义如果来自 Makedef 或者命令行等，就不重新定义**

e.g.

```makefile
ifdef bletch
ifeq ($(origin bletch) "enviroment")
bletch = barf, gag, etc.
endif
endif
```

- shell 函数

它和反引号是相同的功能

**这个函数会新生成一个 shell 程序来执行命令，所以你要注意其运行性能。如果你的 Makefile 中有一些比较复杂的功能, 并大量使用了 shell 函数，那么对程序的性能是有害的。特别是 Makefile 的隐晦规则，可能会让你的 shell 程序执行的次数比你形象的多得多**

```makefile
#`commitID=git log --format=oneline`
```

- error 产生错误时输出错误信息并退出

```makefile
$(error <text...>)
e.g.
ifdef ERROR_001
$(error error is $(ERROR_001))
endif
# e.g.
ERR = $(error fond an error!)
.PHONY:err
err: ;$(ERR)
#
$(warning text...)
# 不会退出，仅输出警告信息
```



##### 16. Makefile 目标

只要不显示指定最终目标，第一个目标就是最终目标，

所有的目标都可以作为最终目标

e.g.

```makefile
make clean
```



**在 Unix 世界中，软件发布时，其 Makefile 都包含了软件编译，安装，打包等功能，我们的 makefile 也可以参照这种功能来写**

```makefile
# 编译所有目标
all:
	...
# clean all
clean:
	...
# 安装已经编译好的程序，其实就是拷贝可执行文件到指定目录
install:
	...
# 列出所有改变过的源文件
print:
	...
# 将源程序打包备份
tar:
	...
# 创建一个目标压缩文件
dist:
	...
# 更新所有的目标以备完整编译
TAGS:
	...
# Makefile 测试
check:
test:
```

##### 17.隐含规则

make 会按照这种惯例运行，比如:

- make 会根据 .o 文件自动推导 .c 文件生成 .o 的规则, 不用显式指出

```shell
gcc -o test.o test.c
```

- **系统变量 $(CFLAGS) $(CXXFLAGS) $(LDFLAGS) **可以控制编译时的编译器参数

e.g.

```makefile
demo : main.o bar.o
	cc -o demo main.o bar.o
# .o 文件 make 会自动推导
# cc -c main.o main.c
# cc -c bar.o bar.c
```

- make 会自自己的 "隐含规则" 库中寻找, 如果找到就使用隐含规则，找不到则报错
- 编译 C 程序的隐含规则

```shell
$(CC) -c $(CFLAGS)
```

- 编译 C++ 程序的隐含规则

```shell
$(CXX) -c $(CPPFLAGS)
```

- 汇编的隐含规则

```shell
<n>.o 的目标会自动推导为 <n>.s
# 默认使用编译器 as
$(AS) $(ASFLAGS)
<n>.s 的目标自动推导为 <n>.S
# 默认使用 C 预编译器 CPP
$(AS) $(ASFLAGS)
```

- 链接 objects 的隐含规则

```makefile
# <n> 自动推导依赖于 <n>.o
# 运行 C 编译器来连接程序(ld)
$(CC) $(LDFLAGS) <n>.o <LOADLIBES> <LDLIBS>
# 这个规则对于一个 和 多个 objects 文件的工程都是有效的
# 例如:
x : y.o z.o
# 隐含规则将执行:
cc -c x.c -o x.o
cc -c y.c -o y.o
cc -c z.c -o z.o
cc -o x x.o y.o z.o
rm -f x.o 
rm -f y.o 
rm -f z.o
```

**如果没有一个源文件（上例中的 x.c） 与你的目标文件相关联，那么你最好显式写出生成规则，否则会报错**

- fortan, pascal, 等其他语言的隐含规则



- 模式规则 - pattern

一个模式规则中，需要有一个 % 字符，% 的意思是表示一个或多个任意字符，在依赖目标中同样可以使用 % ，只是 % 的取值，取决于其目标

**% 的展开发生在变量和函数展开之后，边量和函数的展开发生在 Makefile 载入时，而模式规则中的 % 则发生在运行时**

% ——表示长度任意的非空字符串

```makefile
%.c
s_%.c
```

e.g.

```makefile
%.o : %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@
```



##### 18. 函数库文件的打包

库文件就是通过 ar 来讲程序编译的中间文件 .o 打包

一个函数库文件由多个文件按组成

```makefile
# 专门为了打包文件
archive(member)

e.g.
foolib(hack.o kludge.o)
# 等价于
foollib(hack.o) foolib(kludge.o)
# 或者
foolib(%.o)
```

- 库文件的隐含规则

e.g.

```makefile
make foo.a(bar.o)
# 如果没有 bar.o , make 会去找 bar.c
# 隐含命令
cc -c bar.c -o bar.o
ar r foo.a bar.o
rm -f bar.o
# 也可以使用自动化变量 $%
```

- 库文件的后缀规则

可以使用后缀规则和隐含规则来生成函数库打包文件

```makefile
.c.a:
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $*.o
	$(AR) r $@ $*.o
	$(RM) $*.o
# 等效与
%.o : $.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $*.o
	$(AR) r $@ $*.o
	$(RM) $*.o
```





##### 19. GNU  make 与其他的 make 都大同小异



##### 10. Make.defs  的使用

如何包含其他 Make.defs 文件

```Makefile
```

