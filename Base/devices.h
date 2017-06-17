/**
 * @file devices.h
 * structures for ports (Serial and VGA for now)
 */

typedef struct SerialPort {
	uint16_t address;
	boolean initialized;
} SerialPort;

/* start of framebuffer.
   Framebuffer is made by 25 rows and 80 columns, this is the console size
   Lines and columns start to 0 offset, so first position is at (0,0) */
typedef struct Terminal {
	uint32_t address;
	boolean initialized;
	int currentColumn;
	int currentRow;
	uint16_t defaultColor;
} Terminal;