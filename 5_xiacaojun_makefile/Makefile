TARGET=first_make
LIBS=-lpthread
OBJS=first_make.o xdata.o
CXXFLAGS:=-I./include -std=c++11	#系统自带变量寻找文件的路径


$(TARGET):first_make.cpp xdata.cpp
#只支持行注释，且最前面不可以空格,
#代码段里面的注释可以 @#
#@ 不显示编译过程中的命令
	@-$(RM) test			# 失败
	@#失败
	@echo "start build $(TARGET)"	# 使用 \# 等，输出反斜杠
#g++ first_make.cpp xdata.cpp -o first_make -lpthread -std=c++11	#导入线程库	
	@$(CXX) $^ -o $@ $(LIBS) $(CXXFLAGS)
	@echo "build success!"
	@-$(RM) test	

#伪目标
clean:
	@#$(RM) first_make *.o
	@$(RM) $(OBJS) $(TARGET) *.o
	@echo "cleaning..."
.PHONY:clean *clean
