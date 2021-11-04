#include <stdio.h>
#include "add.h"
//C 调用 C++的普通函数:
//g++ -c add.cpp
//gcc add.o main.c -lstdc++
int main()
{
	add_ii(1, 2);
	add_c('a');

	return 0;
}
