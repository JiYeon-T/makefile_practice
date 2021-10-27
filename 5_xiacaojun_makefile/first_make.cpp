#include <iostream>
#include <thread>
#include "xdata.h"
//#include "test.h"

using namespace std;

//main 线程入口函数
void ThreadMain()
{
	std::cout << "ThreadMain running." << std::endl;
	return;
}

int main(int argc, char **argv)
{
	cout << "first_make running..." << endl;

	thread th(ThreadMain);
	th.join();

	XDATA xdata;

	return 0;
}
