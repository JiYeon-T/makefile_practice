/**
 * @file: 公用库文件
*/
#include "public.h"

#include <stdio.h>
#include <stdlib.h>


void print_some_test_info()
{
    // printf("This is a static lib test\r\n");
    printf("This is a dynamic lib test\r\n");
    printf("[%s:%d] %s\r\n", __FILE__, __LINE__, __func__);
    // printf("This is a static lib test end\r\n");
    printf("This is a dynamic lib test end\r\n");

    return;
}