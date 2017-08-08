#include "Prototypes/display.h"
#include "Prototypes/framebuffer.h"


/**
 * Write a letter in terminal
 * @param char c The character to display
 */
void putChar(char c, uint8_t color)
{
	const size_t index = (FB_COLUMN_SIZE * terminal.currentRow) + terminal.currentColumn; // buffer index
	vgaFrameBuffer[index] = ((uint16_t)color << 8) | c;
	terminal.currentColumn ++;
 
	if (terminal.currentColumn >= FB_COLUMN_SIZE)
	{
		terminal.currentColumn = 0;
		terminal.currentRow ++;
	}
 
	// if full framebuffer return to top
	if (terminal.currentRow >= FB_ROW_SIZE)
	{
		terminal.currentColumn = 0;
		terminal.currentRow = 0;
	}
}

/**
 * This function prints an string onto the screen
 * @param char* str Pointer to string to print
 */ 
void printCat(char* str)
{
	if(terminal.initialized == false) {
		initTerm(BACKGROUND, FOREGOUND);
	} 
	for (size_t i = 0; str[i] != '\0'; i ++){
		putChar(str[i], terminal.defaultColor);
	} 
}

/**
 * This function prints an string onto the screen
 * @param char* str Pointer to string to print
 */ 
void print(char* str)
{
	printCat(str);
	// change line
	terminal.currentColumn = 0; 
	terminal.currentRow ++;
}

/**
 * Takes an integer, converts it to string and print it on screen in a different base
 *
 * @param n The integer to convert and display
 * @param numbers Pointer to an array of digits
 * @param base The chosen base
 * @param size The size of the number in digits
 */
void printBase(uint32_t n, uint8_t* numbers, size_t base, size_t  size)
{
	if(terminal.initialized == false) {
	initTerm(BACKGROUND, FOREGOUND);
	} 

    // if negative number
	if (n < 0) {
     	putChar('-', terminal.defaultColor);
      	n = -n;
    } 

    char charsToDisplay[size]; // digit numbers 
    char num;
    int i = 0;
    while (n > 0) { 
    	int rest = n % base;
    	n = (n-rest) / base;
    	num = numbers[rest];
    	charsToDisplay[i] = num;
    	i++;
    }
    for(int j=0; j<=i; i--) {
    	num = charsToDisplay[i-1];
    	putChar(num, terminal.defaultColor);
    } 
}

/**
 * Takes a number and display in hexadecimal format
 * @param n The number to convert and print
 */
void printHex(uint32_t n)
{
	uint8_t numbers[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	printBase(n, numbers, 16, 10);
}

/**
 * Takes a number and display in decimal format
 * @param n The number to convert and print
 */
void printDec(uint32_t n)
{
	uint8_t numbers[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	printBase(n, numbers, 10, 10);
} 

/**
 * Takes a number and display in binary format
 * @param n The number to convert and print
 */
void printBin(uint32_t n)
{
	uint8_t numbers[] = {'0', '1'};
	printBase(n, numbers, 2, 100);
}

 /**
 * Display string with colors
 *
 * @param char* str Pointer to string to display
 * @param int background The background color
 * @param int foreground The foreground color
 */
 void printColor(char* str, int background, int foreground)
 {
 	if(terminal.initialized == false) {
		initTerm(BACKGROUND, FOREGOUND);
	} 
 	uint8_t color = setColor(background, foreground);
 	for (size_t i = 0; str[i] != '\0'; i ++){
		putChar(str[i], color);
	} 
	// end of line
	terminal.currentColumn = 0; 
	terminal.currentRow ++;	
 }

/**
 * Print CPU register content on screen and  interrupt number and error code
 *
 * @param cpu The CPU structure with registers (from the stack)
 */
void debug(cpuSize_t cpu) {

	printColor("-----------------------------------------------", BLACK, RED);
	printColor("------------------ CPU state ------------------", BLACK, RED);
	print("-------------- General registers --------------");
	printCat("| EAX : ");
	printHex(cpu.eax);
	printCat("| EBX : ");
	printHex(cpu.ebx);
	printCat("| ECX : ");
	printHex(cpu.ecx);
	printCat("| EDX : ");
	printHex(cpu.edx);
	print("");
	print("");
	print("-------------- Segment registers --------------");
	printCat("| GS : ");
	printHex(cpu.gs);
	printCat("| FS : ");
	printHex(cpu.fs);
	printCat("| ES : ");
	printHex(cpu.es);
	printCat("| DS : ");
	printHex(cpu.ds);
	print("");
	print("");
	print("-------------- Pointer registers --------------");
	printCat("| EBP : ");
	printHex(cpu.ebp);
	printCat("| ESP : ");
	printHex(cpu.esp);
	print("");
	print("");
	print("--------------- Index registers ---------------");
	printCat("| ESI : ");
	printHex(cpu.esi);
	printCat("| EDI : ");
	printHex(cpu.edi);
	print("");
	print("");
	printColor("Error Code", RED, BLACK);
	printDec(cpu.errorCode);
	print("");
	printColor("Interrupt Triggered", RED, BLACK);
	printDec(cpu.interrupt);
	print("");
}
