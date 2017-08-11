#define KEYB_DATA_PORT 	0x60
#define KEYB_CMD_PORT 	0x64

void kbCallback(cpuSize_t registers);
void initKeyboard();
unsigned char hexToLetter(char c);

void initKeyboard()
{
	registerInterruptHandler(IRQ1, &kbCallback);
}

void kbCallback(cpuSize_t registers)
{
	unsigned char bytes;
	unsigned char letter;

    do {
        if(inb(KEYB_DATA_PORT) != bytes) { // if new char
            bytes = inb(KEYB_DATA_PORT);
            if(bytes <= 0x5D) {
            	letter = hexToLetter(bytes);
            	putChar(letter, terminal.defaultColor);
         	} 
        }
    } while(true);
}

unsigned char hexToLetter(char c)
{
	char letter;

	uint8_t numbers[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0' };
	uint8_t lettersUp[] = {'a','z','e','r','t','y','u','i','o','p'};
	uint8_t lettersMiddle[] = {'q','s','d','f','g','h','j','k','l','m'};
	uint8_t lettersDown[] = {'w','x','c','v','b','n'};

	if((c >= 0x2) && (c <= 0xB)) { 
		return numbers[c-2];
	} else if ((c >= 0x10) && (c <= 0x19)) {
		return lettersUp[c-16];
	} else if ((c >= 0x1E)  && (c <= 0x27)) {
		return lettersMiddle[c-30];
	} else if ((c >= 0x2C)  && (c <= 0x31)) {
		return lettersDown[c-44];
	} else if (c == 0x1C) {
 		return '\n';
 	} else if (c == 0x39) {
 		return ' ';
 	}
}