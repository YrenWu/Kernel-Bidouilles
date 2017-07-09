
/* 
	Entry of Interrupt Descriptor Table

	Interrupt Handler
	31 . . . . . . . . . . . . . . 16 15 14 13 12 11 10 9 8 7 6 5| 4 3 2 1 0 |
	|		Offset High				|P | DPL |O |D | 1  1 0 0 0 0| reserved  |
	--------------------------------------------------------------------------
	|		Segment selector		|		Offset low	  				     |
	--------------------------------------------------------------------------	

	offset high : the 16 more significants bits of the 32 bits address in the segment
	offset low : the 16 less significants bits of the 32 bits address in the segment
	P : 1 if the handler is present in memory,  0 if not present
	DPL : Desciptor Privilege Level (0, 1, 2, 3)
	D : size of gate 0 = 16 bits, 1 = 32 bits
	segment selector: The offset in GDT
*/

void interruptHandler(cpuSize_t cpu, stackSize_t stack, uint8_t interrupt) {
	//noErrorCodeISR(0); 
}
