#include "Base/types.h"
#include "Base/devices.h"
#include "Base/descriptors.h"

#include "IO/vga.c"
#include "IO/serial.c"

#include "Memory/segmentation.c"

void kernel()
{
	gdtInit();

	// Display some messages
	printColor("Bonjour 0xDEADBABE", LIGHT_MAGENTA, MAGENTA);
	print("0_0");

	logSerial("It works !!!");
}
/**
 * TODO: 
 * - Set up IDT
 */

