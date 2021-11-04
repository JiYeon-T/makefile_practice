#include <stdio.h>
#include "add.h"
//C 调用 C++的普通函数:
//g++ -c add.cpp
//gcc add.o main.c -lstdc++
int main()
{
	add(1, 2);

	return 0;
}
