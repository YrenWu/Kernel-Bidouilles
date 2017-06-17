#include "Base/types.h"
#include "Base/devices.h"
#include "IO/io.c"
#include "IO/vga.c"
#include "IO/serial.c"

void kernel()
{

	// Display some messages
	printColor("Bonjour 0xDEADBABE", LIGHT_MAGENTA, MAGENTA);
	print("0_0");

	logSerial("It works !!!");
}
/**
 * TODO: 
 * - Set up GDT & IDT
 */

