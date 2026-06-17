# 子目录下的 Makefile
objects += subtest.o

# $(objects) : subtest.c
# # $(CC) $(CFLAGS) $(objects)
# 	$(CC) subtest.c -c subtest.o



#使用总 Makefile 传递过来的变量
#export MAKE += -w

subtest.o: subtest.c
	$(Q)$(CC) -c -o subtest.o subtest.c


test:
	$(Q)echo "make:$(MAKE)"
	$(Q)echo "make flag:$(MAKEFLAGS)"
	$(Q)echo "sh:$(SHELL)"


.PHONY:clean

clean:
	$(Q)rm -f $(objects)


