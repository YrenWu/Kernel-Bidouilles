
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