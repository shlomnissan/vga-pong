#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>

#include "gfx.h"

int main(void) {

	int i, x, y, color;

	set_mode(VGA_256_MODE);

	for(i=0; i<32767; i++) {

		x 	= rand()%SCREEN_WIDTH;
		y 	= rand()%SCREEN_HEIGHT;
		color 	= rand()%NUM_COLORS;

		put_pixel(x, y, color);
	}

	getch();
	set_mode(TEXT_MODE);

	return 0;

}
