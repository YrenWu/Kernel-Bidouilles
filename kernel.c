#include "Base/types.h"
#include "IO/io.c"
#include "IO/vga.c"
#include "IO/serial.c"

void kernel()
{
	
	// Display some messages
	print("Yop");
	printColor("Bonjour 0xDEADBABE", BROWN, CYAN);


	logSerial("It works !!!");
}
/**
 * TODO: 
 * - Set up GDT & IDT
 */

