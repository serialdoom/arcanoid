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
	blit(baground, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);


	/////------------- Add to Animation Holder all the films
	AnimationFilmHolder holder("./configs_files/bboxes/", filmsInfo, bitmaps);

	/////------------- Take specific AnimationFilm mporoume to kane auto gia megaliterh taxhthta
	const AnimationFilm * board = holder.GetFilm("boardFilm");
	
	/////------------- Create spriteHolder and sprites
	SpriteHolder spriteHolder;
	
	Board space( 244, 460, const_cast<AnimationFilm*>(board));
	spriteHolder.Insert("boardFilm", &space );
	

	/////------------- Create InputManager
	InputManager input;

	/////------------- Create MovingAnimation for board
	MovingAnimation boardAnimation(244,460,1,true,1);

	/////------------- Create and start Moving animator for board
	MovingAnimator boardAnimator;
	boardAnimator.Start(spriteHolder.GetSprite("boardFilm")->second, &boardAnimation, 0);


	/////------------- Register the animatorHolder
	AnimatorHolder::Register(&boardAnimator);

	/////------------- Initialize State Holder
	StateHolder::Init();
	
	while( !key[KEY_ESC] ) {
		 SetGameTime();
		/////------------- Check imput kanonika edw eprepe na einai o animatorHolder san orisma
		input.CheckInput(&boardAnimator);

		/////------------- Progress all animator in animator holder
		AnimatorHolder::Progress(GetGameTime());

		/////------------- All ten blits
		blit(baground, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		if( space.IsVisible() )
			board->DisplayFrame(buffer, space.GetPointUpLeft(), 0);
		/*rect(buffer, 
				space.GetPointUpLeft().GetX(), 
				space.GetPointUpLeft().GetY(), 
				space.GetPointDownRight().GetX(), 
				space.GetPointDownRight().GetY(), 
				makecol(255, 0, 0));
		*/
		blit(buffer , screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	}
	return 0;
//#endif
	assert(0);
}
END_OF_MAIN()