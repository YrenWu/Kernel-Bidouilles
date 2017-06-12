/* Framebuffer start adress */
#define FRAMEBUFFER_START_ADDRESS   0xB8000

/* Console screen size */
#define FB_ROW_SIZE     25
#define FB_COLUMN_SIZE  80

/* Colors */
#define BLACK 			 0
#define BLUE 		 	 1
#define GREEN 			 2
#define CYAN 		 	 3
#define RED  		 	 4
#define MAGENTA 	 	 5
#define BROWN 			 6
#define LIGHT_GREY 		 7
#define DARK_GREY 		 8
#define LIGHT_BLUE 		 9
#define LIGHT_GREEN  	 10
#define LIGHT_CYAN   	 11
#define LIGHT_RED  		 12
#define LIGHT_MAGENTA	 13
#define LIGHT_BROWN  	 14
#define WHITE 			 15

// x86's VGA buffer. 
volatile uint16_t* vgaFrameBuffer = (uint16_t*) FRAMEBUFFER_START_ADDRESS;
 
// start of framebuffer
int currentColumn 	= 0;
int currentRow 		= 0;

uint16_t defaultColor;

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
void initTerm(int background, int foreground)
{
	// set terminal default background and foreground color
	defaultColor = setColor(background, foreground); 

	for (int col = 0; col < FB_COLUMN_SIZE; col ++)
	{
		for (int row = 0; row < FB_ROW_SIZE; row ++)
		{
			int index = (FB_COLUMN_SIZE * row) + col;
			vgaFrameBuffer[index] = ((uint16_t)defaultColor << 8) | ' ';
		}
	}
}

/**
 * Write a letter in terminal
 * @param char c The character to display
 */
void putChar(char c, uint8_t color)
{
	const size_t index = (FB_COLUMN_SIZE * currentRow) + currentColumn; // buffer index
	vgaFrameBuffer[index] = ((uint16_t)color << 8) | c;
	currentColumn ++;
 
	if (currentColumn >= FB_COLUMN_SIZE)
	{
		currentColumn = 0;
		currentRow ++;
	}
 
	// if full framebuffer return to top
	if (currentRow >= FB_ROW_SIZE)
	{
		currentColumn = 0;
		currentRow = 0;
	}
}

/**
 * This function prints an string onto the screen
 * @param char* str Pointer to string to print
 */ 
void print(char* str)
{
	for (size_t i = 0; str[i] != '\0'; i ++){
		putChar(str[i], defaultColor);
	} 
	// change line
	currentColumn = 0; 
	currentRow ++;
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
 	uint8_t color = setColor(background, foreground);
 	for (size_t i = 0; str[i] != '\0'; i ++){
		putChar(str[i], color);
	} 
	// change line
	currentColumn = 0; 
	currentRow ++;	
 }

 

 