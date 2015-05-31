#include <dos.h>
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
	VGA[y * SCREEN_WIDTH + x] = color;
}
