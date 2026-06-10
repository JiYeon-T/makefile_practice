/**
 * @file: 公用库文件
*/
#include "public.h"


/*******************
 * MACRO
 *******************/
#define MALLOC_SIZE     100


/*******************
 * DECLARATION
 *******************/
// 库文件给外界 port 接口的方式, 只需要声明函数即可
void* service_malloc(int size);
void service_free(void *buff);
void log_output(char *format, ...);


/**
 * @fun: 如何使用引用库文件的用户 port 的接口
 *       例如:malloc(), free()
*/
void port_test_fun()
{
    char *buff = (char*)0;

    log_output("port test start\r\n");

    buff = (char*)service_malloc(100);
    if(!buff) {
        log_output("malloc failed\r\n");
        return;
    }

    for(int ix = 0; ix < MALLOC_SIZE; ++ix) {
        buff[ix] = ix;
        log_output("%d ", buff[ix]);
    }

    service_free(buff);

    log_output("port test end\r\n");

    return;
}

