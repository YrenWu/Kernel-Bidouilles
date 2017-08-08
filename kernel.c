#include "Base/types.h"
#include "Base/devices.h"
#include "Base/descriptors.h"
#include "Base/interrupts.h"

#include "IO/vga.c"
#include "IO/serial.c"

#include "Memory/gdtSetup.c"
#include "Interrupts/PIC/commonPics.c"
#include "Interrupts/idtSetup.c"


void kernel()
{
	gdtInit();
	idtInit();
	
	logSerial("It works !!!");
	asm volatile ("int $34");
}


