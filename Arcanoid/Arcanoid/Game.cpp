/* Implementation of the Game.h */

#include "Game.h"


#define CONFIG_FILE "./game.cfg"
#define BUFF_SZ 20321
#define BALL "ball"
#define BOARD "board"
#define WALL_12 "upper_wall"
#define WALL_3 "right_wall"
#define WALL_6 "down_wall"
#define WALL_9 "left wall"

Game::Game(void){
	const char *tmp1, *tmp2;
	int temp1, temp2, temp3, temp4;

	//Innits
	KeyLogger::Init("arcanoid.log");
	KeyLogger::Write("KeyLogger is up and running.\n");

	KeyLogger::Write("Alegro initiallization...\n");
	allegro_init();
	install_timer();
	install_keyboard();		// Initialize keyboard routines
	install_mouse();

	set_color_depth(16);	// Set the color depth
	//set_gfx_mode(GFX_AUTODETECT, 640,480,0,0); 
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640,480,0,0); // Change our graphics mode to 640x480



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
	tmp1 = get_config_string("GENERAL", "level_file", "");
	tmp2 = get_config_string("FILMS", "brick", "");
	if(!strcmp(tmp1, "")) assert(0);
	if(!strcmp(tmp2, "")) assert(0);

	push_config_state();
	tbuilder->Load(tmp1, tmp2);
	pop_config_state();

	KeyLogger::Write("Creating the ball...\n");
	temp1 = get_config_int("BALL", "start_x", -1);
	temp2 = get_config_int("BALL", "start_y", -1);
	tmp1 = get_config_string("FILMS", "ball", "");
	if(temp1 == -1) assert(0);
	if(temp2 == -1) assert(0);
	if(!strcmp(tmp1, "")) assert(0);

	// asserting
	Ball *theBall = new Ball(temp1, temp2, const_cast<AnimationFilm *>(afh->GetFilm(tmp1)), tmp1);
	assert(theBall);
	cc->AddMovable(dynamic_cast<Sprite *>(theBall));
	sp->Insert(BALL, dynamic_cast<Sprite *>(theBall));

	KeyLogger::Write("Creating the board...\n");
	temp1 = get_config_int("BOARD", "start_x", -1);
	temp2 = get_config_int("BOARD", "start_y", -1);
	tmp1 = get_config_string("FILMS", "board", "");
	if(temp1 == -1) assert(0);
	if(temp2 == -1) assert(0);

	Board *theBoard = new Board(temp1, temp2, const_cast<AnimationFilm *>(afh->GetFilm(tmp1)));
	assert(theBoard);
	cc->AddMovable(dynamic_cast<Sprite *>(theBoard));
	sp->Insert(BALL, dynamic_cast<Sprite *>(theBoard));

	KeyLogger::Write("Creating the Walls...\n");
	//Twelve oclock wall
	temp1 = get_config_int("WALLS", "twelve_up_x", -1);
	temp2 = get_config_int("WALLS", "twelve_up_y", -1);
	temp3 = get_config_int("WALLS", "twelve_down_x", -1);
	temp4 = get_config_int("WALLS", "twelve_down_y", -1);
	if(temp1 == -1 || temp2 == -1 || temp3 == -1 || temp4 == -1) assert(0);
	Wall *twelve = 0;
	twelve = new Wall(temp1, temp2, temp3, temp4);
	assert(twelve);
	cc->AddUnmovable(dynamic_cast<Sprite *>(twelve));
	sp->Insert(WALL_12, dynamic_cast<Sprite *>(twelve));

	//three oclock wall
	temp1 = get_config_int("WALLS", "three_up_x", -1);
	temp2 = get_config_int("WALLS", "three_up_y", -1);
	temp3 = get_config_int("WALLS", "three_down_x", -1);
	temp4 = get_config_int("WALLS", "three_down_y", -1);
	if(temp1 == -1 || temp2 == -1 || temp3 == -1 || temp4 == -1) assert(0);
	Wall *three = 0;
	three = new Wall(temp1, temp2, temp3, temp4);
	assert(three);
	cc->AddUnmovable(dynamic_cast<Sprite *>(three));
	sp->Insert(WALL_3, dynamic_cast<Sprite *>(three));

	//six oclock wall
	temp1 = get_config_int("WALLS", "six_up_x", -1);
	temp2 = get_config_int("WALLS", "six_up_y", -1);
	temp3 = get_config_int("WALLS", "six_down_x", -1);
	temp4 = get_config_int("WALLS", "six_down_y", -1);
	if(temp1 == -1 || temp2 == -1 || temp3 == -1 || temp4 == -1) assert(0);
	Wall *six = 0;
	six = new Wall(temp1, temp2, temp3, temp4);
	assert(six);
	cc->AddUnmovable(dynamic_cast<Sprite *>(six));
	sp->Insert(WALL_6, dynamic_cast<Sprite *>(six));

	//Nine oclock wall
	temp1 = get_config_int("WALLS", "nine_up_x", -1);
	temp2 = get_config_int("WALLS", "nine_up_y", -1);
	temp3 = get_config_int("WALLS", "nine_down_x", -1);
	temp4 = get_config_int("WALLS", "nine_down_y", -1);
	if(temp1 == -1 || temp2 == -1 || temp3 == -1 || temp4 == -1) assert(0);
	Wall *nine = 0;
	nine = new Wall(temp1, temp2, temp3, temp4);
	assert(nine);
	cc->AddUnmovable(dynamic_cast<Sprite *>(nine));
	sp->Insert(WALL_9, dynamic_cast<Sprite *>(nine));

	return;
}
