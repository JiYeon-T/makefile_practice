# 子目录下的 Makefile
# objects += subtest.o
# CC = gcc
# CFLAGS += -Isubtest -c
# CXXFLAGS += -Isubtest -c

# $(objects) : subtest.c
# # $(CC) $(CFLAGS) $(objects)
# 	$(CC) subtest.c -c subtest.o

# Makefile 开头的第一个文件就是目标文件 -> .PHONY == target, clean = prerequires
.PHONY : clean


# 使用总 Makefile 传递过来的变量

export MAKE += -w

clean:
	$(Q) echo $(MAKE) 
	$(Q) echo $(MAKEFLAGS)
	$(Q) echo $(SHELL)