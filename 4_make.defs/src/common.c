#include "common.h"

#include <stdio.h>


int common_test(char *content)
{
    printf("This is %s, content:%s\n", __func__, content);

    return 0;
}