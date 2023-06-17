# optimization
# step1.Makefile 中的第一个目标文件 -> 最终的目标文件 -> 通过目标文件依赖的文件寻找其他需要的文件
# edit:main.o kbd.o command.o display.o insert.o search.o files.o utils.o
# 	cc -o edit main.o kbd.o command.o display.o insert.o search.o files.o utils.o

# op2:可以使用变量对所有需要的中间变量进行管理，减少修改 makefile 的复杂度 
#1.换行: /
#objects = main.o kbd.o command.o display.o insert.o search.o files.o utils.o
CC = gcc
TARGET = edit
CFLAGS =
Q = @
# 定义$(MAKE)宏变量的意思是，也许我们的make需要一些参数，所以定义成一个变量比较利于维护。
#-c
MAKE = make -n -w
# 不需要添加当前目录, 默认就在当前目录查找
SRCS += $(wildcard *.c)
SRCS += $(wildcard app/*.c)
OBJS := $(SRCS:.c=.o)
# 变量的替换
# subst 函数
x = variable1
variable2 := Hello
y = $(subst 1, 2, $(x))
z = y
a := $($($(z)))
# 通过 makefile 传入的变量
INVAR1 += invar1
override INVAR2 += invar2_override
# 多行变量
define two-lines-var
echo foo
echo $(bar)
endef
# 条件判断
foo =
ifdef foo
frobozz = yes
else
frobozz = no
endif

# edit : $(objects)
# 	@echo $(objects)
# 	cc -o edit $(objects)

# command 也可以放到与 target 在同一行, 但是需要用 ; 分割
# edit : $(objects); cc -o edit $(objects)
$(TARGET) : $(objects)
# @echo $(objects)
# 系统变量
# echo $(MAKEFILES)
	-$(CC) -o $(TARGET) $(objects)

# op2: 静态模式
$(objects) : %.o : %.c
# @echo $(objects)
	$(CC) -c $(CFLAGS) $< -o $@

#@echo $(MAKEFILES)

# main.o:main.c defs.h
# 	cc -c main.c
# kbd.o:kbd.c defs.h command.h 
# 	cc -c kbd.c
# command.o:command.c defs.h command.h
# 	cc -c command.c
# display.o:display.c defs.h buffer.h
# 	cc -c display.c
# insert.o:insert.c defs.h buffer.h
# 	cc -c insert.c
# search.o:search.c defs.h buffer.h 
# 	cc -c search.c
# files.o:files.c defs.h buffer.h command.h
# 	cc -c files.c
# utils.o:utils.c defs.h
# 	cc -c utils.c

# op3: 根据 Makefile 的自动推导优化(这种方法，也就是 make 的“隐晦规则”)
# main.o:defs.h
# kbd.o:defs.h command.h
# command.o:defs.h command.h
# display.o:defs.h buffer.h
# insert.o:defs.h buffer.h
# search.o:defs.h buffer.h 
# files.o:defs.h buffer.h command.h
# utils.o:defs.h

# op4: 将重复的 .h 文件也通过变量收集起来
# 但是: 这种风格，让我们的makefile变得很简单，但我们的文件依赖关系就显得有点凌乱了
# 缺点: 一是文件的依赖关系看不清楚，二是如果文件一多，要加入几个新的.o文件，那就理不清楚了
# (自动推导)
$(objects) : defs.h
kbd.o command.o  utils.o : command.h
display.o insert.o search.o files.o: buffer.h

# op5: 使用 gcc -MM main.c -> main.c:main.o defs.h 进行优化
# sources=main.c command.c
# $(sources) 中的所有 .c 替换为 .dep
# include $(sources:.c=.dep)


# 添加其他 Makefile 文件
# -include subtest/Makefile 即使没有找到该 Makefile 后续的命令也要继续进行
# include subtest/Makefile
# 目的: 进入 subtest 目录, 然后 make
subsystem:
	cd subtest && $(MAKE)
# 或者
# subsystem:
# 	$(MAKE) -C subtest


# .PHONY意思表示clean是一个“伪目标”
# 不成文的规矩是——“clean从来都是放在文件的最后”
# 该目标没有放在 Makefile 最开始的地方, 所以 make 的时候不会被执行
# .PHONY:clean
# clean:
# #rm edit $(objects)
# 	@-rm $(TARGET) *.o
# 	@echo "clean"

# 条件表达式和函数
ifeq (${MAKELEVEL}, 0)
cur-dir 	:= $(shell pwd)
whoami		:= $(shell whoami)
host-type   := $(shell arch)
MAKE		:= $(MAKE) host-type=$(host-type) whoami=${whoami}
endif

# Makefile 函数测试
comma := ,
empty := 
space := $(empty) $(empty)
foo := a b c
bar := $(subst $(space), $(comma), $(foo))

#var1 = $(subst ee, EE, "feet on the street")
#src1 = a.c b.c c.c d.c
#dest1 = $(patsubst %.c,%.o,$(src1))
#dest1 = $(src1:%.c=%.o) # 与变量替换作用相同
#before = a b c e e   # space
#after = $(strip $(before)) 
#FIND_STR = $(findstring e,$(before))
SRC_STR = test.s test.h readme.md a.c testj.java test3.python test4.makefile test5.cmake
# 字符串处理函数
#DEST_STR = $(filter %.c %.s,$(SRC_STR))
#DEST_STR = $(filter-out %.c %.s,$(SRC_STR))
#DEST_STR = $(sort $(SRC_STR))
#DEST_STR = $(word 1,$(SRC_STR))
#DEST_STR += $(word 5,$(SRC_STR))
#DEST_STR = $(wordlist 1, 3, $(SRC_STR))
#DEST_STR = $(word $(words $(SRC_STR)), $(SRC_STR))
#DEST_STR = $(firstword $(SRC_STR))
#DEST_STR += $(word 1,$(SRC_STR))
# 文件名处理函数
FILE_PATHS = test.c head.h head.c /etc/passwd ~/qz.c /home/qz/desktop/code/project21/reademe.md
DIRS = $(dir $(FILE_PATHS))
FILES = $(notdir $(FILE_PATHS))
SUFFIXS = $(suffix $(FILE_PATHS))
FILENAMES = $(basename $(FILES))
TEST_FILES = $(addsuffix .c,$(FILENAMES))
TEST_FILES += $(addprefix ./src/,$(FILENAMES))
PREFIX = ./
FINAL = $(join $(PREFIX),$(FILE_PATHS))
# foreach
names := a b c d e f g h i
objects := $(foreach n,$(names),$(n).o)
sources := $(foreach n,$(names),$(n).c)
PRINT_FLAGS = y
# 表达式
reverse = $(2) $(1)
RESULTS = $(call reverse, a, b)
contents := $(shell cat foo)
files := $(shell echo *.c)
outputs := $(shell ps -a > ./foo)
# ERROR_001 = 1

ifdef ERROR_001
$(error error is $(ERROR_001))
endif

# op1: 伪目标同样可以依赖于伪目标
.PHONY : cleanall cleanobj cleandiff cleantarget
cleanall : cleanobj cleandiff cleantarget

cleantarget:
	$(Q) echo "clean target"
	-$(Q) rm $(TARGET)

cleanobj :
	$(Q) echo "cleanobj"
	-$(Q) rm *.o

cleandiff:
	$(Q) echo "cleandiff"
	-$(Q) rm *.diff

# 后面的命令在前面命令的基础上执行
exec:
	$(Q) cd /home/qz; pwd
	$(Q) echo "SRCS:$(SRCS)"
#$(Q) echo "test:$(cur-dir), MAKELEVEL:${MAKELEVEL}"
	$(Q) echo "OBJS:$(OBJS)"

str_test:
# Makefile 函数测试
#$(Q) echo "a:$(a) x:$(x) y:$(y) var2:$(variable2)"
#$(Q) echo "INVAR1:${INVAR1}, INVAR2:${INVAR2}"
#$(Q) echo "two lien:${two-lines-var}"
#$(Q) echo ${frobozz}
#$(Q) echo "bar:$(bar)"
#$(Q) echo "var:$(var1)"
#$(Q) echo "dest1:$(dest1)"
#$(Q) echo "before:$(before)"
#$(Q) echo "afterr:$(after)"
#$(Q) echo "find:$(FIND_STR)"
#$(Q) echo "DEST_STR:$(DEST_STR)"
	$(Q) echo "VAPTH:$(VAPTH)"
	$(Q) echo "MAKEFILES:$(MAKEFILES)"

dir_test:
	$(Q) echo "DIRS:$(DIRS)"
	$(Q) echo "FILES:$(FILES)"
	$(Q) echo "SUFFIXS:$(SUFFIXS)"
	$(Q) echo "FILENAMES:$(FILENAMES)"
	$(Q) echo "TEST_FILES:$(TEST_FILES)"
	$(Q) echo "FINAL:$(FINAL)"

func_test:
	$(Q) echo "func_test"
	$(Q) echo "objects:$(objects)"
	$(Q) echo "sources:$(sources)"
	$(Q) echo "RESULTS:$(RESULTS)"
	$(Q) echo "RESULTS origin:$(origin RESULTS)"
	$(Q) echo "VPATH origin:$(origin VPATH)"
	$(Q) echo "gcc origin:$(origin gcc)"
	$(Q) echo "MAKEFLAGS origin:$(origin MAKEFLAGS)"
# $(Q) echo $(contents)
# $(Q) echo $(files)
#$(Q) echo "outputs:$(outputs)"
	$(shell ps -a > foo)
#$(shell uname -a > foo)
#ERROR_001 = 1
# ifdef ERROR_001
# $(error error is $(ERROR_001))
# endif