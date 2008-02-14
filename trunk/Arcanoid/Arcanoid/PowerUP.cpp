#include "PowerUp.h"

#include "Brick.h"
#include "GameStats.h"
#include "PowerUpSpr.h"
#include "MovingAnimator.h"
#include "MovingAnimation.h"
#include <string>

#define MONEY_BONUS 1000
#define BUFF_SZ 12341

Ball*	PowerUp::ball;
Board*	PowerUp::board;

std::vector< std::pair<powerups_t, Point> > PowerUp::powersToExecute;
AnimatorMap		PowerUp::powerupAnimator;
string			PowerUp::NamePowerUp[MAX_POWER];

SpriteHolder * PowerUp::tsp;


void PowerUp::Init( AnimationHolder *ah, 
					AnimationFilmHolder *afh, 
					SpriteHolder *sp,
					CollisionChecker *ss,
					animid_t &countAnimationID,
					Ball* _ball,
					Board* _board)
{
	tsp = sp;
	ball = _ball;
	board = _board;
	NamePowerUp[MAX]			= "max";	
	NamePowerUp[MIN]			= "min";
	NamePowerUp[STIC]			= "stic";
	NamePowerUp[LIFE_UP]		= "lifeUp";
	NamePowerUp[CLONE_BALL]		= "cloneBall";
	NamePowerUp[SPEED_UP]		= "speedUp";
	NamePowerUp[SPEED_DOWN]		= "speedDown";
	NamePowerUp[DESTRUCTION]	= "destruction";
	NamePowerUp[EXPLOSION]		= "explosion";
	NamePowerUp[BUCKLER]		= "buckler";
	NamePowerUp[BAD]			= "bad";
	NamePowerUp[MONEY]			= "money";
	NamePowerUp[BOMB]			= "bomb";
	NamePowerUp[BANANA]			= "banana";
	NamePowerUp[FIRE]			= "fire";
	NamePowerUp[MONEY_X2]		= "moneyX2";

	for(int i = MAX;i< NONE; ++i){
		//add new prite to sprite holder
		PowerUpSpr *newSprite = new PowerUpSpr(new Point(0, 0), const_cast<AnimationFilm*>(afh->GetFilm("powerupsFilm")));
		newSprite->SetFrame(i);
		newSprite->SetBonusType(i);
		sp->Insert(NamePowerUp[i], newSprite);
		ss->AddPowerUp(newSprite);

		//add new animation to animation holder
		MovingAnimation * mov = new MovingAnimation(0, 0, 1, true, countAnimationID);
		countAnimationID++;
		ah->Insert(NamePowerUp[i], mov );

		//add to animator Holder
		MovingAnimator * brick = new MovingAnimator();
		brick->Start(sp->GetSprite(NamePowerUp[i]), mov, 2000);
		powerupAnimator.insert( make_pair(NamePowerUp[i], brick) );
		
		//brick->Stop();
		AnimatorHolder::Register(brick);
		
		//Edw einai na diagraftoun auta
		AnimatorHolder::MarkAsRunning(brick);
	}//end of for
}


void PowerUp::clear(void){ powersToExecute.clear(); return; }

//Elegxei gia kathe brick an periexei dwraki h' oxi
void PowerUp::ApplyBonus(SpriteHolder *sp, AnimationHolder *ah){
	std::vector< std::pair<powerups_t, Point> >::iterator start	= powersToExecute.begin();
	std::vector< std::pair<powerups_t, Point> >::iterator end	= powersToExecute.end();
	
	while( start != end ){
		if(start->first != NONE ){
			Sprite* sprite = sp->GetSprite(NamePowerUp[start->first]);	//pernoume to spite
			if( !sprite->IsVisible() ){
				sprite->SetVisibility(true);								//makeAsVisibi
				sprite->SetPosition(start->second);							//set potition
			}
			start++;
		}
	}
	powersToExecute.clear();
	return;
}	

void PowerUp::Bomb(void){
	SpriteMap::iterator start	= tsp->GetFirst();
	SpriteMap::iterator	end		= tsp->GetEnd();

	while( start != end ){
		if( dynamic_cast<Brick *>(start->second) &&  dynamic_cast<Brick *>(start->second)->GetTimesToBreak() >1){
			dynamic_cast<Brick *>(start->second)->SetFrame(dynamic_cast<Brick *>(start->second)->GetFrame() - dynamic_cast<Brick *>(start->second)->GetTimesToBreak() + 1);
			dynamic_cast<Brick *>(start->second)->SetTimesToBreak(1);
		}
		start++;
	}
	return;
}



void PowerUp::DesplayAll(BITMAP * bitmap, SpriteHolder *sp){
	for( int i = MAX; i < NONE; i++) { 
		Sprite * sprite = sp->GetSprite(NamePowerUp[i]);
		if( sprite->IsVisible() )
			sprite->Display(bitmap);
	}
	return;
}
/////////////////////////////////////////////////////////////////////



void PowerUp::SpeedUp(void){
	if( ball->GetSpeedX() < ball->GetMaxSpeed() && ball->GetSpeedY() < ball->GetMaxSpeed()){
		ball->SetSpeedX( ball->GetSpeedX() + 1);
		ball->SetSpeedY( ball->GetSpeedY() + 1);
	}
	return;
}

void PowerUp::Destruction(void){
	ball->SetFuckLevel(true);
	return;
}

void PowerUp::Explosion(void){
	ball->SetFuckLevel(true);
}

void PowerUp::DoubleMoney(void){
	GameStats::SetDoubleBricks(true);
	return;
}

void PowerUp::Banana(void){
	ball->SetFrame((ball->GetFrame() == 3)?0:ball->GetFrame()+1);
	return;
}

void PowerUp::Bad(void){
	ball->SetSpeedX(ball->GetMaxSpeed());
	ball->SetSpeedY(ball->GetMaxSpeed());
	board->SetFrame(0);
	return;
}

void PowerUp::SpeedDown(void){
	int x = ball->GetSpeedX();
	int y = ball->GetSpeedX();
	if( x > 1 && y > 1){
		ball->SetSpeedX( x - 1);
		ball->SetSpeedY( y - 1);
	}
	return;
}

void PowerUp::Money(){
	GameStats::IncreaseScore(GameStats::GetScore() + 1000);
	return;
}

void PowerUp::LifeUp(){
	GameStats::IncreaseLife(1);
	return;
}

void PowerUp::Max(){		//ok
	int frame = board->GetFrame();

	if(frame < 4)
		board->SetFrame(frame+1);
	return;
}

void PowerUp::Min(){		//ok
	int frame = board->GetFrame();
	
	if(frame > 0)
		board->SetFrame(frame-1);
	return;
}