#include <algorithm>

#include "AI.h"
#include "KeyLogger.h"
#include "MyTime.h"


#define TIME_BRICK_STOP 10
#define TIME_BRICK_MOVE 1



void AI::AIBricks(SpriteHolder* sh){
	timestamp_t theTime	= MyTime::GetSystemTime();
	static timestamp_t msec	= 0;
	static bool insert1 = false;		//Ta brick prepei na stamatisoun gia TOME_BRICK_MOVE sec

	if( !msec )  { msec = theTime;}		
	else{
		timestamp_t time = MyTime::GetSystemDiffTimeInSec(theTime, msec);
		if( time <= TIME_BRICK_STOP+TIME_BRICK_MOVE ){
			if( time < TIME_BRICK_STOP && !insert1){
				std::for_each(sh->GetFirst(), sh->GetEnd(), StopBricksFunctor());
				insert1 = true;
			}
			else if( time >= TIME_BRICK_STOP ) {
				std::for_each(sh->GetFirst(), sh->GetEnd(), SetSpeedFunctor(2));
				insert1 = false;
			}
		}//end if
		else { 	msec = 0;  }
	}
	return;
}//end of AIBRICKS;


void AI::AINain(){
}

