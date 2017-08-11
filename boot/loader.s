.extern kernel_main				# declare C main function for entry of kernel		
.global loader					# set loader label accessible form outside the file
	
# MULTIBOOT HEADER 	
.set MAGIC, 0x1BADB002 			# GRUB will use this to detect kernel's location		
.set ALIGN_MOD, 0x00000001																				
.set CHECKSUM, -(MAGIC + ALIGN_MOD)

.section .multiboot
	.align 4 
	.long MAGIC
	.long ALIGN_MOD
	.long CHECKSUM
																	
.section .bss
	.align 16				
	kernel_stack_bottom:		# stack allocation							
		.skip 4096											
	kernel_stack_top: 												
																
.section .text 													
.align 4		
	loader:																										
	mov $kernel_stack_top, %esp # stack setup	
	push %ebx;								
	call kernel														
			
	cli							# clear interrupt flags								
.loop: 																
	jmp .loop					# kernel's inifinite loop												
									
