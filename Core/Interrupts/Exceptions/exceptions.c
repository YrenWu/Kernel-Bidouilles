

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
	registerInterruptHandler(EXCEPT0, &zeroCallback);
	registerInterruptHandler(EXCEPT1, &genericExceptionCallback);
	registerInterruptHandler(EXCEPT2, &genericExceptionCallback);
	registerInterruptHandler(EXCEPT6, &genericExceptionCallback);
	registerInterruptHandler(EXCEPT7, &genericExceptionCallback);
}