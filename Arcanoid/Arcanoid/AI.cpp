/*
 *author: koutsop
 */

#include <algorithm>

#include "AI.h"
#include "KeyLogger.h"
#include "MyTime.h"
#include "Terrain.h"


#define TIME_BRICK_STOP 7
#define TIME_BRICK_MOVE 1

#define NAIN_TIME	10



void AI::AIBricks(SpriteHolder* sh){
	timestamp_t theTime	= MyTime::GetSystemTime();
	static timestamp_t msec	= 0;
	static bool insert1 = false;		//mono mia fora se TIME_BRICK_STOP sec na kanei thn for_each
	static bool insert2 = false;		//mono mia fora se TIME_BRICK_MOVE sec na kanei thn for_each

	if( !msec )  { msec = theTime;}		
	else{
		timestamp_t time = MyTime::GetSystemDiffTimeInSec(theTime, msec);
		if( time <= TIME_BRICK_STOP+TIME_BRICK_MOVE ){
			if( time < TIME_BRICK_STOP && !insert1){
				std::for_each(sh->GetFirst(), sh->GetEnd(), StopBricksFunctor());
				insert1 = true;
				insert2 = false;
			}
			else if( time >= TIME_BRICK_STOP && !insert2  ) {
				std::for_each(sh->GetFirst(), sh->GetEnd(), SetSpeedFunctor());
				insert1 = false;
				insert2 = true;
			}
		}//end if
		else { 	msec = 0; }
	}
	return;
}//end of AIBRICKS;


void AI::AINain(NainSpin *nain, int dx, int dy){
	timestamp_t theTime	= MyTime::GetSystemTime();
	static timestamp_t msec	= 0;

	if( !msec )  { msec = theTime;}		
	else{
		timestamp_t time = MyTime::GetSystemDiffTimeInSec(theTime, msec);
		if( time >= NAIN_TIME && !nain->IsVisible() ){
			nain->SetPosition(dx, dy);
			nain->SetVisibility(true);
			msec = 0;
		}
	}
	return;

}

