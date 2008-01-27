/*
 * author: koutsop
 */

#include <cassert>
#include "Sprite.h"




Sprite::Sprite(int upper_x, int upper_y, int down_x, int down_y){
	SetPointUpLeft(upper_x, upper_y);
	SetPointDownRight(down_x, down_y);
}
/////////////////////////////////////////////////////////////////////



Sprite::Sprite(int x, int y, AnimationFilm* film) : currFilm(film){
	assert(film);
	isVisible	= true;
	frameNo		= currFilm->GetTotalFrames();
	SetFrame(0);
	position.SetX(x);
	position.SetY(y);
}
/////////////////////////////////////////////////////////////////////



Sprite::Sprite(Point point, AnimationFilm* film) : currFilm(film){
	assert(film);
	isVisible	= true;
	frameNo		= currFilm->GetTotalFrames();
	SetFrame(0);
	position.SetX(point.GetX());
	position.SetY(point.GetY());
}
/////////////////////////////////////////////////////////////////////



Sprite::Sprite(const Point * const point, AnimationFilm* film) : currFilm(film){
	assert(film);
	isVisible	= true;
	frameNo		= currFilm->GetTotalFrames();
	SetFrame(0);
	position.SetX(point->GetX());
	position.SetY(point->GetY());
}
/////////////////////////////////////////////////////////////////////



void Sprite::SetFrame (char i) {	
	
	if (i != frameNo) {
		assert(i < currFilm->GetTotalFrames());
		const Oblong *tmp  = currFilm->GetFrameBox(frameNo = i);
		SetWidth( tmp->GetWidth() );
		SetHeight( tmp->GetHeight() );
		SetPointUpLeft( tmp->GetPointUpLeft() );
		SetPointDownRight( tmp->GetPointDownRight() );
	}
	return;
}
/////////////////////////////////////////////////////////////////////



void Sprite::Move(const int dx, const int dy){
	SetPointUpLeft( GetPointUpLeft().GetX() + dx, GetPointUpLeft().GetY() + dy);
	return;
}
/////////////////////////////////////////////////////////////////////



bool Sprite::CollisionCheck(Sprite* s){
	int x1, y1, x2, y2, x3, y3, x4, y4;

	x1 = this->GetPointUpLeft().GetX();
	y1 = this->GetPointUpLeft().GetY();

	x2 = this->GetPointDownRight().GetX();
	y2 = this->GetPointDownRight().GetY();

	x3 = s->GetPointUpLeft().GetX();
	y3 = s->GetPointUpLeft().GetY();

	x4 = s->GetPointDownRight().GetX();
	y4 = s->GetPointDownRight().GetY();
	
	if( (x4 < x1) || (x2 < x3) || (y4 < y1) || (y2 < y3) )
		return false;
	Collide(s);

	return true;
}
/////////////////////////////////////////////////////////////////////



void Sprite::Display(BITMAP *bitmap){
	assert(bitmap);
	currFilm->DisplayFrame(bitmap,  position, frameNo);
	return;
}
/////////////////////////////////////////////////////////////////////



void Sprite::SetPosition(int x, int y){
	position.SetX(x);
	position.SetY(y);
	return;
}
