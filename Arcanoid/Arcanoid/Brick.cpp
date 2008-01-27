/*
 *author: koutsop
 */
#include "Brick.h"

	int  score;
	char timesToBreak; 
	bool canBreak, isActive;	


//constructor
Brick::Brick(	int x, int y,
				AnimationFilm* film,
				const int w, const int h,
				const int _score,
				const char frameNo,
				const bool _isActive,
				const bool _canBreak, 
				const char _timesToBreak ) :	Sprite(x, y, film),								
												score(_score),
												isActive(_isActive),
												canBreak(_canBreak),
												timesToBreak(_timesToBreak)
{
	SetWidth(w);
	SetHeight(h);
	SetFrame(frameNo);
	spriteType = SPRITE_BRICK;
}



//overload constructor 1
Brick::Brick(	const Point  point,
				AnimationFilm* film,
				const int w, const int h,
				const int _score,
				const char frameNo,
				const bool _isActive,
				const bool _canBreak, 
				const char _timesToBreak ) :	Sprite(point, film),
												score(_score),
												isActive(_isActive),
												canBreak(_canBreak),
												timesToBreak(_timesToBreak)
{
	SetWidth(w);
	SetHeight(h);
	SetFrame(frameNo);
	spriteType = SPRITE_BRICK;
}

//overload constructor 2
Brick::Brick(	const Point * const point,
				AnimationFilm* film,
				const int w, const int h,
				const int _score,
				const char frameNo,
				const bool _isActive,
				const bool _canBreak, 
				const char _timesToBreak ) :	Sprite(point, film),
												score(_score),
												isActive(_isActive),
												canBreak(_canBreak),
												timesToBreak(_timesToBreak)
{
	SetWidth(w);
	SetHeight(h);
	SetFrame(frameNo);
	spriteType = SPRITE_BRICK;
}

void Brick::Copy(Brick* brick){
	assert(brick);
	
	this->SetFrame( brick->GetFrame() );
	this->GetPointUpLeft().SetX( brick->GetPointUpLeft().GetX() );
	this->GetPointUpLeft().SetY( brick->GetPointUpLeft().GetY() );
	
	this->GetPointDownRight().SetX( brick->GetPointDownRight().GetX() );
	this->GetPointDownRight().SetY( brick->GetPointDownRight().GetY() );

	this->SetWidth( brick->GetWidth() );
	this->SetHeight( brick->GetHeight() );

	this->SetCanBreak( brick->GetCanBreak() );
	this->SetTimesToBreak( brick->GetTimesToBreak() );
	this->SetScore( brick->GetScore() );

	this->SetIsActive( brick->IsActive() );

	return;
}

void Brick::Collide(Sprite *s){
	//TODO: wtite code.
	return;
}