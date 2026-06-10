#ifndef __PUBLIC_H__
#define __PUBLIC_H__

/*******************
 * DECLARATION
 *******************/
// 使用库文件的用户需要实现的 port 的接口
void* service_malloc(int size);
void service_free(void *buff);
void log_output(char *format, ...);


/**
 * @fun: 使用 port 的接口测试
 * @param:
 * @ret:
*/
void port_test_fun();

#endif