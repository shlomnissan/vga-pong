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

	top_offset 		= (top<<8) + (top<<6) + left;
	bottom_offset 	= (bottom<<8) + (bottom<<6) + left;
	width			= right - left + 1;

	for( i=top_offset; i<=bottom_offset; i+=SCREEN_WIDTH ) {

		memset(&double_buffer[i],color,width);
	
	}

}

/*

void load_bitmap(char *file, BITMAP *b) {

	long 	index;
	int 	x;
	FILE 	*fp;
	word 	num_colors;

	if ( (fp = fopen(file, "rb")) == NULL ) {
		
		printf("Error opening file %s.\n", file);
		exit(1);

	}

	if ( fgetc(fp) != 'B' || fgetc(fp) != 'M' ) {
		
		fclose(fp);
		printf("%s is not a bitmap file.\n");
		exit(1);

	}

	fskip(fp,16);
	fread(&b->width, sizeof(word), 1, fp);

	fskip(fp, 2);
	fread(&b->height, sizeof(word), 1, fp);

	fskip(fp, 22);
	fread(&num_colors, sizeof(word), 1, fp);

	fskip(fp, 6);

	if( num_colors == 0 ) {
		
		num_colors = 256;

	}

	// allocate the memory
  if( (b->data = (byte *)malloc( (word)( b->width * b->height ) ) ) == NULL ) {

    fclose(fp);
    printf("Error allocating memory for file %s.\n",file);
    exit(1);

  }

  // read the palette
  for( index = 0; index < num_colors; index++ ) {

    b->palette[(int)(index*3+2)] = fgetc(fp) >> 2;
    b->palette[(int)(index*3+1)] = fgetc(fp) >> 2;
    b->palette[(int)(index*3+0)] = fgetc(fp) >> 2;

    x = fgetc(fp);

  }

  // read the bitmap
  for( index = (b->height - 1) * b->width; index >= 0; index -= b->width ) {

    for( x=0; x<b->width; x++ ) {

      b->data[(word)index+x] = (byte)fgetc(fp);

    }

  }

  fclose(fp);

}*/

void draw_bitmap(BITMAP *bitmap, int x, int y) {

  int j;
  word screen_offset  = (y << 8) + (y << 6) + x;
  word bitmap_offset  = 0;

  for( j=0; j<bitmap->height; j++ ) {

    memcpy(&VGA[screen_offset], &bitmap->data[bitmap_offset], bitmap->width);

    bitmap_offset += bitmap->width;
    screen_offset += SCREEN_WIDTH;

  }

}

void set_palette(byte *palette) {

	int i;

	outp(0x03c8, 0);

	for( i=0; i<256*3; i++ ) {

		outp(0x03c9, palette[i]);

	}

}

void fskip(FILE *fp, int num_bytes) {

  int i;

  for( i=0; i<num_bytes; i++ ) {
    fgetc(fp);
  }

}