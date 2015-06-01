#include <dos.h>
#include <mem.h>
#include "gfx.h"

void set_mode(unsigned char mode)
{
	union REGS regs;

	regs.h.ah = SET_MODE;
	regs.h.al = mode;

	int86(VIDEO_INT, &regs, &regs);
}

void put_pixel(int x, int y, int color)
{
	VGA[(y<<8) + (y<<6) + x] = color; // (256y) + (64y) + x
}

void draw_rect(int left, int top, int right, int bottom, byte color)
{
	word top_offset, bottom_offset, width, i;

	top_offset 	= (top<<8) + (top<<6) + left;
	bottom_offset 	= (bottom<<8) + (bottom<<6) + left;
	width		= right - left + 1;

	for( i=top_offset; i<=bottom_offset; i+=SCREEN_WIDTH ) {
		memset(&VGA[i],color,width);	
	}
}
