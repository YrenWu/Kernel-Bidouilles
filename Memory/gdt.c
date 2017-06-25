    void lgdt(uint16_t addressGDT)
    {
        asm volatile ( "lgdt %0" 
        	: "=m"(addressGDT) 
        	:
        );
    }

    void gdtSetup(uint32_t ptr)
    {
	  /* Commit the GDT into the CPU, and update the segment
	     registers. The CS register may only be updated with a long jump
	     to an absolute address in the given segment (see Intel x86 doc
	     vol 3, section 4.8.1). */
	  asm volatile ("lgdt %0          \n\
	                 ljmp %1,$1f      \n\
	                 1:               \n\
	                 movw 0x10, %%ax    \n\
	                 movw %%ax,  %%ss \n\
	                 movw %%ax,  %%ds \n\
	                 movw %%ax,  %%es \n\
	                 movw %%ax,  %%fs \n\
	                 movw %%ax,  %%gs"
			:
			:"m"(ptr), // pointer to global descriptot table
			 "i"(8),
			 "i"(16) // 24 32
			:"memory","eax");   	
    }