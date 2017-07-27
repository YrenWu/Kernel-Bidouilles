#ifndef INTERRUPTS_H
#define INTERRUPTS_H

/*
 	interrupt gate structure (entry of IDT array)

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
struct idtEntry
{
   uint16_t offsetLow; 	// jump to this address when this interrupt start
   uint16_t segmentSelector;
   uint8_t  reserved;  	// must be zero (reserved + flags)
   uint8_t  flags;  	// P | DPL |O |D | 1  1 
   uint16_t offsetHigh; 
} __attribute__((packed));
typedef struct idtEntry idtEntry_t;

/*
	Pointer to IDT 
*/
struct idtPtr
{
	uint16_t lastAddress; 
	uint32_t firstAddress;
} __attribute__((packed));
typedef struct idtPtr idtPtr_t;

struct stateCPU
{
	uint32_t ds;

	/* source and destination indexes */
	uint32_t edi;
	uint32_t esi;
	
	/* base pointers */
	uint32_t ebp;
	uint32_t esp;

	/* general registers */
	uint32_t ebx;
	uint32_t edx;
	uint32_t ecx;
	uint32_t eax;

	uint32_t intNumber;
	uint32_t errorCode;
	uint32_t eip;
	uint32_t cs;
	uint32_t eflags;
	uint32_t useresp;
	/* segment registers */
	
	uint32_t ss;
	size_t es;
	size_t fs;
	size_t gs;

} __attribute__((packed));
typedef struct stateCPU cpuSize_t;


// set accessible assembly handlers in C code
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31(); 

#endif