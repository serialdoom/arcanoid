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



	LoadFilmsInfo filmsInfo("./configs_files/films.cfg");
	FilmsInfoMap test = filmsInfo.GetFilmsInfo();

	BitmapLoader bitmaps;
	bitmaps.LoadFilms(filmsInfo);
	bitmaps.Load("./images/editorsScreen.bmp");
	BITMAP * buffer = load_bitmap("./images/editorsScreen.bmp", NULL);

	blit( bitmaps.Load("./images/editorsScreen.bmp" ) , screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

	AnimationFilmHolder holder("./configs_files/bboxes/", filmsInfo, bitmaps);
	const AnimationFilm * board = holder.GetFilm("boardFilm");
	
	
	SpriteHolder spriteHolder;
	Board space( 244, 460, const_cast<AnimationFilm*>(board), "boardFilm");
	spriteHolder.Insert("boardFilm", &space );
	

	InputManager input;

	int x = 200;
	int y = 460;
	StateHolder::Init();
	while( !key[KEY_ESC] ) {
		int l;
		if( l = key[KEY_P]){ 
			cout<<">"<< l <<"<"<<endl;
			cout<<">"<< KEY_P <<"<"<<"\n\n\n"<<endl;
			return 0;
		}
		input.CheckInput( spriteHolder.GetSprite("boardFilm")->second );

		blit( bitmaps.Load("./images/editorsScreen.bmp" ) , buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		board->DisplayFrame(buffer, space.GetPointUpLeft(), 0);
		blit(buffer , screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	}
	
	return 0;
}
END_OF_MAIN()