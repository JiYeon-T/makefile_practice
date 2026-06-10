#include <iostream>
// 编译时会在 ${PROJECT_BIN_DIR} 目录下生成 "TutorialConfig.h" 文件
#include "TutorialConfig.h"

using namespace std;

int main(int argc, char *argv[])
{
    char input;

    // cout << "Compile DATE: " << Tutorial_COMPILE_DATE_H << endl;
    // cout << "Compile AUTH: " << Tutorila_COMPILE_AUTH_H << endl;

    std::cout << "This is a main.cpp." << std::endl;
    for (int ix = 0; ix < argc; ++ix) {
        std::cout << "argv[" << ix << "]:" << argv[ix] << std::endl;
    }

#if (Tutorial_VERSION_MAJOR_H == 3) && (Tutorial_VERSION_MINOR_H == 2)
    cout << "从 TutorialConfig.h.in 生成的头文件传入的版本号:"
         << Tutorial_VERSION_MAJOR_H << "."
         << Tutorial_VERSION_MINOR_H << endl;
#else
    cout << "使用默认版本号:0.0.1" << endl;
#endif

    // 通过这里判断
    // printf("%d\n", Tutorial_VERSION_MAJOR_H);
    // printf("%s\n", Tutorial_VERSION_MAJOR_H);
    printf("date:%d\n", Tutorial_COMPILE_DATE_INT);
    printf("date:%s\n", Tutorial_COMPILE_DATE_STR);


    //print_something()

    return 0;
}