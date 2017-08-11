
#include "Base/Types/types.h"
#include "Base/Structures/devices.h"
#include "Base/Structures/descriptors.h"
#include "Base/Structures/interrupts.h"
#include "Base/Functions/Prototypes/isr.h"

#include "Base/Functions/display.c"	// base printing and debug Functions

#include "Core/Interrupts/PIC/pic8259.c"
#include "Core/Interrupts/PIC/pit8254.c"
#include "Core/Interrupts/PIC/kb8042.c"
#include "Core/Interrupts/Exceptions/exceptions.c"

#include "Core/IO/vga.c"
#include "Core/IO/serial.c"
#include "Core/Memory/gdtSetup.c"
#include "Core/Interrupts/idtSetup.c"


void kernel(unsigned int ebx){

	gdtInit();
	idtInit();
	initTerm(BLACK, MAGENTA);
	initTimer(5);
	initExceptions();
	initKeyboard();
	
	logSerial("It works !!!");

	asm volatile ("int $32");
}
