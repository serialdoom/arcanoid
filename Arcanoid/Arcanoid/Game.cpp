/* Implementation of the Game.h */

#include "Game.h"


#define CONFIG_FILE "./game.cfg"
#define BUFF_SZ 20321
#define BALL "ball"


Game::Game(void){
	const char *tmp1, *tmp2;
	int temp1, temp2;

	KeyLogger::Write("Alegro initiallization...\n");
	allegro_init();
	install_timer();
	install_keyboard();		// Initialize keyboard routines
	install_mouse();

	set_color_depth(16);	// Set the color depth
	//set_gfx_mode(GFX_AUTODETECT, 640,480,0,0); 
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640,480,0,0); // Change our graphics mode to 640x480


	//Innits
	KeyLogger::Init("arcanoid.log");
	KeyLogger::Write("KeyLogger is up and running.\n");

	KeyLogger::Write("Initiallizing ColLision Checker...\n");
	cc = 0;
	cc = new CollisionChecker();
	assert(cc);
	
	KeyLogger::Write("Initiallizing StateHolder...\n");
	StateHolder::Init();
	
	KeyLogger::Write("Initiallizing SpriteHolder...\n");
	sp = 0;
	sp = new SpriteHolder();
	assert(sp);

	set_config_file(CONFIG_FILE);

	KeyLogger::Write("Initiallizing filmsInfo...\n");
	tmp1 = 0;
	tmp1 = get_config_string("GENERAL", "films", "");
	if(!strcmp(tmp1, "")) assert(0);
	push_config_state();
	filmsInfo = 0;
	filmsInfo = new LoadFilmsInfo(tmp1);
	assert(filmsInfo);
	pop_config_state();


	KeyLogger::Write("Initiallizing BitMapLoader...\n");
	bitmaps = 0;
	bitmaps = new BitmapLoader();
	assert(bitmaps);
	bitmaps->LoadFilms(*(filmsInfo));

	KeyLogger::Write("Initiallizing	Animation Film Holder...\n");
	tmp1 = 0;
	tmp1 = get_config_string("GENERAL", "animationHolder", "");
	if(!strcmp(tmp1, "")) assert(0);

	push_config_state();
	afh = 0;
	afh = new AnimationFilmHolder(tmp1, (*filmsInfo), (*bitmaps));
	assert(afh);
	pop_config_state();


	KeyLogger::Write("Initiallizing Terrain Builder...\n");
	tbuilder = 0;
	tbuilder = new TerrainBuilder(cc, sp, afh);
	assert(tbuilder);

	KeyLogger::Write("Loading the terrain...\n");
	tmp1 = tmp2 = 0;
	tmp1 = get_config_string("GENERAL", "level_file", "");
	tmp2 = get_config_string("FILMS", "brick", "");
	if(!strcmp(tmp1, "")) assert(0);
	if(!strcmp(tmp2, "")) assert(0);

	push_config_state();
	tbuilder->Load(tmp1, tmp2);
	pop_config_state();

	KeyLogger::Write("Creating the ball...\n");
	tmp1 = 0;
	temp1 = temp2 = -1;
	temp1 = get_config_int("BALL", "start_x", 0);
	temp2 = get_config_int("BALL", "start_y", 0);
	tmp1 = get_config_string("FILMS", "ball", "");
	if(temp1 == -1) assert(0);
	if(temp2 == -1) assert(0);

	Ball *theBall = new Ball(temp1, temp2, afh->GetFilm(tmp1), tmp1);
	assert(theBall);
//	cc->AddMovable(dynamic_cast<Sprite *>(theBall));
//	sp->Insert(BALL, dynamic_cast<Sprite *>(theBall));

	return;
}
