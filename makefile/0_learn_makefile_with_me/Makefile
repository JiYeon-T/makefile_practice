########################## 函数 ##########################
export CC = gcc
export Q = @
export CFLAGS := -g
export CXXFLAGS :=
MAKE :=
MAKEFLAGS += --print-directory
TARGET = edit


objs = main.o kbd.o command.o display.o \
			insert.o search.o files.o utils.o

$(TARGET): $(objs)
	$(Q)echo "CFLAGS:$(CFLAGS)"
	$(CC) $(CFLAGS) -o $(TARGET) $(objs)


######################## 字符串处理函数 #################
comma:=,
empty:=
space:= $(empty) $(empty)
foo:= a b c
#将字符串foo中的space全都替换成comma,等价于前面变量章节讲过的:$(bar: ,,)
bar:= $(subst $(space),$(comma),$(foo))
fun:
	$(Q)echo "bar:$(bar)"

#替换函数
#Makefile中不要随便添加空格,EE前添加空格就从'EE'变成了' EE'
fun_subst:
	$(Q)echo $(subst ee,EE,feet on the street)

#模式替换
fun_patsubst:
	$(Q)echo $(patsubst %.c,%.o,x.c    c.c bar.c)
	$(Q)echo $(patsubst %.c,%.o,x.c.c.c bar.c)

#去空格函数
fun_strip:
	$(Q)echo $(strip "   a b c  ")
	$(Q)echo $(strip   a b c  )

#查找字符串
fun_findstring:
	$(Q)echo $(findstring a,a b c)
	$(Q)echo $(findstring a, b c)

#过滤函数
#按照pattern过滤字符串中的单词,保留符合pattern的单词,可以有多个模式
sources:=foo.c bar.c baz.s ugh.h foo.c
fun_filter:
	$(Q)echo $(filter %.c %.s,$(sources))
	$(Q)echo $(filter %.s,$(sources))

#反过滤函数
#符合pattern的去除,不符合的返回
fun_filter_out:
	$(Q)echo $(filter-out %.c,$(sources))
	$(Q)echo $(filter-out %.s,$(sources))

#排序函数(升序)
#sort函数会删除list中重复的单词
fun_sort:
	$(Q)echo $(sort $(sources))

#取单词函数
#返回text中第n个单词;下标从1开始;如果没找到,返回空
fun_word:
	$(Q)echo $(word 2,$(sources))

#取某个区间的单词返回;[start_index,end_index]
fun_wordlist:
	$(Q)echo $(wordlist 2,3,$(sources))

#单词个数统计
fun_words:
	$(Q)echo "words num:$(words $(sources))"

#返回text中的第1个单词
fun_firstword:
	$(Q)echo $(firstword $(sources))
	$(Q)echo $(word 1,$(sources))



.PHONY: clean

clean:
	$(Q)echo "clean objs:$(objs)"
	$(Q)rm -f $(objs)
	$(Q)rm -f $(TARGET)

