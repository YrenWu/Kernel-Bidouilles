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
#include "Core/Memory/pagination.c"
#include "Core/Interrupts/idtSetup.c"


void init();
void kernel(unsigned int ebx);
void timer();
void keyboard();


/*main.c
int main(struct multiboot *mboot_ptr)
{
   // Initialise all the ISRs and segmentation
   init_descriptor_tables();
   // Initialise the screen (by clearing it)
   monitor_clear();

   initialise_paging();
   monitor_write("Hello, paging world!\n");

   u32int *ptr = (u32int*)0xA0000000;
   u32int do_page_fault = *ptr;

   return 0;
} */

void kernel(unsigned int ebx){
	init();
	initMemPage();
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