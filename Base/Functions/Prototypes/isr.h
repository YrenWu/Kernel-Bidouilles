#ifndef ISR_H
#define ISR_H

// Exceptions

#define DIVIDE_ZERO 0

#define EXCEPT1 1
#define EXCEPT2 2
#define EXCEPT3 3
#define EXCEPT4 4
#define EXCEPT5 5
#define EXCEPT6 6
#define EXCEPT7 7

#define DOUBLE_FAULT 8

#define EXCEPT9 9
#define EXCEPT10 10
#define EXCEPT11 11
#define EXCEPT12 12
#define EXCEPT13 13

#define PAGE_FAULT 14

#define EXCEPT15 15
#define EXCEPT16 16
#define EXCEPT17 17
#define EXCEPT18 18
#define EXCEPT19 19
#define EXCEPT20 20

// Interruptions
#define IRQ0 32		// PIT 8254  PIC-master 0 : Timer | PIC-Slave 8 : Real Time Clock (CMOS)
#define IRQ1 33		// PS2 / Keyboard Interruption

// Enables registration of callbacks for interrupts or IRQs.
typedef void (*isr_t)(cpu);
void registerInterruptHandler(uint8_t n, isr_t handler); 
isr_t interruptCallbacks[256];

Clock clock = {
  0, false
};

#endif 

// 0    # 0x0 divide by zero            		FAULT 
// 1    # 0x1 Debug                     		FAULT/TRAP
// 2    # 0x2 Non-maskable interrupt    		INTERRUPT
// 3    # 0x3 Breakpoint                		TRAP
// 4    # 0x4 Overflow                  		TRAP 
// 5    # 0x5 Bound range Exceeded      		FAULT
// 6    # 0x6 Invalid opcode            		FAULT
// 7    # 0x7 Device not available      		FAULT
// 8    # 0x8 Double fault              		ABORT (code 0)
// 9    # 0x9 Coprocessor Segment Overun 		FAULT  (obsolete > 486)
// 10   # 0xA Invalid TSS               		FAULT 
// 11   # 0xB Segment not present       		FAULT
// 12   # 0xC Stack segment fault       		FAULT
// 13   # 0xD Genreal protection fault  		FAULT
// 14   # 0xE Page fault                		FAULT
// 15   # 0xF  Unknown interrupt exception 
// 16   # 0x10 Floating Point exception 		FAULT
// 17   # 0x11 Alignment check          		FAULT
// 18   # 0x12 Machine check            		ABORT
// 19   # 0x13 SIMD Floating Point Exception 	FAULT  
// 20   # 0x14 Virtualization exception 		FAULT
// 21-29 # 0x15-0x1D Reserved 
// 30   # 0x1E Security Exception       
// 31   # 0x1F Reserved