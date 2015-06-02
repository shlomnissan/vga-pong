#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>

#include "types.h"
#include "gfx.h"
#include "input.h"

int main(void) {

	struct point speed 	= { 1,1 };
	struct point position 	= { SCREEN_WIDTH >> 1, SCREEN_HEIGHT >> 1 };

	init_buffer();

	set_mode(VGA_256_MODE);

	while(readKeyboard() != KEY_ESCAPE) {
	
		position.x += speed.x;
		position.y += speed.y;

		draw_rect( position.x - 1  , position.y - 1, position.x + 1, position.y + 1, 0xf);	
		
		if( position.x >= SCREEN_WIDTH || position.x <= 0 ) {
			speed.x *= -1;
		}

		if( position.y >= SCREEN_HEIGHT || position.y <= 0 ) {
			speed.y *= -1;
		}
		
		sync_v();

		clear_buffer();
	}

	end_buffer();

	set_mode(TEXT_MODE);

	return 0;

}
