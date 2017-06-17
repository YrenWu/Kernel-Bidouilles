/**  Global Descriptor Table Structure

	Offset 		Base Address 		Limit Address 		Privilege Level 	Type 	Segment
	0x00		0 (null descriptor) 0												NULL_DESCRIPTOR
	0x08		0x00000000			0xFFFFFFFF 			Ring 0 				RX 		CS_DESCRIPTOR
	0x10 		0x00000000			0xFFFFFFFF 			Ring 0 				RW 		DS_DESCRIPTOR

	Offset + 8 bits at each time
	DPL : Descriptor privilege level (ring level)
*/
#define NULL_DESCRIPTOR		0x00 // First descriptor (NULL)
#define CS_DESCRIPTOR		0x9A // Code Segment Descriptor
#define DS_DESCRIPTOR		0x92 // Data Segment Descriptor

/** Segments Types
	DS : Data Segment
	CS : Code segment
	R-O : Read-Only
	R-W : Read-Write
	R-X : Read-Execution
	X-O : Execute-Only
	EXP : Expand-Down
	A : Accessed
	C : Conforming
*/
#define DS_RO        		0x00 // Read-Only (R-O)
#define DS_ROA       		0x01 // R-O, accessed
#define DS_RW      			0x02 // Read/Write (R-W)
#define DS_RWA   			0x03 // R-W accessed
#define DS_RO_EXP    		0x04 // R-O, expand-down
#define DS_RO_EXPA		   	0x05 // R-O, expand-down, accessed
#define DS_RW_EXP  			0x06 // R-W expand-down
#define DS_RW_EXPA 			0x07 // R-W expand-down, accessed
#define CS_XO        		0x08 // Execute-Only (X-O)
#define CS_XO_A       		0x09 // X-O, accessed
#define CS_RX_RD      		0x0A // Execute/Read (R-X)
#define CS_RX_RDA     		0x0B // R-X, accessed
#define CS_XO_C       		0x0C // X-O, conforming
#define CS_XO_CA      		0x0D // X-O, conforming, accessed
#define CS_XO_RDC     		0x0E // R-X, conforming
#define CS_XO_RDCA    		0x0F // R-X, conforming, accessed


struct descriptor 
{
	uint16_t baseAddress;
	uint16_t limitAddress;
	unsigned int type;
} __attribute__((packed));

/*
GDT[0] = {.base=0, .limit=0, .type=NULL_DESCRIPTOR};
GDT[1] = {.base=0, .limit=0xffffffff, .type=CS_DESCRIPTOR};
GDT[2] = {.base=0, .limit=0xffffffff, .type=DS_DESCRIPTOR};*/
