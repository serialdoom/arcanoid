#include <iostream>
#include <allegro.h>
#include "game.h"

#define GRAPHICS 1

int main( int argc, char *argv[]){

	Game *the_game = new Game(1);


	the_game->play();
/*
// WORKING !!!
	BITMAP *my_pic = NULL;

	int x= 1280, y = 1024;
	allegro_init();
	install_timer();
	install_keyboard();

	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT, x, y, 0, 0);

	if(!(my_pic = load_bitmap("resources/board.bmp", NULL))) {
		allegro_message("Error while loading the pic.\n");
		return 1;
	}
	blit(my_pic, screen, 0, 0, 0, 0, x, y);

	//set_window_title("hey hey there!");
	//text_mode(makecol(0, 0, 255));
	//textout_centre(screen, font, "Hello World!!!", 0, 0, makecol(255, 255, 0));

	
*/
	return 0;
}

END_OF_MAIN()