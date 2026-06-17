#include <stdio.h>

//调用方法:
//g++ -c Person.cpp
//g++ -c Wrapper.cpp
//gcc Person.o Wrapper.o main.c -lstdc++
//NOTE: 出现很多奇奇怪怪的错误的原因是没有动态链接 c++ 的库
 

int main()
{
	void *p = call_Person_Create();
	int age = call_Person_GetAge(p);
	const char *name = call_Person_GetName(p);
	call_Person_Destroy(p);
	printf("name=%s, age=%d\r\n", name, age);





	return 0;
}
