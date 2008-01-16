/*
 * author: koutsop
 */

#include "Sprite.h"


//test
Sprite::Sprite(int upper_x, int upper_y, int down_x, int down_y){
	SetPointUpLeft(new Point(upper_x, upper_y));
	SetPointDownRight(new Point(down_x, down_y));
}
//end of test


Sprite::Sprite(int x, int y, AnimationFilm* film) : currFilm(film){
	assert(film);
	isVisible	= true;
	frameNo		= currFilm->GetTotalFrames();
	SetFrame(0);
	SetPointUpLeft(x, y);
}

/////////////////////////////////////////////////////////////////////

Sprite::Sprite(Point point, AnimationFilm* film) : currFilm(film){
	assert(film);
	isVisible	= true;
	frameNo		= currFilm->GetTotalFrames();
	SetFrame(0);
	SetPointUpLeft(point);
}

/////////////////////////////////////////////////////////////////////

Sprite::Sprite(const Point * const point, AnimationFilm* film) : currFilm(film){
	assert(film);
	isVisible	= true;
	frameNo		= currFilm->GetTotalFrames();
	SetFrame(0);
	SetPointUpLeft(point);
}

/////////////////////////////////////////////////////////////////////

void Sprite::SetFrame (char i) {	
	if (i != frameNo) {
		assert(i < currFilm->GetTotalFrames());
		const Oblong *tmp  = currFilm->GetFrameBox(frameNo = i);
		this->SetWidth( tmp->GetWidth() );
		this->SetHeight( tmp->GetHeight() );
		this->SetPointUpLeft( tmp->GetPointUpLeft() );
	}
	return;
}

/////////////////////////////////////////////////////////////////////

void Sprite::Move(const int dx, const int dy){
	SetPointUpLeft( GetPointUpLeft().GetX() + dx, GetPointUpLeft().GetY() + dy);
	return;
}

/////////////////////////////////////////////////////////////////////

void Sprite::Move(const Point point){
	SetPointUpLeft( GetPointUpLeft().GetX() + point.GetX(), 
					GetPointUpLeft().GetY() + point.GetY()
				  );
	return;
}

/////////////////////////////////////////////////////////////////////

void Sprite::Move(const Point* point){
	SetPointUpLeft( GetPointUpLeft().GetX() + point->GetX(), 
					GetPointUpLeft().GetY() + point->GetY()
				  );
	return;
}
