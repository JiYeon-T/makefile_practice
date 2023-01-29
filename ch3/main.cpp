#include <iostream>
#include "test.h"
#include "math_add.h"
#include "math_sub.h"
#include "math_div.h"
#include "math_mul.h"
#include "ch3Configure.h"

using namespace std;

int main(int argc, char *argv[])
{
    std::cout << "This is a main.cpp." << std::endl;
    for(int ix = 0; ix < argc; ++ix){
        std::cout << "argv[" << ix << "]:" <<argv[ix] << std::endl;
    }

    print_something();

    int a = 1, b = 2;
    cout << "result:" << my_add(a, b) << ", "
         << my_sub(a, b) << ", "
         << my_mul(a, b) << ", "
         << my_div(a, b) << endl;

    return 0;
}