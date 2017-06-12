/* linker script */ 
ENTRY(loader) 			/* define the entry point */

SECTIONS {

	 . = 0x00100000; 		

	.text ALIGN (0x1000) :  
	{
		*(.multiboot) 	/* or in .text segment */
		*(.text) 		/* all text section from all files */
	}

	.rodata ALIGN (0x1000) : 
	{
		*(.rodata*) 	/* idem for read-only data */
	}

	.data ALIGN (0x1000) : 
	{
		*(.data)
	}

	.bss ALIGN (0x1000) : 
	{
		*(COMMON) 		/* all common sections from all files */
		*(.bss*)
	}

	/* Other sections may be produced by compiler, we can add stuff here as needed. */
}

