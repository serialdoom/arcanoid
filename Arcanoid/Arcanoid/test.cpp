/* Testing file for Acranoid project */

#include <allegro.h>
#include <iostream>


using std::cout;
using std::endl;

#include "Point.h"
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


	bitmaps.Load("./images/editorsScreen.bmp");
	BITMAP * buffy = load_bitmap("./images/editorsScreen.bmp", NULL);
	//bitmaps.Load("./images/ballFilm.bmp");
	//blit(bitmaps.Load("./images/editorsScreen.bmp"), screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

	blit( bitmaps.Load("./images/editorsScreen.bmp" ) , screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

	/*int i =  0;
	while( start != end ){
cout<<"++++++++++++++++++++++++++++++++++++++++++"<<endl;
		blit( bitmaps.Load( (*start).second.second.c_str() ) , screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		start++;
	}*/

	//bitmaps.Load("./images/editorsScreen.bmp");
	cout<<"Number of bitmaps"<<bitmaps.GetSize()<<endl;


	//readkey();

/////////////////////////////////////////////////////////////////////
//xrhsh ths AnimationFilmHolder kai AnimationFilm

	AnimationFilmHolder holder("./configs_files/bboxes/", filmsInfo, bitmaps);

	

	const AnimationFilm * film	= holder.GetFilm("bricksFilm");
	//const AnimationFilm * film2 = holder.GetFilm("ballFilm");
	const AnimationFilm * film3 = holder.GetFilm("ballsFilm");
	const AnimationFilm * film4 = holder.GetFilm("boardFilm");

	const Oblong * rect = film->GetFrameBox(0);
/*
	film->DisplayFrame(screen, new Point(20,240), 0);
	film->DisplayFrame(screen, new Point(40,240), 1);
	film->DisplayFrame(screen, new Point(60,240), 2);
	film->DisplayFrame(screen, new Point(80,240), 3);
	film->DisplayFrame(screen, new Point(100,240), 4);
	film->DisplayFrame(screen, new Point(120,240), 5);
	film->DisplayFrame(screen, new Point(130,240), 6);
	film->DisplayFrame(screen, new Point(140,240), 7);
	film->DisplayFrame(screen, new Point(160,240), 8);
	film->DisplayFrame(screen, new Point(180,240), 9);
	film->DisplayFrame(screen, new Point(200,240), 10);
	film->DisplayFrame(screen, new Point(210,240), 11);
	film->DisplayFrame(screen, new Point(220,240), 12);
	film->DisplayFrame(screen, new Point(240,240), 13);
	film->DisplayFrame(screen, new Point(260,240), 14);
	film->DisplayFrame(screen, new Point(280,240), 15);
	film->DisplayFrame(screen, new Point(300,240), 16);
	film->DisplayFrame(screen, new Point(320,240), 17);

	film2->DisplayFrame(screen, new Point(30, 240), 0);
	film3->DisplayFrame(screen, new Point(42, 240), 0);
	film3->DisplayFrame(screen, new Point(52, 240), 1);
	film3->DisplayFrame(screen, new Point(62, 240), 2);
	film3->DisplayFrame(screen, new Point(72, 240), 3);
*/
	//film4->DisplayFrame(screen, new Point(500, 240), 0);

	//film->DisplayFrame(film->GetBitmap, new Poit(4,4), 3);
	//

#define MAX_DELAY 25000000
	unsigned int delay = MAX_DELAY;
	int x = 200;

	while( !key[KEY_ESC] ) {
		blit( bitmaps.Load("./images/editorsScreen.bmp" ) , buffy, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		film4->DisplayFrame(buffy, new Point(x, 240), 0);
		//while( delay != 0 ){ delay--; }
		blit(buffy , screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		
		//delay = MAX_DELAY;
		x += 15;
		if( x >= 550 )
			x = 200;
	}
	cout<<"AnimationFilmHolder size"<<holder.GetSize()<<endl;;

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


	//readkey();


	return 0;
}
END_OF_MAIN()