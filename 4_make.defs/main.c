#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "module1.h"
#include "module2.h"
#include "module3.h"


// 每个源文件的文件夹下编写一个用来获取源文件的文件 Make.defs


int main(int argc, char * argv[])
{
    if(argc < 1) {
        printf("error\n");
        return -1;
    }
    printf("Hello, world\r\n");

    // common_test(argv[0]);
    print_module1_1_info(NULL);
    print_module1_2_info(NULL);
    print_module1_3_info(NULL);

    return 0;
}