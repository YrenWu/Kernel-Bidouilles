/**
 * @file types.h
 * basic types definitions
 */

/** Memory size of an object (positive) */
typedef unsigned int 		size_t;

/** Low-level sizes */
typedef unsigned long int   uint32_t; /* 32b unsigned */
typedef unsigned short int  uint16_t; /* 16b unsigned */
typedef unsigned char       uint8_t;  /* 8b unsigned */

typedef int bool;
#define true 1
#define false 0

typedef struct 	SerialPort {
	uint16_t address;
	int initialized;
} SerialPort;

/* start of framebuffer.
   Framebuffer is made by 25 rows and 80 columns, this is the console size
   Lines and columns start to 0 offset, so first position is at (0,0) */
typedef struct Terminal {
	uint32_t address;
	int initialized;
	int currentColumn;
	int currentRow;
	uint16_t defaultColor;
} Terminal;