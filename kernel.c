#include "Base/types.h"
#include "IO/io.c"
#include "IO/vga.c"
#include "IO/serial.c"

void kernel()
{
	initTerm(BLACK, WHITE);
	// Display some messages
	printColor("==================== YOP !!! ====================", WHITE, GREEN);
	print("Bonjour 0xDEADBABE");

	logSerial("kisfmh<sf<");
	logSerial("kisfmh<sf<");
	logSerial("kisfmh<sf<");
	logSerial("kisfmh<sf<");
	logSerial("\n");
}
/**
 * TODO: 
 * - Improve Serial 
 * - Set up GDT & IDT
 */

