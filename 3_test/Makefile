# make寻找第一个目标文件作为最终的目标文件
# 注释要顶格写， 不可以Tab

OBJS=main.o tool.o
CFLAGS=-c -Wall -g
CC=gcc

mytool:$(OBJS)
	$(CC) $(OBJS) -o mytool
# echo  OBJS = $(OBJS)
# echo CFLAGS = $(CFLAGS)

#main.o:main.c
#	$(CC) main.c $(CFLAGS) -o main.o

#tool.o:tool.c
#	$(CC) tool.c $(CFLAGS) -o tool.o

# clean这种，没有被第一个目标文件直接或者间接关联，所以它后面的定义不会被自动执行
# 可以使用:make clean 执行

# makefile的隐晦规则
# 实际上,make还有自动推导，当看到main.o会生成:gcc -c main.c, 自动寻找main.c,

# .PHONY是一个虚伪的目标文件
# -rm mytool $(OBJS) 前面的-的意思是：也许中途会出现某些问题，但是不要理睬，继续执行后面的操作

# makefile文件之间的包含关系
# include<filename>  包含子 makefile
-include tool.mk

.PHONY:clean
clean:
	-rm -rf mytool $(OBJS)
