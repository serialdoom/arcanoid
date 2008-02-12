#include "PowerUp.h"
#include "PowerUpSpr.h"
#include "AnimatorHolder.h"
#include "MovingAnimator.h"
#include "MovingAnimation.h"



#define MONEY_BONUS 1000
#define BUFF_SZ 12341

const char * PowerUp::AppendIntegerToString( string str, int i){
	char tmpString[BUFF_SZ];
	assert( (str.size()+ i) < BUFF_SZ);
	sprintf_s(tmpString, BUFF_SZ, "%s%d", str.c_str(), i);
	return _strdup(tmpString);
}

PowerUp::PowerUp(AnimationHolder *ah, 
				 AnimationFilmHolder *afh, 
				 SpriteHolder *sp,
				 animid_t &countAnimationID)
{
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
		sp->Insert(NamePowerUp[i], newSprite);

		//add new animation to animation holder
		MovingAnimation * mov = new MovingAnimation(0, 0, 1, true, countAnimationID);
		countAnimationID++;
		ah->Insert(NamePowerUp[i], mov );

		//add to animator Holder
		MovingAnimator * brick = new MovingAnimator();
		brick->Start(sp->GetSprite(NamePowerUp[i]), mov, 2000);
		powerupAnimator.insert( make_pair(NamePowerUp[i], brick) );
		
		brick->Stop();
		AnimatorHolder::Register(brick);
	}//end of for
}



//Elegxei gia kathe brick an periexei dwraki h' oxi
void PowerUp::ApplyBonus(powerups_t gift){

}	


//Edw prepei na kanoume elegxo poso polu grigora mporei na paei h mpala
void PowerUp::SpeedUp(Ball *ball){
	ball->SetSpeedX( ball->GetSpeedX() + 1);
	ball->SetSpeedY( ball->GetSpeedY() + 1);
	return;
}

void PowerUp::SpeedDown(Ball *ball){
	int x = ball->GetSpeedX();
	int y = ball->GetSpeedX();
	if( x > 1 && y > 1){
		ball->SetSpeedX( x - 1);
		ball->SetSpeedY( y - 1);
	}
	return;
}

void PowerUp::Money(int &score, int level){
	score = score + (level * MONEY_BONUS);
	return;
}

void PowerUp::LifeUp(int &lifes){
	lifes++;
	return;
}

void PowerUp::Max(Board* board){
	int frame = board->GetFrame();

	if(frame < 4)
		board->SetFrame(frame+1);
	return;
}

void PowerUp::Min(Board* board){
	int frame = board->GetFrame();
	
	if(frame > 1)
		board->SetFrame(frame-1);
	return;
}