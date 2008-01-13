/*
 * author: koutsop
 */

#include "Sprite.h"

Sprite::Sprite(int x, int y, AnimationFilm* film) : currFilm(film){
	assert(film);
	isVisible	= true;
	frameNo		= currFilm->GetTotalFrames();
	SetFrame(0);
	SetPointUpLeft(x, y);
}


Sprite::Sprite(Point point, AnimationFilm* film) : currFilm(film){
	assert(film);
	isVisible	= true;
	frameNo		= currFilm->GetTotalFrames();
	SetFrame(0);
	SetPointUpLeft(point);
}


Sprite::Sprite(const Point * const point, AnimationFilm* film) : currFilm(film){
	assert(film);
	isVisible	= true;
	frameNo		= currFilm->GetTotalFrames();
	SetFrame(0);
	SetPointUpLeft(point);
}

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