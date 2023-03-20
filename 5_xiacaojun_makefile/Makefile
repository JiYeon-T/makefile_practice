TARGET = first_make
LIBS = -lpthread
OBJS = first_make.o xdata.o
CXXFLAGS := -I./include -std=c++11	#系统自带变量寻找文件的路径
RM = rm -f


$(TARGET) : first_make.cpp xdata.cpp
#@-$(RM) test			# 失败
#@-$(RM) test
#@#失败
# 使用 \# 等，输出 #
	@echo "start build $(TARGET)"	
#g++ first_make.cpp xdata.cpp -o first_make -lpthread -std=c++11	#导入线程库	
	@$(CXX) $^ -o $@ $(LIBS) $(CXXFLAGS)
	@echo "build success!"	

#伪目标
.PHONY : clean

clean:
#@$(RM) first_make *.o
	@$(RM) $(OBJS) $(TARGET) *.o
	@echo "cleaning"
