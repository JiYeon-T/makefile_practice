
#include "print_hello.h"

#include <stdio.h>
#include <stdlib.h>


void print_hello()
{
    printf("This is print_hello.c\r\n");
    printf("[%s:%d] %s\r\n", __FILE__, __LINE__, __func__);
    printf("This is print_hello.c end\r\n");

    return;
}