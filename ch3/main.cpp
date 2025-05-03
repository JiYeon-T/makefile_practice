#include <iostream>
#include "test.h"
#include "math_add.h"
#include "math_sub.h"
#include "math_div.h"
#include "math_mul.h"
#include "america_history.h"
#include "Ch3Configure.h"

using namespace std;

int main(int argc, char *argv[])
{
    std::cout << "This is a main.cpp." << std::endl;
    for(int ix = 0; ix < argc; ++ix){
        std::cout << "argv[" << ix << "]:" <<argv[ix] << std::endl;
    }

    print_something();

    cout << "static library api:1+2=" << my_add(1, 2) << endl;
    cout << "static library api:1-2=" << my_sub(1, 2) << endl;
    cout << "static library api:1*2=" << my_mul(1, 2) << endl;
    cout << "static library api:1/2=" << my_div(1, 2) << endl;

    america_history_init();
    america_history_deinit();

    return 0;
}