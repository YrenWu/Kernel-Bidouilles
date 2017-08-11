

void zeroCallback(cpuSize_t registers);
void genericExceptionCallback(cpuSize_t registers);
void initExceptions();
void pageFaultCallback(cpuSize_t registers);

void genericExceptionCallback(cpuSize_t registers)
{
	printColor("Exception triggered", BLACK, RED);
	printCat("Interrupt number : ");
	printDec(registers.interrupt);

	switch(registers.interrupt) {
		case(1):
			print("Debug (Fault/Trap)");
			break;
		case(2):
			print("Non-maskable interrupt (Interrupt)");
			break;
		case(3):
			print("Breakpoint (Trap)");
			break;
		case(4):
			print("Overflow (Trap)");
			break;
		case(5):
			print("Bound range Exceeded (Trap)");
			break;
		case(6):
			print("Invalid opcode (Fault)");
			break;
		case(7):
			print("Device not available (Fault)");
			break;
		case(8):
			print("Double fault (Abort) code 0");
			break;
		case(9):
			print("Coprocessor Segment Overun (Fault)");
			break;
		case(10):
			print("Invalid TSS (Fault)");
			break;
		case(11):
			print("Segment not present (Fault)");
			break;
		case(12):
			print("Stack segment fault (Fault)");
			break;
		// 13   # 0xD Genreal protection fault  		FAULT
		// 14   # 0xE Page fault                		FAULT
		// 15   # 0xF  Unknown interrupt exception 
		// 16   # 0x10 Floating Point exception 		FAULT
		// 17   # 0x11 Alignment check          		FAULT
		// 18   # 0x12 Machine check            		ABORT
		// 19   # 0x13 SIMD Floating Point Exception 	FAULT  
		// 20   # 0x14 Virtualization exception 		FAULT
		// 21-29 # 0x15-0x1D Reserved 
		// 30   # 0x1E Security Exception       
		// 31   # 0x1F Reserved
	}

	// if(registers.errorCode != 0){
	// 	printCat("Error code : ");
	// 	printDec(registers.errorCode);
	// }
}

void pageFaultCallback(cpuSize_t registers)
{
	printColor("PAGE FAULT", BLACK, RED);
}

void doubleFaultCallback(cpuSize_t registers)
{
	printColor("DOUBLE FAULT", BLACK, GREEN);
}


void zeroCallback(cpuSize_t registers)
{
	printColor("Fault : division by zero", BLACK, RED);
}

void initExceptions()
{
	registerInterruptHandler(DIVIDE_ZERO, &zeroCallback); 			// 0

	registerInterruptHandler(EXCEPT1, &genericExceptionCallback);
	registerInterruptHandler(EXCEPT2, &genericExceptionCallback);
	registerInterruptHandler(EXCEPT3, &genericExceptionCallback);
	registerInterruptHandler(EXCEPT4, &genericExceptionCallback);
	registerInterruptHandler(EXCEPT5, &genericExceptionCallback);
	registerInterruptHandler(EXCEPT6, &genericExceptionCallback);
	registerInterruptHandler(EXCEPT7, &genericExceptionCallback);

	registerInterruptHandler(DOUBLE_FAULT, &doubleFaultCallback);	// 8 

	registerInterruptHandler(EXCEPT9, &genericExceptionCallback);
	registerInterruptHandler(EXCEPT10, &genericExceptionCallback);
	registerInterruptHandler(EXCEPT11, &genericExceptionCallback);
	registerInterruptHandler(EXCEPT12, &genericExceptionCallback);
	registerInterruptHandler(EXCEPT13, &genericExceptionCallback);

	registerInterruptHandler(PAGE_FAULT, &pageFaultCallback);		// 14

	registerInterruptHandler(EXCEPT15, &genericExceptionCallback);
	registerInterruptHandler(EXCEPT16, &genericExceptionCallback);
	registerInterruptHandler(EXCEPT17, &genericExceptionCallback);
	registerInterruptHandler(EXCEPT18, &genericExceptionCallback);
	registerInterruptHandler(EXCEPT19, &genericExceptionCallback);
	registerInterruptHandler(EXCEPT20, &genericExceptionCallback);
}
/* Page fault Error code
Bit 0
    If set, the fault was not because the page wasn't present. If unset, the page wasn't present.
Bit 1
    If set, the operation that caused the fault was a write, else it was a read.
Bit 2
    If set, the processor was running in user-mode when it was interrupted. Else, it was running in kernel-mode.
Bit 3
    If set, the fault was caused by reserved bits being overwritten.
Bit 4
    If set, the fault occurred during an instruction fetch. 

    Address which cause the fault in CR2 


    US RW  P - Description
0  0  0 - Supervisory process tried to read a non-present page entry
0  0  1 - Supervisory process tried to read a page and caused a protection fault
0  1  0 - Supervisory process tried to write to a non-present page entry
0  1  1 - Supervisory process tried to write a page and caused a protection fault
1  0  0 - User process tried to read a non-present page entry
1  0  1 - User process tried to read a page and caused a protection fault
1  1  0 - User process tried to write to a non-present page entry
1  1  1 - User process tried to write a page and caused a protection fault

*/
