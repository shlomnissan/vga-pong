#include "input.h"

int readKeyboard(void)
{
	int lastKey = inportb(I_KEYBOARD);
	
	// Check if key is pressed (bit 7 = 0) or released (bit 7 = 1)
	if(lastKey < 128) {
		return lastKey;
	}

	outportb(0x20, 0x20); // Signals 8259 in PC that interrupt has been processed

	return 0;
}

