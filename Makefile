ASM 		= ../cross-compiler/bin/i686-elf-as
ASMFLAGS	= -g
CCOMPILER 	= ../cross-compiler/bin/i686-elf-gcc
CFLAGS 		= -std=gnu99 -ffreestanding -g
LFLAGS 		= -ffreestanding -nostdlib -g -T 
QEMU		= qemu-system-i386
EMU_OPT		= -kernel
KERNEL_NAME = MyKernel.elf
LOG_FILE	= qemuSerial.log

O_FILES 	= loader.o kernel.o gdtFlush.o

assemble:
	$(ASM) $(ASMFLAGS) boot/loader.s -o loader.o # -o loader.o io.o 
	$(ASM) $(ASMFLAGS) Memory/gdtFlush.s -o gdtFlush.o

compile:
	$(CCOMPILER) $(CFLAGS) -c kernel.c -o kernel.o 
	$(CCOMPILER) $(LFLAGS) boot/linker.ld $(O_FILES) -o $(KERNEL_NAME) -lgcc #linker

qemu:
	make assemble
	make compile
	# Launch emulator
	$(QEMU) $(EMU_OPT) $(KERNEL_NAME) -serial file:$(LOG_FILE)
	clear
	cat qemuSerial.log

bochs:
	make assemble
	make compile

	cp $(KERNEL_NAME) boot/$(KERNEL_NAME)
	genisoimage -R                      \
        -b boot/grub/stage2_eltorito    \
        -no-emul-boot                   \
        -boot-load-size 4               \
        -A os                           \
        -input-charset utf8             \
        -boot-info-table                \
        -o os.iso                       \
        .

	bochs -f bochsrc.txt

clean:
	rm *.o 
	rm $(KERNEL_NAME) 
	rm boot/$(KERNEL_NAME) 

	
	