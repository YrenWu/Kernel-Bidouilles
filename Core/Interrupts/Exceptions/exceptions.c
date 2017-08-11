

void zeroCallback(cpuSize_t registers);
void genericExceptionCallback(cpuSize_t registers);
void initExceptions();

void genericExceptionCallback(cpuSize_t registers)
{
	printColor("Exception triggered", BLACK, RED);
	printCat("Interrupt number : ");
	printDec(registers.interrupt);

	// if(registers.errorCode != 0){
	// 	printCat("Error code : ");
	// 	printDec(registers.errorCode);
	// }
}

void zeroCallback(cpuSize_t registers)
{
	printColor("Fault : division by zero", BLACK, RED);
}

void initExceptions()
{
	registerInterruptHandler(DIVIDE_ZERO, &zeroCallback);
	registerInterruptHandler(EXCEPT1, &genericExceptionCallback);
	registerInterruptHandler(EXCEPT2, &genericExceptionCallback);
	registerInterruptHandler(EXCEPT6, &genericExceptionCallback);
	registerInterruptHandler(EXCEPT7, &genericExceptionCallback);

	registerInterruptHandler(DOUBLE_FAULT, &genericExceptionCallback);
	registerInterruptHandler(PAGE_FAULT, &genericExceptionCallback);
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
