

test:
	g++ -c apple.cpp
	g++ -c apple.cpp  AppleWrapper.cpp
	gcc test.c -o test AppleWrapper.o apple.o -lstdc++


.PHONY : clean


clean:
	rm -rf *.o test

