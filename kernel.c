#include "Base/Types/types.h"
#include "Base/Structures/devices.h"
#include "Base/Structures/descriptors.h"
#include "Base/Structures/interrupts.h"
#include "Base/Functions/display.c"	// base printing and debug functions

#include "Core/IO/vga.c"
#include "Core/IO/serial.c"
#include "Core/Memory/gdtSetup.c"
#include "Core/Interrupts/PIC/commonPics.c"
#include "Core/Interrupts/idtSetup.c"


void kernel()
{
	gdtInit();
	idtInit();
	
	logSerial("It works !!!");
	asm volatile ("int $3");
}


