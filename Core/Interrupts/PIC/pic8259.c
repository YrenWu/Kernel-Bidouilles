/*  PIC related tu cpu */

/* Master and Slave I/O ports addresses for A port */
#define MASTER_PORT_ADDR_A	0x20
#define SLAVE_PORT_ADDR_A	  0xA0

/* Master and Slave I/O ports addresses for B port */
#define MASTER_PORT_ADDR_B	0x21
#define SLAVE_PORT_ADDR_B	  0xA1

/* ICW Values to send */
#define ICW1_MASTER 		0x11 // configurate master to send ICW4 (port A)
#define ICW1_SLAVE 			0x11 // configurate slave to send ICW4 (port A)
#define ICW2_MASTER 		0x20 // offset in IDT
#define ICW2_SLAVE 			0x28 // offset in IDT
#define ICW3_MASTER 		0x04 // connected lines to slave (IR line 2)
#define ICW3_SLAVE 			0x02 // connected lines to master (IR line 2)
#define ICW4_MASTER 		0x05 // master 
#define ICW4_SLAVE 			0x01 // slave

#define PIC_ACKNOWLEDGEMENT	0x20 // end of interruption signal

#define OFFSET        0x8   // Offet between slave and master 
#define MASTER_BEGIN  MASTER_PORT_ADDR_A
#define SLAVE_BEGIN   MASTER_PORT_ADDR_A + OFFSET 
#define PIC_END       SLAVE_BEGIN + OFFSET - 1

/*
_______________________________________________________
|   PIC 1   |   Matériel  |   PIC 2   |   Matériel    |
|___________|_____________|___________|_______________|
|     0     |   Timer     |     8     |Real Time Clock|
|     1     |   Keyboard  |     9     |   General I/O |
|     2     |   PIC 2     |     10    |   General I/O |   
|     3     |   COM 2     |     11    |   General I/O |   
|     4     |   COM 1     |     12    |   General I/O |   
|     5     |   LPT 2     |     13    |   Coprocessor |
|     6     |   Disquette |     14    |   IDE Bus     |  
|     7     |   LPT 1     |     15    |   IDE Bus     |     
|___________|_____________|___________|_______________|     

*/
/*  Configure ports for programming interruption  */
static void irqRemap()
{
  /* Send ICW1 to port A */
  outb(MASTER_PORT_ADDR_A, ICW1_MASTER);
  outb(SLAVE_PORT_ADDR_A, ICW1_SLAVE);

  /* Send others ICW to port B */
  outb(MASTER_PORT_ADDR_B, ICW2_MASTER);
  outb(SLAVE_PORT_ADDR_B,ICW2_SLAVE);

  outb(MASTER_PORT_ADDR_B,ICW3_MASTER);
  outb(SLAVE_PORT_ADDR_B,ICW3_SLAVE);

  outb(MASTER_PORT_ADDR_B,ICW4_MASTER);
  outb(SLAVE_PORT_ADDR_B, ICW4_SLAVE);

} 

/*  Acknwoledge and reset interruptions when triggered */
void acknowledge(uint8_t interrupt) 
{
  // The interrupt number must be in PIC interval
  if(interrupt > PIC_END || interrupt < MASTER_BEGIN) {
    return;
  }

  // If this interrupt is for slave PIC
  if(interrupt >= SLAVE_BEGIN) {
    // Send reset signal to slave (End Of Interruption))
    outb(SLAVE_PORT_ADDR_A, PIC_ACKNOWLEDGEMENT);
  }
  // Send reset signal to master PIC
  outb(MASTER_PORT_ADDR_A, PIC_ACKNOWLEDGEMENT);
}

// call from asm irq common stub
void irqHandler(cpuSize_t regs)
{
  acknowledge(regs.interrupt);
  if (interruptCallbacks[regs.interrupt] != 0) {
    isr_t handler = interruptCallbacks[regs.interrupt];
    handler(regs);
  } else { 
    debug(regs);
  }
} 

void registerInterruptHandler(uint8_t n, isr_t handler)
{
  interruptCallbacks[n] = handler;
}

