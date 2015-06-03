#include "gfx.h"

unsigned char *double_buffer;

void set_mode(unsigned char mode)
{
	union REGS regs;

	regs.h.ah = SET_MODE;
	regs.h.al = mode;

	int86(VIDEO_INT, &regs, &regs);

	free(double_buffer); 
}

void init_buffer(void)
{
	double_buffer = (unsigned char *) malloc(320*200);

	if( double_buffer==NULL ) {
		printf("Not enough memory for double buffer.\n");
		exit(1);
	}

	clear_buffer();
}

void end_buffer(void)
{
	clear_buffer();
	free(double_buffer);
}

void clear_buffer(void)
{
	memset(&double_buffer[0],0,64000);
}

void sync_v(void)
{
	/* wait until done with vertical retrace */
	while  ((inp(INPUT_STATUS) & VRETRACE));
	/* wait until done refreshing */
	while (!(inp(INPUT_STATUS) & VRETRACE));
	/* copy double buffer to memory */
	memcpy(VGA,double_buffer,320*200);
}

void draw_rect(int left, int top, int right, int bottom, byte color)
{
	word top_offset, bottom_offset, width, i;

	top_offset 	= (top<<8) + (top<<6) + left;
	bottom_offset 	= (bottom<<8) + (bottom<<6) + left;
	width		= right - left + 1;

	for( i=top_offset; i<=bottom_offset; i+=SCREEN_WIDTH ) {
		memset(&double_buffer[i],color,width);	
	}
}
