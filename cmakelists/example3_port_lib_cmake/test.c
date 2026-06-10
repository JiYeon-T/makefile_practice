#include <stdio.h>
#include <stdlib.h>

// #include "./lib/public.h"
#include "public.h"


int main(int argc, char *argv[])
{
    printf("hello world start\r\n");
    port_test_fun();
    printf("hello world end\r\n");

    return 0;
}