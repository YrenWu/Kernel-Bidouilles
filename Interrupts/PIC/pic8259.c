/* Master and Slave I/O ports addresses for A port */
#define MASTER_PORT_ADDR_A	0x20
#define SLAVE_PORT_ADDR_A	0xA0

/* Master and Slave I/O ports addresses for B port */
#define MASTER_PORT_ADDR_B	0x21
#define SLAVE_PORT_ADDR_B	0xA1

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

static void irqRemap()
{
  /* Send ICW1 to port A */
outb(ICW1_MASTER, MASTER_PORT_ADDR_A);
outb(ICW1_SLAVE, SLAVE_PORT_ADDR_A);

/* Send others ICW to port B */
outb(ICW2_MASTER, MASTER_PORT_ADDR_B);
outb(ICW2_SLAVE, SLAVE_PORT_ADDR_B);

outb(ICW3_MASTER, MASTER_PORT_ADDR_B);
outb(ICW3_SLAVE, SLAVE_PORT_ADDR_B);

outb(ICW4_MASTER, MASTER_PORT_ADDR_B);
outb(ICW4_SLAVE, SLAVE_PORT_ADDR_B);

} 

// This gets called from our ASM interrupt handler stub.
void irqHandler(cpuSize_t regs)
{
   // Send an EOI (end of interrupt) signal to the PICs.
   // If this interrupt involved the slave.
   if (regs.interrupt >= 40)
   {
       // Send reset signal to slave.
       outb(0xA0, 0x20);
   }

   debug(regs);
   // Send reset signal to master. (As well as slave, if necessary).
   outb(0x20, 0x20);
} 

