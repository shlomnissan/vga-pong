#ifndef GFX_H
#define GFX_H

#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include "types.h"

#define VIDEO_INT	0x10
#define SET_MODE	0x00
#define VGA_256_MODE	0x13
#define TEXT_MODE	0x03
#define SCREEN_WIDTH	320
#define SCREEN_HEIGHT	200
#define NUM_COLORS	256

#define INPUT_STATUS	0x3da
#define	VRETRACE	0x08

#define VGA 		((byte *)0xA0000000L) // Pointer to video

void set_mode(byte mode);

void init_buffer(void);
void end_buffer(void);
void sync_v(void);
void clear_buffer(void);
void put_pixel(int x, int y, int color);
void draw_rect(int left, int top, int right, int bottom, byte color);


#endif
