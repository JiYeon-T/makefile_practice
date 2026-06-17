#include <stdio.h>

#include "defs.h"
#include "command.h"


void command_test(void)
{
	printf("command module:%s ver:%d.%d\n\n", COMMAND_MODULE_NAME, COMMAND_MODULE_MAJOR_VER,
			COMMAND_MODULE_MINOR_VER);

}


