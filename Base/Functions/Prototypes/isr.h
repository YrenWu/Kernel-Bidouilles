#ifndef ISR_H
#define ISR_H

// Exceptions
#define EXCEPT0 0
#define EXCEPT1 1
#define EXCEPT2 2
#define EXCEPT6 6
#define EXCEPT7 7


// Interruptions
#define IRQ0 32		// PIT 8254  PIC-master 0 : Timer | PIC-Slave 8 : Real Time Clock (CMOS)

// Enables registration of callbacks for interrupts or IRQs.
typedef void (*isr_t)(cpu);
void registerInterruptHandler(uint8_t n, isr_t handler); 
isr_t interruptCallbacks[256];

Clock clock = {
  0, false
};

#endif 