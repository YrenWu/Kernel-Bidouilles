/**  Global Descriptor Table Structure

ID	Offset 		Base Address 		Limit Address 		Privilege Level 	Type 	Segment 				
0	0x00 (0)	0 (null descriptor) 0					0					0		NULL_DESCRIPTOR			Null
1	0x08 (8)	0x00000000			0xFFFFFFFF 			Ring 0 (kernel)		RX 		CS_DESCRIPTOR_PL0		Code
2	0x10 (16)	0x00000000			0xFFFFFFFF 			Ring 0 (kernel)		RW 		DS_DESCRIPTOR_PL0		Data
3	0x18 (24)	0x00000000			0xFFFFFFFF 			Ring 3 (user)		RX		CS_DESCRIPTOR_PL3		Code
4	0x20 (32)	0x00000000			0xFFFFFFFF 			Ring 3 (user)		RW		DS_DESCRIPTOR_PL3		Data

	Offset + 8 bits at each time
	DPL : Descriptor privilege level (ring level)

	OPERATIONS :
	1 segment selector (CS, DS) tells in which table (LDT, GDT)
	2 fetch segment descriptor in the specified table (GDT or LDT) 
	3 make linear address with base + offset 

*/

#define NULL_DESCRIPTOR		0x00 // First descriptor (NULL)
#define CS_DESCRIPTOR_PL0	0x9A // Code Segment Descriptor
#define DS_DESCRIPTOR_PL0	0x92 // Data Segment Descriptor
#define CS_DESCRIPTOR_PL3 	0xFA
#define DS_DESCRIPTOR_PL3	0xF2
#define GRANULARITY 		0xCF

#define DEFAULT_BASE		0x00000000
#define DEFAULT_LIMIT 		0xFFFFFFFF

extern void gdtFlush();

gdtEntry_t gdt[5];
gdtPtr_t   ptrGdt;

static void setEntry(uint32_t i, uint32_t base, uint32_t limit, uint8_t pl, uint8_t granularity)
{
	gdt[i].baseLow 		= (base & 0xFFFF);
	gdt[i].baseMiddle 	= (base >> 16) & 0xFF;
	gdt[i].baseHigh 	= (base >> 24) & 0xFF;

	gdt[i].limitLow  	= (limit & 0xFFFF);

	gdt[i].granularity 	= (limit >> 16) & 0x0F;
	gdt[i].granularity |= granularity & 0xF0;

	gdt[i].privilege 	= pl;
}


static void gdtInit()
{
	ptrGdt.lastAddress = (sizeof(gdtEntry_t) * 5) - 1;
    ptrGdt.firstAddress = (int)&gdt;

    setEntry(0, DEFAULT_BASE, 0, NULL_DESCRIPTOR, 0);  						  // Null descriptor
    setEntry(1, DEFAULT_BASE, DEFAULT_LIMIT, CS_DESCRIPTOR_PL0, GRANULARITY); // Code segment
    setEntry(2, DEFAULT_BASE, DEFAULT_LIMIT, DS_DESCRIPTOR_PL0, GRANULARITY); // Data segment
    setEntry(3, DEFAULT_BASE, DEFAULT_LIMIT, CS_DESCRIPTOR_PL3, GRANULARITY); // User mode code segment
    setEntry(4, DEFAULT_BASE, DEFAULT_LIMIT, DS_DESCRIPTOR_PL3, GRANULARITY); // User mode data segment

    gdtFlush();
}

