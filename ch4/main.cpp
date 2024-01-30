#include <iostream>
#include "third_party/math/math_test.h""
#include "third_party/ulog/ulog_test.h"


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
