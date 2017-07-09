#include "Base/types.h"
#include "Base/devices.h"
#include "Base/descriptors.h"
#include "Base/interrupts.h"

#include "IO/vga.c"
#include "IO/serial.c"

#include "Memory/segmentation.c"
#include "Interrupts/handler.c"

void kernel()
{
	gdtInit();

	// Display some messages
	printColor("Bonjour 0xDEADBABE", LIGHT_MAGENTA, MAGENTA);
	print("0_0");

	logSerial("It works !!!");
}

// void initialize()
// {
// 	gdtInit(); // set up GDT and memory segmentation
// 	// set up IDT and interruptions

// }
/**
 * TODO: 
 * - Set up IDT
 * - Exceptions, IRQ, PIC
 */

