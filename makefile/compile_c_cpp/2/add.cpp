#include <iostream>

//调用 c++ 重载函数
//C 不支持重载, 所以需要对重载函数进行接口封装, 使用 extern "C" 是要告诉编译器,按照 C 的方式来编译封装接口, 接口里面的函数还是按照 C++ 的语法 和 方式来编译.

//重载
int add(int a, int b)
{
	std::cout << "a+b=" << a+b << std::endl;
	return a + b;
}

int add(char c)
{
	std::cout << "c=" << c << std::endl;
	return 0;
}


//使用 C 对接口进行封装
//下面两个函数供 C 程序调用, 自然需要 C 方式进行编译;
//而这两个函数的实现体可以取调用 C++ 的重载函数
extern "C" int add_ii(int a, int b)
{
	//调用 C++
	return add(a, b);
}

extern "C" int add_c(char c)
{
	return add(c);
}












