
#include <string>
#include "PowerUp.h"

#define BUFF_SZ 12341

const char * PowerUp::AppendIntegerToString( string str, int i){
	char tmpString[BUFF_SZ];
	assert( (str.size()+ i) < BUFF_SZ);
	sprintf_s(tmpString, BUFF_SZ, "%s%d", str.c_str(), i);
	return _strdup(tmpString);
}


PowerUp::PowerUp(AnimationHolder *ah, AnimationFilmHolder *afh, SpriteHolder *sp, int countAnimationID, const char *configFileName){
	const char *name = get_config_string("POWERUP", "location", 0);
	push_config_state();
	set_config_file(name);
	int max = get_config_int("POWERUP", "totalNumber", -1);
	assert( max != -1);

	for(int i = 0;i< max;++i){
		const char *name = AppendIntegerToString("position_", i);
		int pos = get_config_int("POWERUP", name, -1);
		assert(pos != -1);
		name = AppendIntegerToString("name_", i);
		NamePowerUp[pos] = get_config_string("POWERUP", name, 0);
		assert(NamePowerUp[pos].length());
		PowerUpSpr *newSprite = new PowerUpSpr(new Point(0, 0), const_cast<AnimationFilm*>(afh->GetFilm("powerupsFilm")));
		newSprite->SetFrame(pos);
		sp->Insert(NamePowerUp[pos], newSprite);

		MovingAnimation * mov = new MovingAnimation(0, 0, 1, true, countAnimationID);
		countAnimationID++;
		ah->Insert(NamePowerUp[pos], mov );

		//add to animator Holder
		MovingAnimator * brick = new MovingAnimator();
		brick->Start(sp->GetSprite(NamePowerUp[pos]), mov, 2000);
		powerupAnimator.insert( make_pair(NamePowerUp[pos], brick) );
		AnimatorHolder::Register(brick);
		AnimatorHolder::MarkAsSuspended(brick);
	}


	pop_config_state();
	return;
}



//Elegxei gia kathe brick an periexei dwraki h' oxi
void PowerUp::ApplyBonus(string gift){

	/*
	if(gift.compare("none"))
		;
	else{
		for(int i=0; i<MAX_POWER; i++){
			if(this->NamePorewUp[i].compare(gift)){

				;
			}
		}
	}
*/
}	