# 源文件的获取(收集)由每个文件夹下的 Make.defs 获取
# 优点: 每个 make.defs 可以决定哪些源文件可以添加到项目, 哪些源文件不需要添加到项目
# Linux, Nuttx 都使用这种方式


BIN := main
OJBPATH := obj

SRCS :=
SRCS += main.c
SRCS += src/common.c
SRCS += src/sysmanager.c

TOP_DIR := .
CFLAGS := -o3 -g0 -I./include
VPATH :=

Q = @


# 包含其他 Make 文件
-include src/module1/Make.defs
-include src/module2/Make.defs
-include src/module3/Make.defs

OBJS := $(patsubst $.c,$(OJBPATH)/%.o,$(notdir $(SRCS)))
# 为每个文件都生成依赖文件 gcc -M
DEPS := $(patsubst %.c,$(OJBPATH)/%.d,$(notdir $(SRCS)))

CC := gcc
WARNINGS 	:= -Werror -Wall
CFLAGS		+= $(WARNINGS)
CFLAGS 		+= -I/include
LDFLAGS		:=

# 创建保存目标文件目录
$(shell if [ ! -d $(OBJPATH) ]; then mkdir -p $(OBJPATH); fi)

$(BIN) : $(OBJS)
	$(Q) echo "SRCS:$(SRCS)"
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJPATH)/%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJPATH)/%.d : %.c
	@(Q) $(CC) -MM $(CFLAGS) $< | sed 's, \($*\)\.o[:]*,$(OBJPATH)/\1.o $@:,g' > %@


.PHONY : clean

clean:
	$(Q) rm -f $(OBJPATH)/*.o $(OBJPATH)/*.d  $(BIN)
	$(Q) echo "clean"

-include $(DEPS)