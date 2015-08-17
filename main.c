#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#include <time.h>

#include "types.h"
#include "gfx.h"
#include "input.h"

#include "logo.h"

#define PADDLE_WIDTH	5
#define PADDLE_HEIGHT	30

void clear_screen(void);
void animate_ball(void);
void draw_paddles(void);
void collision_detection(void);
void pc_ai(void);
void logo_screen(void);
void game_loop(void);

point ball_speed 	= { 2, 2 };
point ball_position 	= { SCREEN_WIDTH >> 1, SCREEN_HEIGHT >> 1 };
point player_position	= { 7, 10 };
point pc_position	= { SCREEN_WIDTH - 12, SCREEN_HEIGHT - 50 };

float player_speed	= 2;
float pc_speed		= 1.8;

int player_score	= 0;
int pc_score	 	= 0;
int game_state		= 0;
int key 			= 0;
int is_hero			= 0;
int is_init			= 0;

clock_t	begin;

double 	time_spent;

unsigned int reset = FALSE;

int main(void) {

	set_mode(VGA_256_MODE);
	init_buffer();	

	key = readKeyboard();

	/* Game Loop */
	while(key != KEY_ESCAPE) {

		switch( game_state ) {

			case 0:

				logo_screen();

				break;

			case 1:

				game_loop();

				break;

		}

		key = readKeyboard();

	}

	end_buffer();
	
	set_mode(TEXT_MODE);

	printf("Player score: %i\n", player_score);
	printf("Computer score: %i\n\n", pc_score);
	printf("Thanks for playing! This game was coded in 2015 by 1Byte Beta.\nVisit: www.1bytebeta.com/labs to find out more.\n\n", pc_score);
	return 0;

}

void logo_screen(void)
{

	BITMAP bitmap;

	if( is_hero == 0 ) {

		bitmap.width 	= 128;
		bitmap.height 	= 32;
		bitmap.data 	= logo_data;

		memset(&VGA[0],7,64000); // clear screen
		
		set_palette(logo_palette);
		
  		draw_bitmap(&bitmap, ( SCREEN_WIDTH - bitmap.width ) >> 1,  ( SCREEN_HEIGHT - bitmap.height ) >> 1 );

  		is_hero = 1;

	}

	key = readKeyboard();

	if( key == SPACE_BAR ) {

		free(bitmap.data);

		set_mode(VGA_256_MODE);

		clear_buffer();

		game_state = 1;

	}

}

void game_loop(void)
{

	if( reset == TRUE ) {
		
		time_spent = (double)(clock() - begin) / CLOCKS_PER_SEC;
		
		if( time_spent >= 1.0 ) {

			time_spent = 0;
			ball_position.x = SCREEN_WIDTH >> 1;
			ball_position.y = SCREEN_HEIGHT >> 1;
			reset = FALSE;
		}
	}

	key = readKeyboard();			
	
	if( key == KEY_DOWN_D ) {
		
		if( player_position.y <= SCREEN_HEIGHT - 12 - PADDLE_HEIGHT ) {
			
			player_position.y += player_speed;					

		}

	} else if( key == KEY_UP_D ) {
	
		if( player_position.y >= 12 ) {
			
			player_position.y -= player_speed;					

		}
		
	}
	
	if( reset == FALSE ) {
		pc_ai();				
		animate_ball();					
	}

	draw_paddles();
	collision_detection();

	if( is_init == 0 ) {

		is_init = 1;

		draw_rect(160,0, 161, 200, 0xf);

	}

	sync_v();
	clear_screen();

}

void clear_screen(void)
{	

	draw_rect( ball_position.x - 1  , ball_position.y - 1, ball_position.x + 1, ball_position.y + 1, 0x0);
	
	// redraw the portion of the half-court that has been erased by the clearing the ball
	if( ball_position.x > 157 && ball_position.x < 163 ) {

		draw_rect(160,ball_position.y - 1, 161, ball_position.y + 1, 0xf);

	} 

	draw_rect( player_position.x, player_position.y, player_position.x + PADDLE_WIDTH, player_position.y + PADDLE_HEIGHT, 0x0 );
	draw_rect( pc_position.x, pc_position.y, pc_position.x + PADDLE_WIDTH, pc_position.y + PADDLE_HEIGHT, 0x0 );
}

void animate_ball(void)
{
	ball_position.x += ball_speed.x;
	ball_position.y += ball_speed.y;

	draw_rect( ball_position.x - 1  , ball_position.y - 1, ball_position.x + 1, ball_position.y + 1, 0xf);	
	
	if( ball_position.x >= SCREEN_WIDTH - 2 || ball_position.x <= 2 ) {
		
		if( ball_speed.x > 0 ) {
			++player_score;
		} else {
			++pc_score;
		}
		
		begin = clock();	

		reset = TRUE;
	}

	if( ball_position.y >= SCREEN_HEIGHT || ball_position.y <= 0 ) {
		ball_speed.y *= -1;
	}
}

void draw_paddles(void)
{
	draw_rect( player_position.x, player_position.y, player_position.x + PADDLE_WIDTH, player_position.y + PADDLE_HEIGHT, 0xf );
	draw_rect( pc_position.x, pc_position.y, pc_position.x + PADDLE_WIDTH, pc_position.y + PADDLE_HEIGHT, 0xf );

	gotoxy(17,20);
	printf("%i", player_score);
	gotoxy(24,20);
	printf("%i", pc_score);

}

void collision_detection(void)
{

	// Player collision

	if( ball_position.x <= player_position.x + PADDLE_WIDTH && ball_position.y > player_position.y && ball_position.y < player_position.y + PADDLE_HEIGHT ) {
		ball_position.x = player_position.x + PADDLE_WIDTH + 1;
		ball_speed.x *= -1;
	}

	// Computer collision

	if( ball_position.x + 1 >= pc_position.x && ball_position.y > pc_position.y && ball_position.y < pc_position.y + PADDLE_HEIGHT ) {
		ball_position.x = pc_position.x - 1;
		ball_speed.x *= -1;
	}

}

void pc_ai(void)
{
	int pc_paddle_center = pc_position.y + (PADDLE_HEIGHT >> 1);

	if( ball_position.y != pc_paddle_center ) {

		if( ball_position.y < pc_paddle_center ) {
			
			if( pc_position.y > 10 ) {

				pc_position.y -= pc_speed;						

			}

		} else {
			
			if( pc_position.y + PADDLE_HEIGHT <= SCREEN_HEIGHT - 10 ) { 

				pc_position.y += pc_speed;

			}

		}

	}
}
