#ifndef DISPLAY_H
#define DISPLAY_H

/* Color set for terminal */
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

#define BACKGROUND 		 BLACK
#define FOREGOUND 		 CYAN

/* Console screen size */
#define FB_ROW_SIZE     25
#define FB_COLUMN_SIZE  80

extern void outb();

/*	Display strings or character on screen 	*/
void printColor(char* str, int background, int foreground);
void putChar(char c, uint8_t color); 
void printCat(char* str);
void print(char* str);

/*	Allow prinnting data in hexadecimal, decimal or binary format	*/
void printBase(uint32_t n, uint8_t* numbers, size_t base, size_t  size);
void printHex(uint32_t n);
void printDec(uint32_t n);
void printBin(uint32_t n);

/*	Screen displayed debugging function 	*/
void debug(cpuSize_t cpu);

#endif