/*
   serial.c allows to write in a log file on host system through serial port.
   It can be useful for debugging or log events

   Interacts with COM 1 port. First, we need to initialize COM ports 
   sending bytes through them.
*/

// Base addresses of serial ports (start of port buffer)
#define COM1_ADDR    0x3F8 
#define COM2_ADDR    0x2F8

// Port registers, specified by port base address + offset
#define INT_ENABLE(baseAddr)        (baseAddr + 1)
#define INT_ID_FIFO(baseAddr)       (baseAddr + 2)
#define LINE_CTRL_REG(baseAddr)     (baseAddr + 3)
#define MODEM_CTRL_REG(baseAddr)    (baseAddr + 4)
#define LINE_STATUS_REG(baseAddr)   (baseAddr + 5)
#define MODEM_STATUS_REG(baseAddr)  (baseAddr + 6)
#define SCRATCH_REG(baseAddr)       (baseAddr + 7)

extern void outb();

/** inb:
 *  Lit un octet reçu d'un port E/S.
 *
 *  @param  port L'adresse du port E/S
 *  @return      L'octet lu
 */
extern unsigned char inb(unsigned short port);

/* Serial port structures defined by address and initilized flag (int) */
SerialPort com1 = {
   COM1_ADDR, false
};

SerialPort com2 = {
   COM2_ADDR, false
};

/**
 * Initialize the serial port 
 * -> Configure speed for sending data to serial port
 * -> Configures the way data are send to the line of the given serial port
 * @param port The port to parameter
 * @param divisor To set bauds rate (bits per seconds speed on serial port)
 */
void initSerial(int nb, size_t divisor) {
   switch (nb) {
      case 1:
         /* Enable DLAB : tell serial port to wait for 8 most significants first bits */
         outb(LINE_CTRL_REG(com1.address), 0x80);         
         // Serial port have an internal clock who works at 115200 with Hz
         // Divisor allow to control the speed to send data (115200 / 2 = 57600 Hz)     
         outb(com1.address, divisor); 
         outb(LINE_CTRL_REG(com1.address), 0x03); // standard value for 8 bits data length, no parity bits, one stop bit
         com1.initialized = true;
         break;
      case 2:
         outb(LINE_CTRL_REG(com2.address), 0x80);         
         outb(com2.address, divisor); 
         outb(LINE_CTRL_REG(com2.address), 0x03); 
         com2.initialized = true;      
         break;
   }
}

/**
 * Check if FIFO queue is empty 
 * @param comPort The COM port to check
 * @return 0 if not empty, 1 if empty
 */
int isTransmitEmpty(uint16_t comPort) {
   return inb(LINE_STATUS_REG(comPort)) & 0x20;
}

/**
 * Write a single character in serial port 
 * @param c Character to write
 * @param comPort Serial port where write data
 *
 */
void writeCharSerial(char c, uint16_t comPort) {
   while (isTransmitEmpty(comPort) == 0);
   outb((comPort),c);
}

/**
 * Write a string in serial port
 * @param str The string to write
 * @param comPort The serial port where write 
 */
void writeSerial(char* str, uint16_t comPort) {
   for (int i = 0; str[i] != '\0'; i ++){
      writeCharSerial(str[i], comPort);
   } 
}

void logSerial(char *message) {
   char *flag;
   if (com1.initialized == false) {
      initSerial(1, 3);
   } 
   
   writeSerial(message, com1.address);
   writeSerial("\n", com1.address);
}
