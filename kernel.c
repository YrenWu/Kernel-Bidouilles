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

	initSerial(COM1_ADDR, 2);
	writeCharSerial('r', COM1_ADDR);
	writeSerial("eadonly", COM1_ADDR);
}
/**
 * TODO: 
 * - Improve Serial 
 * - Set up GDT & IDT
 */

