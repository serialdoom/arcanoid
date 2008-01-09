/*
 *author: koutsop
 */
#include "Brick.h"


Brick::Brick(	const int _frameNum, 
				const Point up, 
				const Point down, 
				const int w, const int h, 
				const bool _canBreak, 
				const int _timesToBreak, 
				const int _score, 
				const bool _isActive) :	frameNum(_frameNum),
										Oblong(up, down, w, h),
										canBreak(_canBreak),
										timesToBreak(_timesToBreak),
										score(_score),
										isActive(_isActive){ }

Brick::Brick(	const int _frameNum, 
				const Point * const up, 
				const Point * const down, 
				const int w, const int h, 
				const bool _canBreak, 
				const int _timesToBreak, 
				const int _score, 
				const bool _isActive) :	frameNum(_frameNum),
										Oblong(up, down, w, h),
										canBreak(_canBreak),
										timesToBreak(_timesToBreak),
										score(_score),
										isActive(_isActive){ }


Brick::~Brick(void){}


void Brick::Copy(Brick* brick){
	assert(brick);
	
	this->SetFrameNum( brick->GetFrameNum() );
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
