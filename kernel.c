#include "Base/types.h"
#include "Base/devices.h"
#include "Memory/structGDT.h"

#include "IO/io.c"
#include "IO/vga.c"
#include "IO/serial.c"

#include "Memory/segmentation.c"

void kernel()
{
	// Display some messages
	printColor("Bonjour 0xDEADBABE", LIGHT_MAGENTA, MAGENTA);
	print("0_0");

	logSerial("It works !!!");
	gdtInit();
}
/**
 * TODO: 
 * - Set up IDT
 */

