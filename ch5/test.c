#include <stdio.h>

int main(void)
{

#if TEST_OPTION
	printf("main project,\r\nfile:%s", __FILE__);
#endif

	return 0;


}
