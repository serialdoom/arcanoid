/*
 * author: koutsop
 */
//TODO tropo na diabazoume ola ta terrain pou uparxoun
#include <string>
#include <cassert>

#include "Game.h"

#define BUFF_SZ			20321
#define MAX_TMP_SIZE	100
#define CONFIG_FILE		"./configs_files/game.cfg"
#define BUFFER_IMAGE	"./images/bufferEditorsScreen.bmp"
#define BAGROUND_IMAGE	"./images/editorsScreen.bmp"

#define BALL			"ball"
#define BOARD			"board"
#define WALL_12			"upper_wall"
#define WALL_3			"right_wall"
#define WALL_6			"down_wall"
#define WALL_9			"left wall"


static char tmpString[MAX_TMP_SIZE]; //tmp table gia to append string me ari8mou
/////////////////////////////////////////////////////////////////////



//******************  Start of static private functions  ************


static char * Append( string str, int i){
	sprintf_s(tmpString, MAX_TMP_SIZE, "%s%d", str.c_str(), i);
	return tmpString;
}
/////////////////////////////////////////////////////////////////////



static void InitiallizingAllegro(void){
	//Innits
	allegro_init();
	install_timer();
	install_keyboard();		// Initialize keyboard routines
	install_mouse();

	set_color_depth(16);	// Set the color depth
	//set_gfx_mode(GFX_AUTODETECT, 640,480,0,0); 
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640,480,0,0); // Change our graphics mode to 640x480
	return;
}
/////////////////////////////////////////////////////////////////////



static Board * CreatingBoard( AnimationFilmHolder * animationFH, 
							  CollisionChecker *cc, 
							  SpriteHolder *sh,
							  char playerNo )
{
	int x, y;
	string filmID;

	x		= get_config_int("BOARD", "start_x", -1);
	y		= get_config_int("BOARD", "start_y", -1);
	filmID	= get_config_string("FILMS", "board", "");
	
	if( !filmID.compare("") ) { assert(0); }
	if( (x == -1) || (y == -1)) { assert(0); }

	Board *theBoard = new Board( x, y, 
							  const_cast<AnimationFilm *>(animationFH->GetFilm(filmID)), 
							  playerNo);
	assert(theBoard);

	cc->AddMovable(dynamic_cast<Sprite *>(theBoard));
	sh->Insert(BALL, dynamic_cast<Sprite *>(theBoard));
	
	return theBoard;
}
/////////////////////////////////////////////////////////////////////



static Ball * CreatingBall( AnimationFilmHolder * animationFH, 
						    AnimationHolder * animationH,
						    CollisionChecker *cc, 
						    SpriteHolder *sh )
{
	int x, y;
	string filmID;

	x		= get_config_int("BALL", "start_x", -1);
	y		= get_config_int("BALL", "start_y", -1);
	filmID	= get_config_string("FILMS", "ball", "");
	
	if( !filmID.compare("") ) { assert(0); }
	if( (x == -1) || (y == -1)) { assert(0); }
	
	Ball *theBall = new Ball( x, y, 
							  const_cast<AnimationFilm *>(animationFH->GetFilm(filmID)), 
							  filmID.c_str());
	assert(theBall);

	cc->AddMovable(dynamic_cast<Sprite *>(theBall));
	sh->Insert(BALL, dynamic_cast<Sprite *>(theBall));

	return theBall;
}
/////////////////////////////////////////////////////////////////////


//print to screen all den visible bricks
static void DisplayTerrain(BITMAP *bitmap, SpriteHolder* sh){
	int cnt = 0;
	SpriteMap::iterator	start	= sh->GetFirst();
	SpriteMap::iterator	end		= sh->GetEnd();

	while( start != end ){
		Sprite * tmp = sh->GetSprite( Append("Brick_", cnt ) );
		if( (tmp != (Sprite*)0) && tmp->IsVisible() )
			tmp->Display(bitmap);
		cnt++;
		start++;
	}
	return;
}
/////////////////////////////////////////////////////////////////////


//******************  End of static private functions  ***************


//Destructor
Game::~Game(){
	delete bitmaps;
	delete spriteH;
	delete terrainB;
	delete filmsInfo;
	delete collisionC;
	delete animationFH;
	delete inputManager;
}
/////////////////////////////////////////////////////////////////////



//constructor
Game::Game(void){
	levelsNo		= currLevel = currTime = 0;
	bitmaps			= (BitmapLoader *)0;
	spriteH			= (SpriteHolder *)0;
	terrainB		= (TerrainBuilder *)0;
	filmsInfo		= (LoadFilmsInfo *)0;
	animationH		= (AnimationHolder *)0;
	collisionC		= (CollisionChecker *)0;
	animationFH		= (AnimationFilmHolder *)0;
	Wall *twelve	= (Wall *)0;
	Wall *three		= (Wall *)0;
	Wall *six		= (Wall *)0;
	Wall *nine		= (Wall *)0;


	InitiallizingAllegro();
	
	spriteH		= new SpriteHolder();
	animationH	= new AnimationHolder();
	collisionC	= new CollisionChecker();
	assert(spriteH || collisionC);

	StateHolder::Init();
	InitiallizingFilmsInfo();
	InitiallizingBitmapLoader();
	InitiallizingAnimationFilmHolder();

	terrainB = new TerrainBuilder(collisionC, spriteH, animationFH);
	assert(terrainB);

	LoadLevelsInfo();
	LoadingTerrain(currLevel);

	twelve			= CreatingTwelveWall();
	three			= CreatingThreeWall();
	six				= CreatingSixWall();
	nine			= CreatingNineWall();
	inputManager	= new InputManager();
	assert(inputManager);
}
/////////////////////////////////////////////////////////////////////



void Game::InitiallizingFilmsInfo(){
	set_config_file(CONFIG_FILE);
	string filmsPath = get_config_string("GENERAL", "films", "");
	if( !filmsPath.compare("") ) { assert(0); }

	filmsInfo = new LoadFilmsInfo(filmsPath.c_str());
	assert(filmsInfo);
	return;
}
/////////////////////////////////////////////////////////////////////



void Game::InitiallizingBitmapLoader(void){
	assert(filmsInfo);
	bitmaps = new BitmapLoader();
	assert(bitmaps);
	bitmaps->LoadFilms(*(filmsInfo));
	return;
}
/////////////////////////////////////////////////////////////////////



void Game::InitiallizingAnimationFilmHolder(void) {
	set_config_file(CONFIG_FILE);
	string bboxesPath = get_config_string("GENERAL", "animationHolder", "");
	if( !bboxesPath.compare("") ) { assert(0); }

	animationFH = new AnimationFilmHolder(bboxesPath, (*filmsInfo), (*bitmaps));
	assert(animationFH);
	return;
}
/////////////////////////////////////////////////////////////////////



void Game::LoadLevelsInfo(void){
	set_config_file(CONFIG_FILE);
	levelsNo	= get_config_int("GENERAL", "levels_files_No", -1);
	levelPath	= get_config_string("GENERAL", "levels_path", "");
	
	assert( levelsNo >= 1 );
	if( !levelPath.compare("") ) { assert(0); }
	currLevel = 0;
	return;
}
/////////////////////////////////////////////////////////////////////



void Game::LoadingTerrain(int levelNo){
	set_config_file(CONFIG_FILE);
	string fileName		= get_config_string("GENERAL", Append("level_file_", levelNo), "");
	string bricksFilm	= get_config_string("FILMS", "brick", "");
	
	if( !fileName.compare("") )		{ assert(!"file name"); }
	if( !bricksFilm.compare("") )	{ assert(!"bricks film"); }
	string lala = levelPath+fileName;
	terrainB->Load( (levelPath+fileName).c_str(), bricksFilm.c_str());
	return;
}
/////////////////////////////////////////////////////////////////////



Wall * Game::CreatingTwelveWall(void){
	int upX, upY, downX, downY;
	
	set_config_file(CONFIG_FILE);
	upX		= get_config_int("WALLS", "twelve_up_x", -1);
	upY		= get_config_int("WALLS", "twelve_up_y", -1);
	downX	= get_config_int("WALLS", "twelve_down_x", -1);
	downY	= get_config_int("WALLS", "twelve_down_y", -1);
	if(upX == -1 || upY == -1 || downX == -1 || downY == -1) assert(0);
	
	twelve = new Wall(upX, upY, downX, downY);
	assert(twelve);

	collisionC->AddUnmovable(dynamic_cast<Sprite *>(twelve));
	spriteH->Insert(WALL_12, dynamic_cast<Sprite *>(twelve));
	return twelve;
}
/////////////////////////////////////////////////////////////////////



Wall * Game::CreatingThreeWall(void){
	int upX, upY, downX, downY;
	
	set_config_file(CONFIG_FILE);
	upX		= get_config_int("WALLS", "three_up_x", -1);
	upY		= get_config_int("WALLS", "three_up_y", -1);
	downX	= get_config_int("WALLS", "three_down_x", -1);
	downY	= get_config_int("WALLS", "three_down_y", -1);
	if(upX == -1 || upY == -1 || downX == -1 || downY == -1) assert(0);
		
	three = new Wall(upX, upY, downX, downY);
	assert(three);

	collisionC->AddUnmovable(dynamic_cast<Sprite *>(three));
	spriteH->Insert(WALL_3, dynamic_cast<Sprite *>(three));
	return three;
}
/////////////////////////////////////////////////////////////////////



Wall * Game::CreatingSixWall(void){
	int upX, upY, downX, downY;

	set_config_file(CONFIG_FILE);
	upX		= get_config_int("WALLS", "six_up_x", -1);
	upY		= get_config_int("WALLS", "six_up_y", -1);
	downX	= get_config_int("WALLS", "six_down_x", -1);
	downY	= get_config_int("WALLS", "six_down_y", -1);
	if(upX == -1 || upY == -1 || downX == -1 || downY == -1) assert(0);
	
	six = new Wall(upX, upY, downX, downY);
	assert(six);

	collisionC->AddUnmovable(dynamic_cast<Sprite *>(six));
	spriteH->Insert(WALL_6, dynamic_cast<Sprite *>(six));
	return six;
}
/////////////////////////////////////////////////////////////////////



Wall * Game::CreatingNineWall(void){
	int upX, upY, downX, downY;

	set_config_file(CONFIG_FILE);
	upX		= get_config_int("WALLS", "nine_up_x", -1);
	upY		= get_config_int("WALLS", "nine_up_y", -1);
	downX	= get_config_int("WALLS", "nine_down_x", -1);
	downY	= get_config_int("WALLS", "nine_down_y", -1);
	if(upX == -1 || upY == -1 || downX == -1 || downY == -1) assert(0);
	
	nine = new Wall(upX, upY, downX, downY);
	assert(nine);

	collisionC->AddUnmovable(dynamic_cast<Sprite *>(nine));
	spriteH->Insert(WALL_9, dynamic_cast<Sprite *>(nine));
	return nine;
}
/////////////////////////////////////////////////////////////////////


void Game::DisplayALL(BITMAP *baground, BITMAP *buffer){
		blit(baground, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		DisplayTerrain(buffer, spriteH);
		blit(buffer , screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		return;
}
/////////////////////////////////////////////////////////////////////



void Game::GameLoop(BITMAP *baground, BITMAP *buffer){
	bool input = false;
	while( !key[KEY_ESC] && (currLevel < levelsNo) ) {
		SetGameTime();

		if( inputManager->CheckInput() ){
			
		}
		DisplayALL(baground, buffer);
	}
	return;
}


void Game::PlayGame(void){
	//bitmaps
	BITMAP * buffer		= bitmaps->Load(BUFFER_IMAGE);
	BITMAP * baground	= bitmaps->Load(BAGROUND_IMAGE);
	//sprites
//	Ball* theBall		= CreatingBall(animationFH, collisionC, spriteH);
	Board* theBoard		= CreatingBoard(animationFH, collisionC, spriteH, 1);

//	assert(buffer || baground || theBall || theBoard);
	

	GameLoop(baground, buffer);

	//readkey();
	return;
}