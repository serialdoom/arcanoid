/* Implementation of the Game.h */

#include "Game.h"


#define CONFIG_FILE "./game.cfg"
#define BUFF_SZ 20321
#define BALL "ball"


Game::Game(void){
	const char *tmp;

	KeyLogger::Write("Alegro initiallization...\n");
	allegro_init();

	//Innits
	KeyLogger::Init("arcanoid.log");
	KeyLogger::Write("KeyLogger is up and running.\n");

	KeyLogger::Write("Initiallizing ColLision Checker...\n");
	cc = new CollisionChecker();
	
	KeyLogger::Write("Initiallizing StateHolder...\n");
	StateHolder::Init();
	
	KeyLogger::Write("Initiallizing SpriteHolder...\n");
	sp = new SpriteHolder();

	set_config_file(CONFIG_FILE);

	KeyLogger::Write("Initiallizing filmsInfo...\n");
	tmp = get_config_string("GENERAL", "films", "");
	if(!strcmp(tmp, "")) assert(0);
	push_config_state();
	filmsInfo = new LoadFilmsInfo(tmp);
	pop_config_state();


	KeyLogger::Write("Initiallizing BitMapLoader...\n");
	bitmaps = new BitmapLoader();
	assert(filmsInfo);
	bitmaps->LoadFilms(*(filmsInfo)); // problem...

	KeyLogger::Write("Initiallizing	Animation Film Holder...\n");
	tmp = get_config_string("GENERAL", "animationHolder", "");
	if(!strcmp(tmp, "")) assert(0);
	assert(filmsInfo);
	assert(bitmaps);

	push_config_state();
	afh = new AnimationFilmHolder(tmp, (*filmsInfo), (*bitmaps));
	pop_config_state();


	KeyLogger::Write("Initiallizing Terrain Builder...\n");
	tbuilder = new TerrainBuilder(cc, sp, afh);

	set_config_file(CONFIG_FILE);
	KeyLogger::Write("Loading the terrain...\n");
	tbuilder->Load(get_config_string("GENERAL", "level_file", ""), get_config_string("FILMS", "brick", ""));

//	KeyLogger::Write("Creating the ball...\n");
//	Ball *theBall = new Ball(get_config_int("BALL", "start_x", 0), get_config_int("BALL", "start_y", 0), afh, get_config_string("FILMS", "ball", ""));
//	cc->AddMovable(dynamic_cast<Sprite *>(theBall));
//	sp->Insert(BALL, dynamic_cast<Sprite *>(theBall));

	return;
}
