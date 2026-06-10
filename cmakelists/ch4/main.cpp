#include <iostream>

#include "math_test.h""
#include "ulog_test.h"


using namespace std;

int main(int argc, char *argv[])
{
	for(int ix = 0; ix < argc; ++ix){
		cout << argv[ix] << endl;
	}
	cout << "This is a sub cmakelist.txt test" << endl;


	ulog_module_test_function();
	math_module_test_function();

	return 0;

}
