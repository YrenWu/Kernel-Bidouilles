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

    do {
        if(inb(KEYB_DATA_PORT) != bytes) { // if new char
            bytes = inb(KEYB_DATA_PORT);
            if(bytes > 0) {
            	printHex(bytes);
            } 
        }
    } while(true);
}