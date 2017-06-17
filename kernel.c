#include "Base/types.h"
#include "IO/io.c"
#include "IO/vga.c"
#include "IO/serial.c"

void kernel()
{
	initTerm(BLACK, WHITE);
	// Display some messages
	print("Bonjour 0xDEADBABE");

	logSerial("kisfmh<sf<");
	logSerial("kisfmh<sf<");
	logSerial("kisfmh<sf<");
	logSerial("kisfmh<sf<");
	logSerial("\n");
}
/**
 * TODO: 
 * - Set up GDT & IDT
 */

