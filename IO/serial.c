// Base addresses of serial ports 
#define COM1_ADDR    0x3F8 // Start of buffer
#define COM2_ADDR    0x2F8

// Port registers, specified by port base address + offset
#define INT_ENABLE(baseAddr)        (baseAddr + 1)
#define INT_ID_FIFO(baseAddr)       (baseAddr + 2)
#define LINE_CTRL_REG(baseAddr)     (baseAddr + 3)
#define MODEM_CTRL_REG(baseAddr)    (baseAddr + 4)
#define LINE_STATUS_REG(baseAddr)   (baseAddr + 5)
#define MODEM_STATUS_REG(baseAddr)  (baseAddr + 6)
#define SCRATCH_REG(baseAddr)       (baseAddr + 7)

/**
 * Configure speed for sending data to serial port
 * @param portCom The port COM to configure
 * @param divisor The divisor for baud rate (result speed in bits/s)
 */
void configureBaudRate(unsigned short comPort, unsigned int divisor) {
   outb(LINE_CTRL_REG(comPort), 0x80);          // Enable DLAB 
   outb(comPort, (divisor >> 8) & 0x00FF);    // Set divisor 
   outb(comPort, (divisor & 0x00FF));
}

/** 
 *  Configures the line of the given serial port
 *  @param comPort The serial port to configure
 */
void configureLine(unsigned short comPort){
   outb(LINE_CTRL_REG(comPort), 3); // standard value for 8 bits data length, no parity bits, one stop bit
}

/**
 * Initialize the serial port
 */
void initSerial(portCom) {
   /* configure serial port */
   configureBaudRate(portCom, 3); // divisor to 3, 38400 baud
   configureLine(portCom);
}


int serialReceived(unsigned short comPort) {
   return inb(LINE_STATUS_REG(comPort)) & 1;
}
 
char readSerial(unsigned short comPort) {
   while (serialReceived(comPort) == 0);
   return inb((comPort));
}

/**
 * Check if FIFO queue is empty 
 * @param comPort The COM port to check
 * @return 0 if not empty, 1 if empty
 */
int isTransmitEmpty(unsigned short comPort) {
   return inb(LINE_STATUS_REG(comPort)) & 0x20;
}
 
void writeSerial(char a, unsigned short comPort) {
   while (isTransmitEmpty(comPort) == 0);
   outb((comPort),a);
}


