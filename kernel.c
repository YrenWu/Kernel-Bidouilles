#include "Base/types.h"
#include "Base/devices.h"
#include "Base/descriptors.h"
#include "Base/interrupts.h"

#include "IO/vga.c"
#include "IO/serial.c"

#include "Memory/gdtSetup.c"
#include "Interrupts/idtSetup.c"

void kernel()
{
	gdtInit();
	idtInit();

	// Display some messages
	printColor("Bonjour 0xDEADBABE", LIGHT_MAGENTA, MAGENTA);
	print("0_0");

	//logSerial("It works !!!");
	asm volatile ("int $0x3");
}

/**
 * TODO: 
 * - debug 
 * - Exceptions, IRQ, PIC
 */

