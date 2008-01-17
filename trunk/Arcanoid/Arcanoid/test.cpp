/* Testing file for Acranoid project */

#include <allegro.h>
#include <iostream>


using std::cout;
using std::endl;

#include "Point.h"
#include "Board.h"
#include "StateHolder.h"
#include "SpriteHolder.h"
#include "BitmapLoader.h"
#include "InputManager.h"
#include "LoadFilmsInfo.h"
#include "AnimationFilmHolder.h"

#include "Game.h"

int main(){
	//Game *theGame = new Game();

	/////_------------ Initialize all the necessary parts of alllegro
	allegro_init();			
	install_timer();
	install_keyboard();		
	install_mouse();

	set_color_depth(16);	
	set_gfx_mode(GFX_AUTODETECT, 640,480,0,0); 
	//set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640,480,0,0); 
	


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
	
	Board space( 244, 460, const_cast<AnimationFilm*>(board), "boardFilm");
	spriteHolder.Insert("boardFilm", &space );
	

	/////------------- Create InputManager
	InputManager input;

	/////------------- Initialize State Holder
	StateHolder::Init();
	while( !key[KEY_ESC] ) {
		/////------------- Check imput
		input.CheckInput( spriteHolder.GetSprite("boardFilm")->second );

		/////------------- All den blits
		blit(baground, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		if( space.IsVisible() )
			board->DisplayFrame(buffer, space.GetPointUpLeft(), 0);
		blit(buffer , screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	}
	
	return 0;
}
END_OF_MAIN()