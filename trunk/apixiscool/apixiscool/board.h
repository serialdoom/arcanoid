#ifndef __BOARD_H__
#define __BOARD_H__

#include <string>
#include <allegro.h>

using namespace std;
class Board{

private:
	int board_w, board_h, pos_x, pos_y, speed;
	string filename;
	BITMAP *board_bmp;

public:
	Board(int width, int height, char *filename);
	void moveleft();
	void moveright();
	void display(BITMAP *board);
	void setspeed(int speed);
	~Board();
};

#endif