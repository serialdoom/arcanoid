#include "game.h"

bool Game::Init(char *config_file){
	return true;
}

Game::Game(/*int hasGraphics*/){
#if 0
	if(hasGraphics){
		allegro_init();
		install_keyboard();
		set_color_depth(32);
		set_gfx_mode(GFX_AUTODETECT/*_WINDOWED*/, 1280, 1024, 0, 0);
	}
	the_ball = new Ball("./resources/ballz.bmp");
	int width = 78, height = 27;
	the_board = new Board(78, 27, "./resources/board.bmp");
	the_board->setspeed(5);
	the_ball->setspeed(1);
	if(!(background = load_bitmap("./resources/gamescreen.bmp", NULL))){
		allegro_message("Error while loading the background.\n");
		exit(1);
	}
	clear_keybuf();
	//Inniting double buffering crap;
	buffy = create_bitmap(SCREEN_W, SCREEN_H);
#endif
}


void Game::play(void){
#if 0
	while( !(key[KEY_ESC]) ){
		the_ball->move();
		if(key[KEY_LEFT]){
			the_board->moveleft();
		} else if(key[KEY_RIGHT]){
			the_board->moveright();
		}else {
			// i just dont know what to do with my self
		}
		blit(background, buffy, 0, 0, 0, 0, background->w, background->h);
		the_ball->display(buffy);
		the_board->display(buffy);
		blit(buffy, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	}
#endif
}
Game::~Game(void){
	//delete the_ball;
}
