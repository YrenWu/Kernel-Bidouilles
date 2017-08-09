
#include "Base/Types/types.h"
#include "Base/Structures/devices.h"
#include "Base/Structures/descriptors.h"
#include "Base/Structures/interrupts.h"
#include "Base/Functions/Prototypes/isr.h"

#include "Base/Functions/display.c"	// base printing and debug Functions

#include "Core/Interrupts/PIC/pit8254.c"
#include "Core/Interrupts/Exceptions/exceptions.c"

#include "Core/IO/vga.c"
#include "Core/IO/serial.c"
#include "Core/Memory/gdtSetup.c"
#include "Core/Interrupts/commonPics.c"
#include "Core/Interrupts/idtSetup.c"


void kernel()
{
	gdtInit();
	idtInit();
	initTerm(BLACK, MAGENTA);
	initTimer(50);
	initExceptions();
	
	logSerial("It works !!!");
	asm volatile ("int $0");
}


