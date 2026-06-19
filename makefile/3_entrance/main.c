#include <stdio.h>
#include <stdlib.h>
#include "tool.h"

int main()
{
    printf("Hello, world\n%s() was called.\n", __func__);

    PrintSomething();
    PrintSomething();
    PrintSomething();
    return 0;
}