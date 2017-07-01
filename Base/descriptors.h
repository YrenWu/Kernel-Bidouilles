#ifndef DESCRIPTORS_H
#define DESCRIPTORS_H

/*
	Entry of Global Descriptor Table

	Segment Descriptor (Intel)
	31 . . . . . . 24 23 22 21 20 19 . . 16 15 14 13 12 11 . . 8 7 . . . . . . 0
	|	Base 31:24	| G |DB|L |AVL | SL   |P | DPL	 |S | Type |  Base 23:16   |
	----------------------------------------------------------------------------
	|		Base Address				  |		Segment Limit				   |
	----------------------------------------------------------------------------								
*/
struct gdtEntry
{
   uint16_t limitLow;           
   uint16_t baseLow;

   uint8_t baseMiddle;                 
   uint8_t privilege;              // Access flags, determine what ring this segment can be used in.
   uint8_t granularity;      
   uint8_t baseHigh;

} __attribute__((packed));
typedef struct gdtEntry gdtEntry_t; 

/*
	Pointer to GDT Address
*/
struct gdtPtr
{
	uint16_t lastAddress;
	uint32_t firstAddress;

} __attribute__((packed));
typedef struct gdtPtr gdtPtr_t; 

#endif