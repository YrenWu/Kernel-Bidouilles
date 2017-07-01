.global gdtFlush  	# make this function global, this will be visible in C code
.extern ptrGdt   	# take an extern label form C code

gdtFlush:

    lgdt (ptrGdt)        # load Global Descriptor Table, take a pointer to first GDT entry in parameter
    mov  $0x10, %ax    
    mov %ax, %ds 		 # initialize segment registers 
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs 
    mov %ax, %ss
    jmp $0x08, $.flush 
.flush:
   ret
