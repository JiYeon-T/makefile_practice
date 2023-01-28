/**
 * @fun: 移植库的时候 port 的接口
*/
#include "port_api.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


void* service_malloc(int size)
{
    return malloc(size);
}


void service_free(void *buff)
{
    free(buff);
    return;
}


// 可变参数的宏, 参数使用
// #define log_output(format, ...)     printf(format"", ##__VA_ARGS__)
// 这个 log 类似的可变参数的函数如何移植???
void log_output(char *format, ...)
{
    printf("第一个字母:%c\r\n", format[0]);
    return;
}