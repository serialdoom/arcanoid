/* Testing file for Acranoid project */

#include <allegro.h>
#include <iostream>


using std::cout;
using std::endl;

#include "BitmapLoader.h"
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
	//set_gfx_mode(GFX_AUTODETECT, 640,480,0,0); 
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640,480,0,0); // Change our graphics mode to 640x480
	
	set_window_title("Game Editor (koutsop@csd.uoc.gr)");	



//////////////////////////////////////////////////////////////////////
//xrhsh ths LoadFilmsInfo
	LoadFilmsInfo filmsInfo("./configs_files/films.cfg");

	FilmsInfoMap test = filmsInfo.GetFilmsInfo();
	FilmsInfoMap::iterator start	= test.begin();
	FilmsInfoMap::iterator end		= test.end();

	cout<<">"<<filmsInfo.GetFilmsNo()<<"<"<<endl;
	while( start != end ){
		cout<<"id\t:"<<(*start).first<<endl;
		cout<<"bboxes\t:"<<(*start).second.first<<endl;
		cout<<"bitmap\t:"<<(*start).second.second<<endl;
		start++;
	}
/////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////
//xrhsh ths BitmapLoad

	BitmapLoader bitmaps;
	bitmaps.LoadFilms(filmsInfo);
	start = test.begin();

	int i =  0;
	while( start != end ){
		blit( bitmaps.Load( (*start).second.second.c_str() ) , screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		start++;
	}

	readkey();

/////////////////////////////////////////////////////////////////////
//xrhsh ths AnimationFilmHolder kai AnimationFilm

	AnimationFilmHolder holder("./configs_files/bboxes/", filmsInfo, bitmaps);

	const AnimationFilm * film = holder.GetFilm("bricksFilm");
	const Oblong * rect = film->GetFrameBox(0);

	cout<<"===============================\n"<<endl;
	cout<<rect->GetPointUpLeft().GetX()<<endl;
	cout<<rect->GetPointUpLeft().GetY()<<endl;
	cout<<rect->GetPointDownRight().GetX()<<endl;
	cout<<rect->GetPointDownRight().GetY()<<endl;
	cout<<rect->GetWidth()<<endl;
	cout<<rect->GetHeight()<<endl;
	cout<<film->GetId()<<endl;

	int filmNo = film->GetTotalFrames();
	cout<<">"<<filmNo<<"<"<<endl;


	readkey();

	return 0;
}
END_OF_MAIN()