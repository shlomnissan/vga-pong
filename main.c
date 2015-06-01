#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>

#include "gfx.h"

int main(void) {

	int i, x, y, color;

	set_mode(VGA_256_MODE);
	
	draw_rect(5, 5, 13, 45, 5);	

	getch();
	set_mode(TEXT_MODE);

	return 0;

}
