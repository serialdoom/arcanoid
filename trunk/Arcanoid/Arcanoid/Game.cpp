/* Implementation of the Game.h */

#include "Game.h"


#define CONFIG_FILE "./game.cfg"
#define BUFF_SZ 20321
#define BALL "ball"


Game::Game(void){
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

	//Open file for data extraction
	KeyLogger::Write("Opening \"%s\" to read the data...\n", CONFIG_FILE);
	set_config_file(CONFIG_FILE);

	KeyLogger::Write("Initiallizing filmsInfo...\n");
	filmsInfo = new LoadFilmsInfo(get_config_string("GENERAL", "films", ""));

	KeyLogger::Write("Initiallizing BitMapLoader...\n");
	bitmaps = new BitmapLoader();
	bitmaps->LoadFilms(*(filmsInfo));

	KeyLogger::Write("Initiallizing	Animation Film Holder...\n");
	afh = new AnimationFilmHolder(get_config_string("GENERAL", "animationHolder", ""), (*filmsInfo), (*bitmaps));


	KeyLogger::Write("Initiallizing Terrain Builder...\n");
	tbuilder = new TerrainBuilder(cc, sp, afh);

	KeyLogger::Write("Loading the terrain...\n");
	tbuilder->Load(get_config_string("GENERAL", "level_file", ""), get_config_string("FILMS", "brick", ""));

	KeyLogger::Write("Creating the ball...\n");
	Ball *theBall = new Ball(get_config_int("BALL", "start_x", 0), get_config_int("BALL", "start_y", 0), afh, get_config_string("FILMS", "ball", ""));
	cc->AddMovable(dynamic_cast<Sprite *>(theBall));
	sp->Insert(BALL, dynamic_cast<Sprite *>(theBall));

	return;
}
