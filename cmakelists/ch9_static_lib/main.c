#include <stdio.h>
#include <stdint.h>
#include "opus_encode.h"
#include "opus_decode.h"

int main(int argc, char *argv[])
{
    uint8_t arr[10] = {1, 2, 3};    
    printf("hello, world.\n");
    opus_encode(arr, 10);
    opus_decode(arr, 10);
    
    return 0;
}