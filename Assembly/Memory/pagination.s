.global enablePagination
.global enablePSE
#.global invalidate 

#	Routine who enable pagination 
#	[esp+8] Page Directory 0 (kernel mode) parameter
#	[esp+4] Paging Flag parameter
enablePagination:
    mov 8(%esp), %eax # get Page Directory 0 (kernel mode)
    mov %eax, %cr3 # load cr3 with Page Directory address
    mov %cr0, %eax
    or 4(%esp), %eax # oring eax and paging flag (PG flag)
    mov %eax, %cr0
    ret

# Routine who enable PSE for 4Mb pages instead of 4 Kb
# Just oring the CR4 register with 0x00000010 to activate PSE bit
enablePSE:
	mov %cr4, %eax 
	or 0x00000010, %eax 
	mov %eax, %cr4

