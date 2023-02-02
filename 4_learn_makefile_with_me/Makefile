# optimization
# op1.Makefile 中的第一个目标文件 -> 最终的目标文件 -> 通过目标文件依赖的文件寻找其他需要的文件
# edit:main.o kbd.o command.o display.o insert.o search.o files.o utils.o
# 	cc -o edit main.o kbd.o command.o display.o insert.o search.o files.o utils.o

# op2:可以使用变量对所有需要的中间变量进行管理，减少修改 makefile 的复杂度 
#1.换行: /
objects = main.o kbd.o command.o display.o insert.o search.o files.o utils.o

edit : $(objects)
	@echo $(objects)
	cc -o edit $(objects)

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
$(objects) : defs.h
kbd.o command.o  utils.o : command.h
display.o insert.o search.o files.o: buffer.h


# .PHONY意思表示clean是一个“伪目标”
# 不成文的规矩是——“clean从来都是放在文件的最后”
# 该目标没有放在 Makefile 最开始的地方, 所以 make 的时候不会被执行
.PHONY:clean

clean:
#rm edit $(objects)
	@rm edit *.o
	@echo "clean"