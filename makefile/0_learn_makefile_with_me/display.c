#include <stdio.h>

#include "defs.h"
#include "display.h"
#include "buffer.h"


void display_test(void)
{
	printf("display module:%s ver:%d.%d\n\n", DISPLAY_MODULE_NAME, DISPLAY_MODULE_MAJOR_VER,
			DISPLAY_MODULE_MINOR_VER);

}


