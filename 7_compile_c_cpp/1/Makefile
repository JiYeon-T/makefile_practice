SRCS += $(wildcard *.c) $(wildcard *.cpp)
TARGET = test
CC = g++
CFLAGS += -I./ 
CXXFLAGS += -I./  -lstdc++
Q = @


$(TARGET) : $(SRCS)
	$(Q) echo "SRCS:$(SRCS)"
	$(CC) $(CXXFLAGS) -o $@ $(SRCS)
	$(Q) echo "build success"

.PHONY : clean

clean:
	$(Q) rm $(TARGET) $(objects)
	$(Q) echo "clean"