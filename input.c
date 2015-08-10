#include "input.h"

int keys[128];

int readKeyboard(void)
{
	int key = inportb(I_KEYBOARD);
	outportb(0x20, 0x20); // Signals 8259 in PC that interrupt has been processed
	
	if( key == SPACE_BAR ) {

		return SPACE_BAR;

	}

	if( key < 128 ) {
	
		keys[key] = 1;

		if( key == KEY_ESCAPE || key == KEY_UP_D || key == KEY_DOWN_D ) {
			
			return key;

		}

	} else {
		
		// if up button released, check if down button is still pressed
		if( key == KEY_UP_R ) {

			keys[KEY_UP_D] = 0;
			
			if( keys[KEY_DOWN_D] == 1 ) {
				return KEY_DOWN_D;
			}
		}

		// if down button released, check if up button is still pressed
		if( key == KEY_DOWN_R ) {
		
			keys[KEY_DOWN_D] = 0;
			
			if( keys[KEY_UP_D] == 1 ) {
				return KEY_UP_D;
			}

		}

	}

	return 0;
}

