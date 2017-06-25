/** Segments Types - 4 bits 0 to F
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

/* 	Segment Descriptor (Intel)
	31 . . . . . . 24 23 22 21 20 19 . . 16 15 14 13 12 11 . . 8 7 . . . . . . 0
	|	Base 31:24	| G |DB|L |AVL | SL   |P | DPL	 |S | Type |  Base 23:16   |
	----------------------------------------------------------------------------
	|		Base Address				  |		Segment Limit				   |
	----------------------------------------------------------------------------								
*/
struct segmentDescriptor 
{
	uint16_t segmentLimit; 		// 0 -> 15 bits 	Segment Limit (16)
	uint16_t baseAddress;		// 0 -> 15 bits 	Base Address (16)

	/* Lowest Dword */
	uint8_t baseLow; 			// 0 -> 7			Base 23:16 (8)
	uint8_t type:4; 			// 8 -> 11			Type : Segment Type (4) (0 to F)
	uint8_t	descriptorType:1;	/* bit 12			S descriptor type (1)
													0:system, 
													1: code or data */
	uint8_t privilegeLevel:2;	// bits 13, 14		DPL, Descriptor Privilege Level (2) (Ring 0 -> 3)	
	uint8_t segmentPresent:1;	// bit 15			P segment present (1)

	/* Highest Dword */
	uint8_t limit:4; 			// 16 -> 19 		SL Segment Limit 19:16 (4)
	uint8_t	available:1;		// bit 20			AVL available for use by system software (1)
	uint8_t	flag64b:1;			// bit 21			L  64-bits code segment (1:executed 64b, 0:32b)(1)				
	uint8_t	operationSize:1;	// bit 22			DB  Default Operation size (0:16bits, 1:32bits) (1)
	uint8_t	granularity:1;		// bit 23			G Granularity (1)
	uint8_t baseHigh; 			// 24 -> 31			Base 31:24 (8)
}  __attribute__ ((packed, aligned (8)));

/* 	Segment Selector 16 bits
	15 . . . . . . . . . 3 2 1 0
	|		index	     |T|RPL|
	----------------------------

	Index : select one of descriptor in GDT ot LDT
	T : Table Indicator (0: GDT, 1: LDT)
	RPL : Rquest Privilege Level
 */
struct segmentSelector 
{
	uint16_t index:12;	
	uint8_t	requestPrivilege:3;
	uint8_t tableIndicator:1;
}  __attribute__ ((packed, aligned (8)));