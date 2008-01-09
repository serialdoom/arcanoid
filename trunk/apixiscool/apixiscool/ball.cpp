
#include "ball.h"
#include <iostream>

Ball::Ball(char *filename){
	going_left = 1;
	going_up = 0;
	pos_x = 15;
	pos_y = 15;
	ball_bmp = NULL;
	if(!(ball_bmp = load_bitmap(filename, NULL))){
		allegro_message("Error while loading the ball.\n");
		exit(1);
	}
}


void Ball::move(void){
	//fprintf(stdout, "ball: pos_x + ball_bmp->w = %d left:%d, up:%d (%d, %d).\n", pos_x + ball_bmp->w, going_left, going_up, pos_x, pos_y);

	if(pos_x + ball_bmp->w >= SCREEN_W) going_left=1;
	else if(pos_x <= 0) going_left=0;
	else {;}
	
	if(pos_y + ball_bmp->h >= SCREEN_H) going_up=1;
	else if(pos_y <= 0) going_up=0;
	else {;}

	if(going_left) pos_x -= speed;
	else pos_x += speed;
	if(going_up) pos_y -= speed;
	else pos_y += speed;

}

void Ball::setspeed(int speedo){
	speed = speedo;
}
void Ball::display( BITMAP *buffy){
	masked_blit(ball_bmp, buffy, 0, 0, pos_x, pos_y, ball_bmp->w, ball_bmp->h);
	return;
}