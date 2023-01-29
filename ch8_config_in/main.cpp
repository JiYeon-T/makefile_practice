#include <iostream>

// 为什么找不到头文件, 添加了文件路径没用 ?/?/
// #include "TutorialConfig.h"
#include "build/TutorialConfig.h"

#ifdef USE_MYMATH
    #include "MathFunctions.h"
#else
    #include <cmath>
#endif



using namespace std;


int main(int argc, char *argv[])
{
    cout << "VERSION:" << Tutorial_VERSION_MAJOR << "." << Tutorial_VERSION_MINOR << endl;

    double num = 5;
    double result;

    cout << "Enter a number" << endl;;

    // cin << num;
    // 在自己的源代码中通过宏的方式决定使用哪个函数
    // 宏可以在 TutorialConfig.h.in 中 或者 CMakeLists 中 或者 头文件中
#ifdef USE_MYMATH
    result = sqrt(num); 
#else
    result = sqrt(num); 
#endif
    cout << "result:" << result << endl;

    return 0;
}