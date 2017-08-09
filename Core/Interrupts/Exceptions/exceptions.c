

void zeroCallback(cpuSize_t registers);

void zeroCallback(cpuSize_t registers)
{
	printColor("Error : division by zero", BLACK, RED);
}

void initExceptions()
{
	registerInterruptHandler(EXCEPT0, &zeroCallback);
}
