/*
 * author: koutsop
 */

#include "Terrain.h"

#include "GameStats.h"
#include <iostream>

using std::cout;
using std::endl;

int		Terrain::width;
int		Terrain::height;	
Point	Terrain::coordinates;




#define MAX_TMP_SIZE	100

static char tmpString[MAX_TMP_SIZE]; //tmp table gia to append string me ari8mou

static char * Append( string str, int i){
	sprintf_s(tmpString, MAX_TMP_SIZE, "%s%d", str.c_str(), i);
	return tmpString;
}


Terrain::Terrain(string _cgf, 
				 AnimationFilmHolder * afh, 
				 CollisionChecker * cc, 
				 AnimationHolder * ah,
				 SpriteHolder * sh) :cfg(_cgf)
{
	terrainB = new TerrainBuilder(cc, sh, afh, ah);
	assert(terrainB);

	LoadingLevelsInfo();
	LoadingTerrainInfo();
}

Terrain::~Terrain(void){
	delete terrainB;
}

/////////////////////////////////////////////////////////////////////



void Terrain::LoadingLevelsInfo(void){
	set_config_file(cfg.c_str());
	levelsNo	= get_config_int("LEVELS", "levels_files_No", -1);
	levelPath	= get_config_string("LEVELS", "levels_path", "");
	
	assert( levelsNo >= 1 );
	if( !levelPath.compare("") ) { assert(0); }
	return;
}
/////////////////////////////////////////////////////////////////////


void Terrain::LoadingTerrainInfo(void){
	set_config_file(cfg.c_str());

	int w = get_config_int("GENERAL", "terrain_w", -1);
	int h = get_config_int("GENERAL", "terrain_h", -1);
	int x = get_config_int("GENERAL", "terrain_start_x", -1);
	int y = get_config_int("GENERAL", "terrain_start_y", -1);

	assert( (x != -1) && (y != -1) && (w != -1) && (h != -1) );

	width	= w;
	height	= h;
	coordinates.SetX(x);
	coordinates.SetY(y);
	return;
}
/////////////////////////////////////////////////////////////////////



int Terrain::LoadingTerrain(int countAnimationID, int levelNo){
	set_config_file(cfg.c_str());
	string fileName		= get_config_string("LEVELS", Append("level_file_", levelNo), "");
	string bricksFilm	= get_config_string("FILMS", "brick", "");
	
	if( !fileName.compare("") )		{ assert(!"file name"); }
	if( !bricksFilm.compare("") )	{ assert(!"bricks film"); }

	bricksAnimator.clear();
	string lala = levelPath+fileName;
	countAnimationID = terrainB->Load( (levelPath+fileName).c_str(), 
										bricksFilm.c_str(), 
										countAnimationID,
										bricksAnimator);
	return countAnimationID;
}
/////////////////////////////////////////////////////////////////////


//print to screen all den visible bricks
void Terrain::DisplayTerrain(BITMAP *bitmap, SpriteHolder* sh){
	SpriteMap::iterator	start	= sh->GetFirst();
	SpriteMap::iterator	end		= sh->GetEnd();

	while( start != end ){
		Sprite * tmp = sh->GetSprite( start->first );
		if( (dynamic_cast<Brick *>(tmp) != (Sprite*)0) && dynamic_cast<Brick *>(tmp)->IsVisible() )
			tmp->Display(bitmap);
		start++;
	}
	return;
}
/////////////////////////////////////////////////////////////////////


void Terrain::BricksCleanUp(SpriteHolder* sh){
//void Terrain::BricksCleanUp(SpriteHolder* sh , PowerUp	* powerup){
	int cnt = 0;
	std::list<Sprite *> * theList		= sh->GetDelededList();
	std::list<Sprite *>::iterator start = theList->begin();
	std::list<Sprite *>::iterator end	= theList->end();

	while( start != end ){
		Sprite * tmp = (*start);
		if( dynamic_cast<Brick *>(tmp) ){
			//edw elegxw an to brick einai running wtse na to kanw stop
			Animator * anim = bricksAnimator.find( dynamic_cast<Brick *>(tmp)->GetID() )->second;
			if( !anim->HasFinished() ){//einai running animator
				anim->Stop();
				AnimatorHolder::MarkAsSuspended(anim);
			}
			powerups_t gift = dynamic_cast<Brick *>(tmp)->GetGift();
			int x = tmp->GetPosition().GetX();
			int y = tmp->GetPosition().GetY();
			if( gift != NONE )
				PowerUp::AddPowerToExecute( std::pair<powerups_t, Point>(gift, new Point(x, y)));
			//powerup->AddPowerToExecute( std::pair<powerups_t, Point>(gift, new Point(x, y)));
			start++;
			
			//if(dynamic_cast<Brick *>(tmp)->GetTimesToBreak() == 1)
			//	cnt++;

			theList->remove(tmp);
			
			continue;
		}
		start++;
	}//end while
	//GameStats::SetBricksToGo( GameStats::GetBricksToGo() - cnt );
	return;
}
/////////////////////////////////////////////////////////////////////

