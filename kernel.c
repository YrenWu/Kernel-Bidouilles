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


void init();
void kernel(unsigned int ebx);
void timer();
void keyboard();

void kernel(unsigned int ebx){
	init();
	asm volatile ("int $31");
	// Interrupt with error code : 8, 10 11, 12, 13, 14, 17, 30
}

void init() 
{
	gdtInit();
	idtInit();
	initTerm(BLACK, MAGENTA);
	initExceptions();
	initKeyboard();
	logSerial("Boot");
}

void keyboard()
{
	asm volatile ("int $33");
}

void timer()
{
	initTimer(50);
	asm volatile ("int $32");
	asm volatile ("int $32");
	asm volatile ("int $32");
	asm volatile ("int $32");
	asm volatile ("int $32");
	printTimer();
}