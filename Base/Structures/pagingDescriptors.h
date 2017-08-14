#ifndef PAGING_DESCRIPTORS_H
#define PAGING_DESCRIPTORS_H
/*
	Page descriptor 32 bits word

	
	31 . . . . . . . . . . . . . . . . . . 12 11 . 9 8   7 6 5  4  3  2   1  0
	|	Frame Address						 |Avail| Rsrv |D|A| Rsrv|U/S|R/W|P|
	---------------------------------------------------------------------------		

	Frame Address 	20 bits of the frame address in physical memory	
	Avail			for kernel use	
	Rsrv			used by the CPU internally	
	D 				1 if the page has been written to
	A 				1 if the page has been accessed
	U/S 			1 User mode page, 0 Kernel mode page (User/Supervisor)
	R/W 			1 writeable page, 0 read-only	
	P 				1 if the page is present in memory

*/

/* Structure of desriptor for Page Directory Entry or Page Table Entry */
struct pageEntry
{
  	uint32_t mapped:1; /* 1=mapped, 0=free */
  	uint32_t write:1; /* 0=read-only, 1=RW */
  	uint32_t privilege:1; /* 0=kernel mode, 1=user mode */
  	uint32_t writeThrough:1; /* 0=the page has not been written to, 1=the page has been written to (since last refresh) */
  	uint32_t cacheDisabled:1; /* 1=cache disabled, 0=cache enabled */
  	uint32_t accessed:1; /* 1=RW access */
  	uint32_t reserved1:1;
  	uint32_t pageSize:1; /* 0=4Ko, 1=4Mo or > */
  	uint32_t reserved2:1; 
  	uint32_t custom:3;
  	uint32_t address:20; /* address to Page Table or Page Frame*/
} __attribute__ ((packed));
typedef struct pageEntry pageEntry_t;

typedef struct pageTable 
{
 	pageEntry_t pageFrame[1024]; // one Page Table is an array of Page Frame
} pageTable_t;

typedef struct pageDirectory
{
   pageTable_t *tables[1024]; // Array of pointers to Pages Tables
   /* the page directoty must hold physical adresses */
   uint32_t physTableAddresses[1024]; // physical location of Page Tables (for CR3) in an array of addresses
   uint32_t physicalAddr; // the physical address of physTableAddresses (array of physical addesses)
} pageDirectory_t;

void initPaging();
void switchPageDirectory(pageDirectory_t *new);
pageEntry_t *getPage(uint32_t address, int make, pageDirectory_t *dir);

#endif
