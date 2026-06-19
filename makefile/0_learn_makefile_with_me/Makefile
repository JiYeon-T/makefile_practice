########################## make更新库 ##########################
export CC = gcc
export Q = @
export CFLAGS := -g
export CXXFLAGS :=
MAKE :=
MAKEFLAGS += --print-directory
TARGET = edit
TARGET_LIB = libmylib.a
BUILD_LIB:= 1

#NOTE: 编译库的时候不要用-j选项,可能损坏文件
objs = main.o kbd.o command.o display.o \
			insert.o search.o files.o utils.o

ifneq ($(BUILD_LIB),)
#$(info "build libs $(TARGET_LIB)")
all: $(TARGET) $(TARGET_LIB)
else
all: $(TARGET)
endif

$(TARGET): $(objs)
	$(Q)echo "CFLAGS:$(CFLAGS)"
	$(CC) $(CFLAGS) -o $(TARGET) $(objs)


#生成库文件测试一个函数库文件由多个文件组成;由AR命令实现
#utilib(*.o): $(objs)
utilib(utils.o): utils.o
	$(AR) cr utilib utils.o


# 生成函数库测试:
#$(shell mkdir -p build lib)

#all: $(TARGET_LIB)

#规则1:生成静态库
#依赖所有的.o文件生成静态库
$(TARGET_LIB): $(filter-out main.o,$(objs))
	$(Q)echo "generating lib $(TARGET_LIB)"
	$(AR) $(ARFLAGS) -o $@ $^


.PHONY: clean

clean:
	$(Q)echo "clean objs:$(objs)"
	$(Q)rm -f $(objs)
	$(Q)rm -f $(TARGET)
	$(Q)rm -f $(TARGET_LIB)
	
