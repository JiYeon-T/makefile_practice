#include <iostream>
#include "test.h"
#include "mymath.h"

using namespace std;

int main(int argc, char *argv[])
{
    std::cout << "This is a main.cpp." << std::endl;
    for(int ix = 0; ix < argc; ++ix){
        std::cout << ix << ":" <<argv[ix] << std::endl;
    }

    print_something();
    
    cout << "static library:" << my_add(1, 2) << endl;
    cout << "static library:" << my_sub(1, 2) << endl;
    cout << "static library:" << my_mul(1, 2) << endl;
    cout << "static library:" << my_div(1, 2) << endl;
    
    return 0;
}