/*
	vga.c allows us to write on screen.
	interactions with vga port framebuffer can displays 
	characters in a terminal. 

	We need to initialize Terminal before writing with two properties
	default backgroud color and default foreground color
*/
#include "../../Base/Functions/Prototypes/framebuffer.h"

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

