#都在同一个文件夹下, 所以也不需要添加路径
mytool:main.o tool1.o tool2.o
	@#可执行文件
	gcc main.o tool1.o tool2.o -o mytool 	
	@#可执行文件
	@#可执行文件
CC=abc
#CC是系统变量, 默认是==gcc的, 所以 ?= 不执行
CC?=abc	
GG?=zzz
CC+=abcdef
#@echo ${CC}


#main.o:main.c
#	@# -Wall = warning all, 查看编译过程中所有的警告, -W警告类型
#	gcc main.c -c -Wall -g -o main.o		
#	echo $(GG)
#	@#输出:CC abcdef
#	echo $(CC)
#CC:=def
#tool1.o:tool1.c
#	gcc tool1.c -c -Wall -g -o tool1.o
#	echo $(GG)
#tool2.o:tool2.c
#	gcc tool2.c -c -Wall -g -o tool2.o

#clean:
#	rm *.o mytool -rf
#	#@#变量$(RM)相当于rm -f
#	$(RM) *.o mytool -r

############# 2.可以定义变量 ####################################
#OBJS=main.o tool1.o tool2.o
#CC=gcc		# CC在makefile中的默认值就是GCC，这里只是为了说明定义变量
#CFLAGS+=-c -Wall -g	# Compile Flags可以使用+=
#RM+=-r
#mytool:$(OBJS)
#	$(CC) main.o tool1.o tool2.o -o mytool
#	echo $(CC)
#	echo $(CFLAGS)
#	echo $(RM)
#main.o:main.c
#	$(CC) main.c $(CFLAGS) -o main.o
#tool1.o:tool1.c
#	$(CC) tool1.c $(CFLAGS) -o tool1.o

#tool2.o:tool2.c
#	$(CC) tool2.c $(CFLAGS) -o tool2.o

#clean:
#	rm *.o mytool -rf
#	@#变量$(RM)相当于rm -f
#	$(RM) *.o mytool -r

############ 3.使用一些组合进行替换 ############################
# OBJS=main.o tool1.o tool2.o
# CC=gcc		# CC在makefile中的默认值就是GCC，这里只是为了说明定义变量
# CFLAGS+=-c -Wall -g	# Compile Flags 可以使用+=
# mytool:$(OBJS)
# 	@#shell命令前加@ -> 不打印 shell 命令，
# 	@$(CC) $^ -o $@	# $^代表上一行的目标， $@代表要生成的目标文件
# 	@echo 1

# main.o:main.c
# 	@$(CC) $^ $(CFLAGS) -o $@	# $@这里代表main.o，即使在注释中，这些也会被替换掉
# 	@echo 2

# tool1.o:tool1.c
# 	@$(CC) $^ $(CFLAGS) -o $@
# 	@echo 3

# tool2.o:tool2.c
# 	@$(CC) $^ $(CFLAGS) -o $@
# 	@echo 4

# clean:
# 	@rm *.o mytool -rf
# 	@#变量$(RM)相当于rm -f
# 	@$(RM) *.o mytool -r

############ 4.再进行简化 #####################################
#OBJS=main.o tool1.o tool2.o
#CC=gcc		
#CFLAGS+=-c -Wall -g	
#mytool:$(OBJS)
#	$(CC) $^ -o $@	

# %通配符,代表同一个文件
#%.o:%.c	  
#	$(CC) %^ $(CFLAGS) -o %@

#clean:
#	rm *.o mytool -rf





