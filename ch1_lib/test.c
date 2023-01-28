#include <stdio.h>
#include <stdlib.h>

#include "public.h"
#include "print_hello.h"


int main(int argc, char *argv[])
{
    printf("hello, world.\r\n");

    print_some_test_info();
    print_hello();


    return 0;
}