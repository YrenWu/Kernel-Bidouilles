.globl gdtFlush    # Allows the C code to call gdtFlush().

gdtFlush:
   mov 4(%esp), %eax
   lgdt (%eax)
   mov $0x10, %ax
   mov %ax, %ds
   mov %ax, %es
   mov %ax, %fs
   mov %ax, %gs 
   mov %ax, %ss
   jmp .flush
.flush:
   ret
