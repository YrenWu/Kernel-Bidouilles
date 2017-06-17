#include "Base/types.h"
#include "IO/io.c"
#include "IO/vga.c"
#include "IO/serial.c"

void kernel()
{
	
	// Display some messages
	printColor("Bonjour 0xDEADBABE", BROWN, CYAN);
	print("0_0");


	logSerial("It works !!!");
}
/**
 * TODO: 
 * - Set up GDT & IDT
 */

