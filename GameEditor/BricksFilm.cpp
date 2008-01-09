/*
 *author: koutsop
 */
#include "BricksFilm.h"

BricksFilm::BricksFilm(void){
	width		= 0;
	height		= 0;
	numOfBricks = 0;
}

BricksFilm::~BricksFilm(void){}

BITMAP *BricksFilm::LoadBitmapBricks(BITMAP *source){
	if( !(source = load_bitmap(fileNameBricksFilm.c_str(), NULL)) ){
		allegro_message(fileNameBricksFilm.c_str());
		exit(-1);
	}
	return source;
}


//8a prepei na exei ginei prwta to load_blit gia to source kai to dest
void BricksFilm::BlitBricks(BITMAP *source, BITMAP *dest){
	assert(bricks.size() == numOfBricks);
	assert(source);
	assert(dest);

	for( unsigned int i = 0; i < bricks.size(); i++ ){
		int w	 = bricks.at(i)->GetWidth();
		int h	 = bricks.at(i)->GetHeight();
		int source_x = bricks.at(i)->GetFrameNum() * width;
		int source_y = 0;
		int dest_x	 = bricks.at(i)->GetPointUpLeft().GetX();
		int dest_y	 = bricks.at(i)->GetPointUpLeft().GetY();
		blit(source, dest, source_x, source_y, dest_x, dest_y, w, h);
	}//end of for

	return;
}


Brick* BricksFilm::GetBrick(unsigned int i) const {
	assert( bricks.size() > i );
	return bricks.at(i);
}

brickContainer BricksFilm::GetAllBricks(void)	const{
	return bricks;
}
