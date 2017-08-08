#ifndef FRAMEBUFFER_H 
#define FRAMEBUFFER_H

/* Framebuffer start adress */
#define FRAMEBUFFER_START_ADDRESS   0xB8000

// x86's VGA buffer
volatile uint16_t* vgaFrameBuffer = (uint16_t*) FRAMEBUFFER_START_ADDRESS;

/* Terminal structure defined by address, initilized flag (int), row, column and color */
Terminal terminal = {
   FRAMEBUFFER_START_ADDRESS, false, 0, 0
};

uint8_t setColor(int background, int foreground);
void clearConsole();
void initTerm(int background, int foreground);


#endif