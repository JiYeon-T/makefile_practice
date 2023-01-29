#include <stdint.h>
#include <stdio.h>

void opus_decode(uint8_t *p_data, uint16_t len)
{
    printf("Decode data len:%d\n", len);
    return;
}

// service_malloc 以及 service_free 如何实现移植 
// 增加一个中间层