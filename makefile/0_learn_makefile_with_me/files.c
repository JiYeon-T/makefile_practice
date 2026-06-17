#include <stdio.h>

#include "defs.h"
#include "files.h"
#include "buffer.h"
#include "command.h"


void files_test(void)
{
	printf("files module:%s ver:%d.%d\n\n", FILES_MODULE_NAME, FILES_MODULE_MAJOR_VER,
			FILES_MODULE_MINOR_VER);
	//buffer_test();
	command_test();
}


