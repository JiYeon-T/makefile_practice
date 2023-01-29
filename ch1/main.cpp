#include <iostream>
#include "TutorialConfig.h" // 编译时会在 ${PROJECT_BIN_DIR} 目录下生成 "TutorialConfig.h" 文件

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Compile DATE: " << Tutorial_COMPILE_DATE << endl;
    cout << "Compile AUTH: " << Tutorila_COMPILE_AUTH << endl;

    std::cout << "This is a main.cpp." << std::endl;
    for(int ix = 0; ix < argc; ++ix){
        std::cout << "argv[" << ix << "]:" << argv[ix] << std::endl;
    }

    cout << "从 TutorialConfig.h.in 生成的头文件传入的版本号:"
         << Tutorial_VERSION_MAJOR << "."
         << Tutorial_VERSION_MINOR << endl; 

    //print_something()
    return 0;
}