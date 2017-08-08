/*
	vga.c allows us to write on screen.
	interactions with vga port framebuffer can displays 
	characters in a terminal. 

	We need to initialize Terminal before writing with two properties
	default backgroud color and default foreground color
*/


/* Framebuffer start adress */
#define FRAMEBUFFER_START_ADDRESS   0xB8000

// x86's VGA buffer
volatile uint16_t* vgaFrameBuffer = (uint16_t*) FRAMEBUFFER_START_ADDRESS;

/* Terminal structure defined by address, initilized flag (int), row, column and color */
Terminal terminal = {
   FRAMEBUFFER_START_ADDRESS, false, 0, 0
};

/**
 * Set the console color
 *
 * @param blackground The background color
 * @param foreground The foreground color
 *
 * @return uint8_t
 */
uint8_t setColor(int background, int foreground)
{
	/* on 16 bits: 
	8 most significant bits  
	Color : 
		- 4 MSB for background
		- 4 LSB for foreground
	8 less significants bits 
		Character */
	uint8_t color;
	color = ((background & 0x0F) << 4) | (foreground & 0x0F);
	return color;
} 

/**
 * Clear the terminal
 */
void clearConsole()
{
	terminal.currentColumn = 0;
	terminal.currentRow = 0;
	for (int col = 0; col < FB_COLUMN_SIZE; col ++)
	{
		for (int row = 0; row < FB_ROW_SIZE; row ++)
		{
			int index = (FB_COLUMN_SIZE * row) + col;
			vgaFrameBuffer[index] = ((uint16_t)terminal.defaultColor << 8) | ' ';
		}
	}
}

/**
 * Set default Color and Clear
 * @param background The backgrount color
 * @param foreground The foreground color
 */
void initTerm(int background, int foreground)
{
	// set terminal default background and foreground color
	terminal.defaultColor = setColor(background, foreground); 
	terminal.initialized = true;
	clearConsole();
}

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

void printHex(uint32_t n)
{
	uint8_t numbers[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	printBase(n, numbers, 16, 10);
}

void printDec(uint32_t n)
{
	uint8_t numbers[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	printBase(n, numbers, 10, 10);
} 

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
