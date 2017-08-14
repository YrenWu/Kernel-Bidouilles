#include "../../Base/Structures/pagingDescriptors.h"

uint32_t placementAddr = 0xC0100000;

uint32_t realign(uint32_t placementAddress,int align);
uint32_t allocate(uint32_t buffSize, int align, uint32_t *physicAddr);

uint32_t realign(uint32_t placementAddress, int align) {
	boolean checkAlignement;
	checkAlignement = 1 && (placementAddress & 0xFFFFF000);
	// check if the address is already page-aligned or not, if not realign it
	if(align == checkAlignement) {
	    placementAddress &= 0xFFFFF000;
	    placementAddress += 0x1000;
	}
	return placementAddress;
}

uint32_t allocate(uint32_t buffSize, int align, uint32_t *physicAddr) 
{
	uint32_t alignAddr;
	alignAddr = realign(placementAddr, align);

	if(physicAddr) {
		*physicAddr = placementAddr;
	}

	uint32_t tmpAddress = placementAddr;
	placementAddr += buffSize; 
	return tmpAddress; // return saved address 
}

