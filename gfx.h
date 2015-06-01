#ifndef GFX_H
#define GFX_H

#define VIDEO_INT	0x10
#define SET_MODE	0x00
#define VGA_256_MODE	0x13
#define TEXT_MODE	0x03
#define SCREEN_WIDTH	320
#define SCREEN_HEIGHT	200
#define NUM_COLORS	256

typedef unsigned char	byte;
typedef unsigned short 	word;

#define VGA 		((byte *)0xA0000000L) // Pointer to video

void set_mode(byte mode);
void put_pixel(int x, int y, int color);
void draw_rect(int left, int top, int right, int bottom, byte color);

#endif
