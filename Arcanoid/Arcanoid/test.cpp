/* Testing file for Acranoid project */


#include <ctime>
#include <iostream>
#include <allegro.h>



using std::cout;
using std::endl;

#include "Point.h"
#include "Board.h"
#include "Animator.h"
#include "StateHolder.h"
#include "SpriteHolder.h"
#include "BitmapLoader.h"
#include "InputManager.h"
#include "LoadFilmsInfo.h"
#include "AnimatorHolder.h"
#include "MovingAnimator.h"
#include "MovingAnimation.h"
#include "AnimationFilmHolder.h"



#include "Game.h"






//#define _APIX_
//#define _KOUTSOP_

static unsigned long currTime = 0;
void SetGameTime(){ currTime = time((time_t *)0); }
unsigned long GetGameTime(void){ return currTime; }




int main(){
//#ifdef _APIX_
//	Game *theGame = new Game();
//	return 0;
//#endif

//#ifdef _KOUTSOP_
	/////_------------ Initialize all the necessary parts of alllegro
	allegro_init();			
	install_timer();
	install_keyboard();		
	install_mouse();

	set_color_depth(16);	
	//set_gfx_mode(GFX_AUTODETECT, 640,480,0,0); 
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640,480,0,0); 
	


	/////_------------ Load films data
	LoadFilmsInfo filmsInfo("./configs_files/films.cfg");
	FilmsInfoMap test = filmsInfo.GetFilmsInfo();

	/////------------- Load all den bitmaps
	BitmapLoader bitmaps;
	bitmaps.LoadFilms(filmsInfo);

	BITMAP* baground	= bitmaps.Load("./images/editorsScreen.bmp");
	BITMAP* buffer		= bitmaps.Load("./images/bufferEditorsScreen.bmp");


	/////------------- Add to Animation Holder all the films
	AnimationFilmHolder holder("./configs_files/bboxes/", filmsInfo, bitmaps);

	/////------------- Take specific AnimationFilm
	const AnimationFilm * board  = holder.GetFilm("boardFilm");
	const AnimationFilm * board2 = holder.GetFilm("boardFilm");
	
	/////------------- Create spriteHolder and sprites
	SpriteHolder spriteHolder;
	
	Board space( 244, 460, const_cast<AnimationFilm*>(board));
	Board space2( 444, 460, const_cast<AnimationFilm*>(board2));
	spriteHolder.Insert("boardFilm", &space );
	spriteHolder.Insert("boardFilm2", &space2 );


	/////------------- Create InputManager
	InputManager input;

	/////------------- Create MovingAnimation for board
	MovingAnimation boardAnimation(244,460,1,true,1);
	MovingAnimation boardAnimation2(444,460,1,true,1);


	/////------------- Create and start Moving animator for board
	MovingAnimator boardAnimator;
	MovingAnimator boardAnimator2;
	boardAnimator.Start(spriteHolder.GetSprite("boardFilm")->second, &boardAnimation, 0);
	boardAnimator2.Start(spriteHolder.GetSprite("boardFilm2")->second, &boardAnimation2, 0);

	/////------------- Register the animatorHolder
	AnimatorHolder::Register(&boardAnimator);
	AnimatorHolder::Register(&boardAnimator2);
	/////------------- Initialize State Holder
	
	StateHolder::Init();
	bool isRunning		= false;
	bool isSuspended	= true;		//otan kanoume register mpenei kai sto suspend

	bool isRunning2		= false;
	bool isSuspended2	= true;		//otan kanoume register mpenei kai sto suspend

	KEY tmp;

	while( !key[KEY_ESC] ) {
		SetGameTime();
		
///////////////////////////////////////////////////////////////////////////////////////////
		if( ((tmp = input.CheckInput()) != Key_None) && (tmp != Key_A) && (tmp != Key_D) ){
			//cout<<"Input is: "<<StateHolder::GetKey()<<endl;
			space.SetKey(tmp);
			if( !isRunning ){		//Gia prwth fora mpenei sthn lista me ta running
				AnimatorHolder::MarkAsRunning(&boardAnimator);
				isRunning	= true;
				isSuspended	= false;
			}
			if(tmp == Key_Mouse_Left || tmp == Key_Mouse_Right)
				boardAnimation.SetDx(input.GetOldMouseX());
		}

		else{
			//cout<<"None input from keyboard"<<std::endl;
			if( !isSuspended ){	//Gia prwth fora sthn lista me ta suspended
				AnimatorHolder::MarkAsSuspended(&boardAnimator);
				isRunning	= false;
				isSuspended	= true;
			}
		}
/////////////////////////////////////////////////////////////////////////////////////////////

		if( ((tmp = input.CheckInput()) != Key_None) && ((tmp == Key_A) || (tmp == Key_D))){
			space2.SetKey(tmp);
			if( !isRunning2 ){		//Gia prwth fora mpenei sthn lista me ta running
				AnimatorHolder::MarkAsRunning(&boardAnimator2);
				isRunning2	= true;
				isSuspended2	= false;
			}
		}

		else{
			if( !isSuspended2 ){	//Gia prwth fora sthn lista me ta suspended
				AnimatorHolder::MarkAsSuspended(&boardAnimator2);
				isRunning2	= false;
				isSuspended2	= true;
			}
		}






		/////------------- Progress all animator in animator holder
		AnimatorHolder::Progress(GetGameTime());

		/////------------- All ten blits
		blit(baground, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		if( space.IsVisible() )
			board->DisplayFrame(buffer, space.GetPointUpLeft(), 0);

		rect(	buffer,
				space2.GetPointUpLeft().GetX(),
				space2.GetPointUpLeft().GetY()-1,
				space2.GetPointDownRight().GetX(),
				space2.GetPointDownRight().GetY(),
				makecol(255,0,0)
			);

		if(space2.IsVisible())
			board2->DisplayFrame(buffer, space2.GetPointUpLeft(), 0);
		
		blit(buffer , screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	}
	return 0;
}
END_OF_MAIN()