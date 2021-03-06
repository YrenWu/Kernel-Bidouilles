void genericExceptionCallback(cpuSize_t registers);
void initExceptions();
void pageFaultCallback(cpuSize_t registers);

void pageFaultCallback(cpuSize_t registers)
{
	printColor("PAGE FAULT", BLACK, GREEN);
	debug(registers);
	/* 
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

	/*  Address who triggered the fault is in CR2 :
		- end of the program (error Segmentation Fault)
		- load temporary memory on a swap area (on hard drive)
		- allocate frame page
	*/
}

void genericExceptionCallback(cpuSize_t registers)
{
	printColor("Exception triggered", BLACK, RED);
	printCat("Interrupt number : ");
	printDec(registers.interrupt);

	char * errorMessages[] = {
		"Divide by zero (Fault)",
		"Debug (Fault/Trap)",
		"Non-maskable interrupt (Interrupt)",
		"Breakpoint (Trap)",
		"Overflow (Trap)",
		"Bound range Exceeded (Trap)",
		"Invalid opcode (Fault)",
		"Device not available (Fault)",
		"Double fault (Abort) code 0",
		"Coprocessor Segment Overun (Fault)",
		"Invalid TSS (Fault)",
		"Segment not present (Fault)",
		"Stack segment fault (Fault)",
		"General protection fault (Fault)",
		"Page fault (Fault)",
		"Unknown interrupt exception",
		"Floating Point exception (Fault)",
		"Alignment check (Fault)",
		"Machine check (Abort)",
		"SIMD Floating Point Exception(Fault)",
		"Virtualization exception (Fault)",
	};

	if(registers.interrupt < 21) {
		print(errorMessages[registers.interrupt]);
	} else if((registers.interrupt >= 21 && registers.interrupt < 30) || registers.interrupt == 31) {
		print("Reserved");
	} else if(registers.interrupt == 30 ){
		print("Security Exception");
	} else {
		printCat("Unregistered interrupt, please check for interrupt number : ");
		printDec(registers.interrupt);
	}

	if(registers.errorCode != 0){
		print("");
		printCat("Error code : ");
		printDec(registers.errorCode);
	}
}

void initExceptions()
{
	registerInterruptHandler(DIVIDE_ZERO, &genericExceptionCallback); // 0

	registerInterruptHandler(EXCEPT1, &genericExceptionCallback);
	registerInterruptHandler(EXCEPT2, &genericExceptionCallback);
	registerInterruptHandler(EXCEPT3, &genericExceptionCallback);
	registerInterruptHandler(EXCEPT4, &genericExceptionCallback);
	registerInterruptHandler(EXCEPT5, &genericExceptionCallback);
	registerInterruptHandler(EXCEPT6, &genericExceptionCallback);
	registerInterruptHandler(EXCEPT7, &genericExceptionCallback);

	registerInterruptHandler(DOUBLE_FAULT, &genericExceptionCallback); // 8 

	registerInterruptHandler(EXCEPT9, &genericExceptionCallback);
	registerInterruptHandler(EXCEPT10, &genericExceptionCallback);
	registerInterruptHandler(EXCEPT11, &genericExceptionCallback);
	registerInterruptHandler(EXCEPT12, &genericExceptionCallback);
	registerInterruptHandler(EXCEPT13, &genericExceptionCallback);

	registerInterruptHandler(PAGE_FAULT, &pageFaultCallback); // 14

	registerInterruptHandler(EXCEPT15, &genericExceptionCallback);
	registerInterruptHandler(EXCEPT16, &genericExceptionCallback);
	registerInterruptHandler(EXCEPT17, &genericExceptionCallback);
	registerInterruptHandler(EXCEPT18, &genericExceptionCallback);
	registerInterruptHandler(EXCEPT19, &genericExceptionCallback);
	registerInterruptHandler(EXCEPT20, &genericExceptionCallback);

	registerInterruptHandler(EXCEPT30, &genericExceptionCallback);
	registerInterruptHandler(EXCEPT31, &genericExceptionCallback);
}
