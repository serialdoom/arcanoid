/* Testing file for Acranoid project */


#include <ctime>
#include <iostream>
#include <allegro.h>
#include <string>



using std::cout;
using std::endl;

#include "Game.h"
#include "Point.h"
#include "Board.h"
#include "Animator.h"
#include "StateHolder.h"
#include "SpriteHolder.h"
#include "BitmapLoader.h"
#include "InputManager.h"
#include "LoadFilmsInfo.h"
#include "TerrainBuilder.h"
#include "AnimatorHolder.h"
#include "MovingAnimator.h"
#include "MovingAnimation.h"
#include "CollisionChecker.h"
#include "AnimationFilmHolder.h"




#define BUFF_SZ 9999

#define CONFIG_FILE "./configs_files/game.cfg"



//#define _APIX_
//#define _KOUTSOP_


static unsigned long currTime = 0;
void SetGameTime(){ currTime = time((time_t *)0); }
unsigned long GetGameTime(void){ return currTime; }
void Walls(CollisionChecker *cc);

const char * AppendIntegerToString( string str, int i){
	char tmpString[BUFF_SZ];
	assert( (str.size()+ i) < BUFF_SZ);
	sprintf_s(tmpString, BUFF_SZ, "%s%d", str.c_str(), i);
	return _strdup(tmpString);
}


int main(){
//	Game theGame;
//	theGame.PlayGame();
//#if 0
	/////------------- Initialize all the necessary parts of alllegro ok
	allegro_init();			
	install_timer();
	install_keyboard();		
	install_mouse();

	set_color_depth(16);	
	//set_gfx_mode(GFX_AUTODETECT, 640,480,0,0); ok
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640,480,0,0); 
	
	KeyLogger::Init("arcanoid.log");
	KeyLogger::Write("KeyLogger is up and running.\n");

	/////_------------ Load films data ok
	LoadFilmsInfo filmsInfo("./configs_files/films.cfg");
	FilmsInfoMap test = filmsInfo.GetFilmsInfo();

	/////------------- Load all den bitmaps OK
	BitmapLoader bitmaps;
	bitmaps.LoadFilms(filmsInfo);

	BITMAP* baground	= bitmaps.Load("./images/editorsScreen.bmp");
	BITMAP* buffer		= bitmaps.Load("./images/bufferEditorsScreen.bmp");

	CollisionChecker cc;
	
	/////------------- Add to Animation Holder all the films ok
	AnimationFilmHolder holder("./configs_files/bboxes/", filmsInfo, bitmaps);

	/////------------- Take specific AnimationFilm NO
	const AnimationFilm * board  = holder.GetFilm("boardFilm");
	const AnimationFilm * board2 = holder.GetFilm("boardFilm");
	
	/////------------- Create spriteHolder and sprites OK
	SpriteHolder spriteHolder;
	
	Board space( 244, 460, const_cast<AnimationFilm*>(board), 1);
	Board space2( 444, 460, const_cast<AnimationFilm*>(board2), 2);
	spriteHolder.Insert("boardFilm", &space );
	cc.AddMovable(&space);
	spriteHolder.Insert("boardFilm2", &space2 );
	cc.AddMovable(&space);

	//Adding walls
	Walls(&cc);

	/////------------- Create InputManager OK
	InputManager input;

	/////------------- Create MovingAnimation for board
	MovingAnimation boardAnimation(244,460,1,true,1);
	MovingAnimation boardAnimation2(444,460,1,true,1);


	/////------------- Create and start Moving animator for board
	MovingAnimator boardAnimator;
	MovingAnimator boardAnimator2;
	boardAnimator.Start(spriteHolder.GetSprite("boardFilm"), &boardAnimation, 0);
	boardAnimator2.Start(spriteHolder.GetSprite("boardFilm2"), &boardAnimation2, 0);

	/////------------- Register the animatorHolder
	AnimatorHolder::Register(&boardAnimator);
	AnimatorHolder::Register(&boardAnimator2);

	/////------------- Loading the terrain OK
	TerrainBuilder tb(&cc, &spriteHolder, &holder);
	/////------------- Set cfg file
	set_config_file(CONFIG_FILE);
	
	string fileName		= get_config_string("GENERAL", "level_file", "");
	string bricksFilm	= get_config_string("FILMS", "brick", "");
	

	if( !fileName.compare("") )		{ assert(!"file name"); }
	if( !bricksFilm.compare("") )	{ assert(!"bricks film"); }

	tb.Load(fileName.c_str(), bricksFilm.c_str());

	/////------------- display terrain	OK
	SpriteMap::iterator	start	= spriteHolder.GetFirst();
	SpriteMap::iterator	end		= spriteHolder.GetEnd();

	//print to screen all den bricks
	int cnt = 0;
	while( start != end ){
		Sprite * tmp = spriteHolder.GetSprite( AppendIntegerToString("Brick_", cnt ));
		if( (tmp != (Sprite*)0) && tmp->IsVisible() )
			tmp->Display(baground);
		cnt++;
		start++;
	}
	

	
	
	/////------------- Initialize State Holder OK
	StateHolder::Init();
	bool isRunning		= false;
	bool isSuspended	= true;		//otan kanoume register mpenei kai sto suspend

	bool isRunning2		= false;
	bool isSuspended2	= true;		//otan kanoume register mpenei kai sto suspend

	while( !key[KEY_ESC] ) {
		KeyLogger::Write("Begin of the game loop:\n");
		SetGameTime();

		if( input.CheckInput() ){
			space.SetKey(StateHolder::stateKey);
			space2.SetKey(StateHolder::stateKey);

			if( StateHolder::stateKey.Key_Mouse_Left	|| 
				StateHolder::stateKey.Key_Mouse_Right	||
				StateHolder::stateKey.Key_Left			||
				StateHolder::stateKey.Key_Right) 
			{
				boardAnimation.SetDx(input.GetOldMouseX());		//alazoume to dx tou board
				if( !isRunning ){		//Gia prwth fora mpenei sthn lista me ta running
					AnimatorHolder::MarkAsRunning(&boardAnimator);
					isRunning	= true;
					isSuspended	= false;
				}
			}//

			if( StateHolder::stateKey.Key_A ||
				StateHolder::stateKey.Key_D)
			{
				if( !isRunning2 ){		//Gia prwth fora mpenei sthn lista me ta running
					AnimatorHolder::MarkAsRunning(&boardAnimator2);
					isRunning2		= true;
					isSuspended2	= false;
				}
			}//

		}//first if

		else{
			if( !isSuspended ){	//Gia prwth fora sthn lista me ta suspended
				AnimatorHolder::MarkAsSuspended(&boardAnimator);
				isRunning	= false;
				isSuspended	= true;
			}
			if( !isSuspended2 ){	//Gia prwth fora sthn lista me ta suspended
				AnimatorHolder::MarkAsSuspended(&boardAnimator2);
				isRunning2	= false;
				isSuspended2	= true;
			}
		}
///////////////////////////////////////////////////////////////////////////////////////////
	
		//Collisioncheck !
		cc.CollisionCheck();

		/////------------- Progress all animator in animator holder
		AnimatorHolder::Progress(GetGameTime());

		/////------------- All ten blits
		blit(baground, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);


		if( space.IsVisible() )
			space.Display(buffer);

		rect(	buffer,
				space2.GetPosition().GetX(),
				space2.GetPosition().GetY()-1,
				space2.GetPosition().GetX() + space2.GetWidth(),
				space2.GetPosition().GetY() + space2.GetHeight(),
				makecol(255,0,0)
			);

		if(space2.IsVisible())
			space2.Display(buffer);
		
		blit(buffer , screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	}
	return 0;
//#endif
}

void Walls(CollisionChecker *cc){
	const char *tmp1, *tmp2;
	int temp1, temp2, temp3, temp4;

	push_config_state();
	set_config_file("./game.cfg");

	KeyLogger::Write("Creating the Walls...\n");
	//Twelve oclock wall
	temp1 = get_config_int("WALLS", "twelve_up_x", -1);
	temp2 = get_config_int("WALLS", "twelve_up_y", -1);
	temp3 = get_config_int("WALLS", "twelve_down_x", -1);
	temp4 = get_config_int("WALLS", "twelve_down_y", -1);
	if(temp1 == -1 || temp2 == -1 || temp3 == -1 || temp4 == -1) assert(0);
	Wall *twelve = 0;
	twelve = new Wall(temp1, temp2, temp3, temp4);
	assert(twelve);
	cc->AddUnmovable(dynamic_cast<Sprite *>(twelve));

	//three oclock wall
	temp1 = get_config_int("WALLS", "three_up_x", -1);
	temp2 = get_config_int("WALLS", "three_up_y", -1);
	temp3 = get_config_int("WALLS", "three_down_x", -1);
	temp4 = get_config_int("WALLS", "three_down_y", -1);
	if(temp1 == -1 || temp2 == -1 || temp3 == -1 || temp4 == -1) assert(0);
	Wall *three = 0;
	three = new Wall(temp1, temp2, temp3, temp4);
	assert(three);
	cc->AddUnmovable(dynamic_cast<Sprite *>(three));

	//six oclock wall
	temp1 = get_config_int("WALLS", "six_up_x", -1);
	temp2 = get_config_int("WALLS", "six_up_y", -1);
	temp3 = get_config_int("WALLS", "six_down_x", -1);
	temp4 = get_config_int("WALLS", "six_down_y", -1);
	if(temp1 == -1 || temp2 == -1 || temp3 == -1 || temp4 == -1) assert(0);
	Wall *six = 0;
	six = new Wall(temp1, temp2, temp3, temp4);
	assert(six);
	cc->AddUnmovable(dynamic_cast<Sprite *>(six));

	//Nine oclock wall 
	temp1 = get_config_int("WALLS", "nine_up_x", -1);
	temp2 = get_config_int("WALLS", "nine_up_y", -1);
	temp3 = get_config_int("WALLS", "nine_down_x", -1);
	temp4 = get_config_int("WALLS", "nine_down_y", -1);
	if(temp1 == -1 || temp2 == -1 || temp3 == -1 || temp4 == -1) assert(0);
	Wall *nine = 0;
	nine = new Wall(temp1, temp2, temp3, temp4);
	assert(nine);
	cc->AddUnmovable(dynamic_cast<Sprite *>(nine));
	pop_config_state();
}



END_OF_MAIN()