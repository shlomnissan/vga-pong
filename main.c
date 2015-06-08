#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>

#include "types.h"
#include "gfx.h"
#include "input.h"

#define PADDLE_WIDTH	8
#define PADDLE_HEIGHT	40

void clear_screen(void);
void animate_ball(void);
void draw_paddles(void);
void collision_detection(void);
void pc_ai(void);

point ball_speed 	= { 2,2 };
point ball_position 	= { SCREEN_WIDTH >> 1, SCREEN_HEIGHT >> 1 };
point player_position	= { 10, 10 };
point pc_position	= { SCREEN_WIDTH - 18, SCREEN_HEIGHT - 50 };

int player_speed	= 2;
int pc_speed		= 2;


int main(void) {

	int key 	= 0;

	set_mode(VGA_256_MODE);
	init_buffer();	

	key = readKeyboard();

	/* Game Loop */
	while(key != KEY_ESCAPE) {

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

		pc_ai();		

		draw_paddles();
		animate_ball();
		collision_detection();
		sync_v();
		clear_screen();
	}

	end_buffer();

	set_mode(TEXT_MODE);

	return 0;

}

void clear_screen(void)
{
	draw_rect( ball_position.x - 1  , ball_position.y - 1, ball_position.x + 1, ball_position.y + 1, 0x0);
	draw_rect( player_position.x, player_position.y, player_position.x + PADDLE_WIDTH, player_position.y + PADDLE_HEIGHT, 0x0 );
	draw_rect( pc_position.x, pc_position.y, pc_position.x + PADDLE_WIDTH, pc_position.y + PADDLE_HEIGHT, 0x0 );
}

void animate_ball(void)
{
	ball_position.x += ball_speed.x;
	ball_position.y += ball_speed.y;

	draw_rect( ball_position.x - 1  , ball_position.y - 1, ball_position.x + 1, ball_position.y + 1, 0xf);	
	
	if( ball_position.x >= SCREEN_WIDTH - 2 || ball_position.x <= 2 ) {
		ball_speed.x *= -1;
	}

	if( ball_position.y >= SCREEN_HEIGHT || ball_position.y <= 0 ) {
		ball_speed.y *= -1;
	}
}

void draw_paddles(void)
{
	draw_rect( player_position.x, player_position.y, player_position.x + PADDLE_WIDTH, player_position.y + PADDLE_HEIGHT, 0xf );
	draw_rect( pc_position.x, pc_position.y, pc_position.x + PADDLE_WIDTH, pc_position.y + PADDLE_HEIGHT, 0xf );

}

void collision_detection(void)
{

	// Player
	if( ball_position.x <= player_position.x + PADDLE_WIDTH && ball_position.y > player_position.y && ball_position.y < player_position.y + PADDLE_HEIGHT ) {
		ball_position.x = player_position.x + PADDLE_WIDTH + 1;
		ball_speed.x *= -1;
	}

	// Computer
	if( ball_position.x + 1 >= pc_position.x && ball_position.y > pc_position.y && ball_position.y < pc_position.y + PADDLE_HEIGHT ) {
		ball_position.x = pc_position.x - 1;
		ball_speed.x *= -1;
	}

}

void pc_ai(void)
{
	int pc_paddle_center = pc_position.y + (PADDLE_HEIGHT >> 1);

	if( ball_speed.x < 0 ) {

		// Go back to center of the screen
		if( pc_paddle_center > (SCREEN_HEIGHT >> 1) + 1 ) {
			pc_position.y -= pc_speed;
		} else if( pc_paddle_center < (SCREEN_HEIGHT >> 1) - 1 ) {
			pc_position.y += pc_speed;
		}


	} else {

		// Predict
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
		
}
