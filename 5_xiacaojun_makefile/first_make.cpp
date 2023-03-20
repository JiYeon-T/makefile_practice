#include <iostream>
#include <thread>
#include "xdata.h"
#include "test.h"
#include <unistd.h>


using namespace std;

//main 线程入口函数
void ThreadMain()
{
	while(1) {
		std::cout << "ThreadMain(child thread) running." << std::endl;
		usleep(2 * 1000 * 1000);
	}
	return;
}

int main(int argc, char **argv)
{
	cout << "first_make(main thread) running..." << endl;

	thread th(ThreadMain);
	th.join();

	XDATA xdata;

	cout << "CONF_PATH:" << CONF_PATH << endl;

	return 0;
}
