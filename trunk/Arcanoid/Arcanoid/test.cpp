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


	allegro_init();			// Initialize Allegro
	install_timer();
	install_keyboard();		// Initialize keyboard routines
	install_mouse();

	set_color_depth(16);	// Set the color depth
	set_gfx_mode(GFX_AUTODETECT, 640,480,0,0); 
	//set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640,480,0,0); // Change our graphics mode to 640x480
	
	set_window_title("Game Editor (koutsop@csd.uoc.gr)");	


	/////_------------ Load films data
	LoadFilmsInfo filmsInfo("./configs_files/films.cfg");
	FilmsInfoMap test = filmsInfo.GetFilmsInfo();

	/////------------- Load all den bitmaps
	BitmapLoader bitmaps;
	bitmaps.LoadFilms(filmsInfo);
	bitmaps.Load("./images/editorsScreen.bmp");
	bitmaps.Load("./images/bufferEditorsScreen.bmp");
	blit( bitmaps.Load("./images/editorsScreen.bmp" ) , screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);


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

	/////------------- Init State Holder
	StateHolder::Init();
	while( !key[KEY_ESC] ) {
		/////------------- Check impit
		input.CheckInput( spriteHolder.GetSprite("boardFilm")->second );

		/////------------- All den blits
		blit( bitmaps.Load("./images/editorsScreen.bmp" ) , buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		board->DisplayFrame(buffer, space.GetPointUpLeft(), 0);
		blit(buffer , screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	}
	
	return 0;
}
END_OF_MAIN()