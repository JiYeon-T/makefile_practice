#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	for(int ix = 0; ix < argc; ++ix){
		cout << argv[ix] << endl;
	}

	return 0;

}
