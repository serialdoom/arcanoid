/*
 *author: koutsop
 */
#include <ctime> 
#include <cstdlib>

#include "Brick.h"


#define BRICK_SPEED 2

//constructor
Brick::Brick(	int x, int y,
				AnimationFilm* film,
				const int w, const int h,
				const int _score,
				const char frameNo,
				const bool _isActive,
				const bool _canBreak, 
				const char _timesToBreak,
				const string _id ) :	Sprite(x, y, film),								
										score(_score),
										isActive(_isActive),
										canBreak(_canBreak),
										timesToBreak(_timesToBreak),
										id(_id)
{
	SetWidth(w);
	SetHeight(h);
	SetFrame(frameNo);
	up			= false;
	speed		= BRICK_SPEED;
	isRunning	= false;
	SetGift( static_cast<powerups_t>(CalculateRandomPowerUp()) );
}



//overload constructor 1
Brick::Brick(	const Point  point,
				AnimationFilm* film,
				const int w, const int h,
				const int _score,
				const char frameNo,
				const bool _isActive,
				const bool _canBreak, 
				const char _timesToBreak,
				const string _id ) :	Sprite(point, film),
										score(_score),
										isActive(_isActive),
										canBreak(_canBreak),
										timesToBreak(_timesToBreak),
										id(_id)
{
	SetWidth(w);
	SetHeight(h);
	SetFrame(frameNo);
	up			= false;
	speed		= BRICK_SPEED;
	isRunning	= false;
	SetGift(static_cast<powerups_t>(CalculateRandomPowerUp()) );
}

//overload constructor 2
Brick::Brick(	const Point * const point,
				AnimationFilm* film,
				const int w, const int h,
				const int _score,
				const char frameNo,
				const bool _isActive,
				const bool _canBreak, 
				const char _timesToBreak,
				const string _id ) :	Sprite(point, film),
										score(_score),
										isActive(_isActive),
										canBreak(_canBreak),
										timesToBreak(_timesToBreak),
										id(_id)
{
	SetWidth(w);
	SetHeight(h);
	SetFrame(frameNo);
	up			= false;
	speed		= BRICK_SPEED;
	isRunning	= false;
	SetGift(static_cast<powerups_t>(CalculateRandomPowerUp()) );
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

void Brick::Move(const int dx, const int dy) {
	if( isRunning ){
		if( !up ){ 
			SetPosition(GetPosition().GetX(), GetPosition().GetY()+speed);
			up = true;
		}
		else{
			SetPosition(GetPosition().GetX(), GetPosition().GetY()-speed);
			up = false;
		}
	}
	return;
}


bool Brick::QuestionDeath(){
	assert(this->GetTimesToBreak() >= 0);
	if(this->GetCanBreak() && this->GetTimesToBreak() == 1){
		this->SetIsActive(true);
		GameStats::IncreaseScore(this->GetScore());
		GameStats::IncreaseBrick(-1);
		return true;
	} else if( this->GetCanBreak() && this->GetTimesToBreak() >1){
		this->SetTimesToBreak( this->GetTimesToBreak() - 1);
		this->SetFrame(this->GetFrame() - 1);
	} else {
		//brick cant break;
	}
	return false;
}


int Brick::CalculateRandomPowerUp(){
    srand((unsigned)time(0)); 
    int random_integer; 
    int lowest=0, highest=16; 
    int range=(highest-lowest)+1;
    random_integer = lowest+int(range*rand()/(RAND_MAX + 1.0)); 
	
	int giftArray[MAX_POWER+1];

	for( int i = MAX; i < NONE; i++)
		giftArray[i] = i;

	return giftArray[random_integer];
   
}
