#include "board.h"

Board::Board(int width, int height, char *filename){
	pos_x = SCREEN_W/2;
	pos_y = SCREEN_H - 100;
	filename = filename;
	board_bmp = NULL;
	if(!(board_bmp = load_bitmap(filename, NULL))){
		allegro_message("Error while loading the board.\n");
		exit(1);
	}
	return;
}

void Board::moveleft(){
	if(pos_x >= 0){
		pos_x -= speed;
	}
}

void Board::moveright(){
	if(pos_x + board_bmp->w <= SCREEN_W){
		pos_x += speed;
	}
}
void Board::display(BITMAP *buffer){
	blit(board_bmp, buffer, 0, 0, pos_x, pos_y, board_bmp->w, board_bmp->h);
	return;
}

void Board::setspeed(int s){
	speed = s;
}