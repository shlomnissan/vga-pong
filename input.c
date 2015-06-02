#include "input.h"

int readKeyboard(void)
{
	int last_key = inportb(I_KEYBOARD);
	
	// Check if key is pressed (bit 7 = 0) or released (bit 7 = 1)
	if(last_key < 128) {
		return last_key;
	}

	outportb(0x20, 0x20); // Signals 8259 in PC that interrupt has been processed

	return 0;
}

