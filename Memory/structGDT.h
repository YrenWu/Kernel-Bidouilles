#ifndef INCLUDE_STRUCTGDT_H
#define INCLUDE_STRUCTGDT_H

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