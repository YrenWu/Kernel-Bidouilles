#include "Prototypes/display.h"

/*
	Print CPU register content on screen and  interrupt number and error code

	@param cpu The CPU structure with registers (from the stack)
*/
void debug(cpuSize_t cpu) {

	printColor("-----------------------------------------------", BLACK, RED);
	printColor("------------------ CPU state ------------------", BLACK, RED);
	print("-------------- General registers --------------");
	printCat("| EAX : ");
	printHex(cpu.eax);
	printCat("| EBX : ");
	printHex(cpu.ebx);
	printCat("| ECX : ");
	printHex(cpu.ecx);
	printCat("| EDX : ");
	printHex(cpu.edx);
	print("");
	print("");
	print("-------------- Segment registers --------------");
	printCat("| GS : ");
	printHex(cpu.gs);
	printCat("| FS : ");
	printHex(cpu.fs);
	printCat("| ES : ");
	printHex(cpu.es);
	printCat("| DS : ");
	printHex(cpu.ds);
	print("");
	print("");
	print("-------------- Pointer registers --------------");
	printCat("| EBP : ");
	printHex(cpu.ebp);
	printCat("| ESP : ");
	printHex(cpu.esp);
	print("");
	print("");
	print("--------------- Index registers ---------------");
	printCat("| ESI : ");
	printHex(cpu.esi);
	printCat("| EDI : ");
	printHex(cpu.edi);
	print("");
	print("");
	printColor("Error Code", RED, BLACK);
	printDec(cpu.errorCode);
	print("");
	printColor("Interrupt Triggered", RED, BLACK);
	printDec(cpu.interrupt);
	print("");
}
