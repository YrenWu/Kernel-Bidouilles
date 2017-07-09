#define SELECTOR 0x08
#define FLAGS 0x8E

extern void loadIDT(); // lidt asm code

idtEntry_t idt[256];
idtPtr_t  ptrIdt;

void idtSetEntry(uint8_t i, uint32_t base, uint16_t selector, uint8_t flags)
{
   idt[i].offsetLow = base & 0xFFFF;
   idt[i].offsetHigh = (base >> 16) & 0xFFFF;

   idt[i].segmentSelector = selector;
   idt[i].reserved = 0;
   // We must uncomment the OR below when we get to using user-mode.
   // It sets the interrupt gate's privilege level to 3.
   idt[i].flags   = flags /* | 0x60 */;
} 

void idtInit()
{
   ptrIdt.lastAddress = sizeof(idtEntry_t) * 256 -1;
   ptrIdt.firstAddress  = (uint32_t)&idt;

   idtSetEntry(0, (uint32_t)isr0 , SELECTOR, FLAGS);
   idtSetEntry(1, (uint32_t)isr1 , SELECTOR, FLAGS);
   idtSetEntry(2, (uint32_t)isr2 , SELECTOR, FLAGS);
   idtSetEntry(3, (uint32_t)isr3 , SELECTOR, FLAGS);
   idtSetEntry(4, (uint32_t)isr4 , SELECTOR, FLAGS);
   idtSetEntry(5, (uint32_t)isr5 , SELECTOR, FLAGS);
   idtSetEntry(6, (uint32_t)isr6 , SELECTOR, FLAGS);
   idtSetEntry(7, (uint32_t)isr7 , SELECTOR, FLAGS);
   idtSetEntry(8, (uint32_t)isr8 , SELECTOR, FLAGS);
   idtSetEntry(9, (uint32_t)isr9 , SELECTOR, FLAGS);
   idtSetEntry(10, (uint32_t)isr10 , SELECTOR, FLAGS);
   idtSetEntry(11, (uint32_t)isr11 , SELECTOR, FLAGS);
   idtSetEntry(12, (uint32_t)isr12 , SELECTOR, FLAGS);
   idtSetEntry(13, (uint32_t)isr13 , SELECTOR, FLAGS);
   idtSetEntry(14, (uint32_t)isr14 , SELECTOR, FLAGS);
   idtSetEntry(15, (uint32_t)isr15 , SELECTOR, FLAGS);
   idtSetEntry(16, (uint32_t)isr16 , SELECTOR, FLAGS);
   idtSetEntry(17, (uint32_t)isr17 , SELECTOR, FLAGS);
   idtSetEntry(18, (uint32_t)isr18 , SELECTOR, FLAGS);
   idtSetEntry(19, (uint32_t)isr19 , SELECTOR, FLAGS);
   idtSetEntry(20, (uint32_t)isr20 , SELECTOR, FLAGS);
   idtSetEntry(21, (uint32_t)isr21 , SELECTOR, FLAGS);
   idtSetEntry(22, (uint32_t)isr22 , SELECTOR, FLAGS);
   idtSetEntry(23, (uint32_t)isr23 , SELECTOR, FLAGS);
   idtSetEntry(24, (uint32_t)isr24 , SELECTOR, FLAGS);
   idtSetEntry(25, (uint32_t)isr25 , SELECTOR, FLAGS);
   idtSetEntry(26, (uint32_t)isr26 , SELECTOR, FLAGS);
   idtSetEntry(27, (uint32_t)isr27 , SELECTOR, FLAGS);
   idtSetEntry(28, (uint32_t)isr28 , SELECTOR, FLAGS);
   idtSetEntry(29, (uint32_t)isr29 , SELECTOR, FLAGS);
   idtSetEntry(30, (uint32_t)isr30 , SELECTOR, FLAGS);
   idtSetEntry(31, (uint32_t)isr31 , SELECTOR, FLAGS);

   loadIDT((uint32_t)&ptrIdt);
}

void printCPU(cpuSize_t cpu) {
	printColor("-----------------------------------------------", BLACK, RED);
	printColor("------------------ CPU state ------------------", BLACK, RED);
	printColor("-----------------------------------------------", BLACK, RED);
	print("");
	print("-----------------------------------------------");
	print("------------ CPU general registers ------------");
	printCat("| EAX : ");
	printDec(cpu.eax);
	printCat("| EBX : ");
	printDec(cpu.ebx);
	printCat("| ECX : ");
	printDec(cpu.ecx);
	printCat("| EDX : ");
	printDec(cpu.edx);
	print("");
	print("");
	print("-----------------------------------------------");
	print("------------ CPU segment registers ------------");
	printCat("| CS : ");
	printDec(cpu.cs);
	printCat("| DS : ");
	printDec(cpu.ds);
	printCat("| SS : ");
	printDec(cpu.ss);
	printCat("| ES : ");
	printDec(cpu.es);
	printCat("| FS : ");
	printDec(cpu.fs);
	printCat("| GS : ");
	printDec(cpu.gs);
	print("");
	print("");
	print("-----------------------------------------------");
	print("---------- EBP and Indexes regiters -----------");
	printCat("| EBP : ");
	printDec(cpu.ebp);
	printCat("| ESI : ");
	printDec(cpu.esi);
	printCat("| EDI : ");
	printDec(cpu.edi);
	print("");
	print("");
}

void printStack(stackSize_t stack) {
	printColor("-----------------------------------------------", BLACK, RED);
	printColor("-------------------- Stack --------------------", BLACK, RED);
	printColor("-----------------------------------------------", BLACK, RED);
	print("");
	printCat("| error code : ");
	printDec(stack.errorCode);
	printCat("| EIP : ");
	printDec(stack.eip);
	printCat("| CS : ");
	printDec(stack.cs);
	printCat("| eflags : ");
	printDec(stack.eflags);
	print("");
	print("");
}

void debug(cpuSize_t cpu, stackSize_t stack, int interrupt) {
	printColor("Interrupt Triggered", RED, BLACK);
	printStack(stack);
	printCPU(cpu);
}

void interruptHandler(cpuSize_t cpu, stackSize_t stack, int interrupt) {
	debug(cpu, stack, interrupt);
}