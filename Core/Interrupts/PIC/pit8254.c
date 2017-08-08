#include "../../../Base/Functions/Prototypes/isr.h"

/* I/O port     Usage
0x40         Channel 0 data port (read/write)
0x41         Channel 1 data port (read/write)
0x42         Channel 2 data port (read/write)
0x43         Mode/Command register (write only, a read is ignored)
*/

#define PIT_DATA_PORT0  0x40
#define PIT_CMD_PORT    0x43
#define REPEAT_MODE     0x36


Clock clock = {
  0, false
};

extern void outb();
void printTimer(); 

void registerInterruptHandler(uint8_t n, isr_t handler)
{
  interruptCallbacks[n] = handler;
} 

void timerCallback(cpuSize_t regs)
{
   clock.timer++;
   // printTimer();
}

void printTimer()
{
   printCat("Timer: ");
   printDec(clock.timer);
   print("");
}

void initTimer(uint32_t frequency)
{
  if(clock.initialized == false) {
    // Register the callback to execute when interruption is triggered
    registerInterruptHandler(IRQ0, &timerCallback);
     
    // the divisor must be small enough to fit into 16-bits.
    // clock frequency : 1193182 Hz
    uint32_t divisor = 1193182 / frequency;

    // Send the command byte.
    outb(PIT_CMD_PORT, REPEAT_MODE);

    // Divisor has to be sent byte-wise
    uint8_t lower = (uint8_t)(divisor & 0xFF); // lower bytes
    uint8_t higher = (uint8_t)((divisor>>8) & 0xFF ); // upper bytes

    // Send the frequency divisor
    outb(PIT_DATA_PORT0, lower);
    outb(PIT_DATA_PORT0, higher);

    clock.initialized = true;
  }
} 
