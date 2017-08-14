#include "../../Base/Structures/pagingDescriptors.h"

void initPageMem();

#define READ_ONLY_PAGING_FLAG 0x80010001 // WP bit enable r/o mode
#define PAGING_FLAG     0x80000000     /* CR0 - bit 31   0x80000000 */ 

#define PD0_ADDR 0x20000        /* addr. page directory kernel */
#define PT0_ADDR 0x21000        /* addr. page table[0] kernel */

#define FRAME_SIZE 1024

extern void enablePagination(uint32_t pagingFlag, uint32_t pd0);
extern void enablePSE(); // Causes an exception 13, Triple fault

/* First mapping : virtual addesses = physical adresses on 4Mo */
void initMemPage(void)
{
    uint32_t *pDir0;       /* kernel page directory */
    uint32_t *pTab0;       /* kernel page table */
    uint32_t pageAddress;
    int i;

    /* Always initialise Page Directory before activate pagination */
    /* Create Page Directory */
    pDir0 = (uint32_t *) PD0_ADDR; // page directory to 0x20000 physical address (array 1024 entries)
    pDir0[0] = PT0_ADDR; // initialise first entry (points to first Page Table. Physical Address :0x21000)
    pDir0[0] |= 3; // add flag bytes for enab1e in memory, and RW

    for (i = 1; i < FRAME_SIZE; i++) {
    	pDir0[i] = 0;
    }
        
    /* Create Page Table[0] */
    pTab0 = (uint32_t *) PT0_ADDR;
    pageAddress = 0;

    for (i = 0; i < FRAME_SIZE; i++) {
        pTab0[i] = pageAddress;
        pTab0[i] |= 3;
        pageAddress += FRAME_SIZE * 4; // points to next page table
    }

    enablePagination(PAGING_FLAG, PD0_ADDR);
}
