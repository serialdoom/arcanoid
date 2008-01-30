/*
 * author: koutsop
 */
//TODO tropo na diabazoume ola ta terrain pou uparxoun
#include <string>
#include <cassert>

#include "Game.h"

#define BUFF_SZ			20321

#define CONFIG_FILE		"./configs_files/game.cfg"
#define BUFFER_IMAGE	"./images/bufferEditorsScreen.bmp"
#define BAGROUND_IMAGE	"./images/editorsScreen.bmp"

#define BALL			"ball"
#define BOARD			"board"
#define WALL_12			"upper_wall"
#define WALL_3			"right_wall"
#define WALL_6			"down_wall"
#define WALL_9			"left wall"


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


//Destructor
Game::~Game(){
	delete bitmaps;
	delete spriteH;
	delete terrain;
	delete filmsInfo;
	delete collisionC;
	delete animationFH;
	delete inputManager;
}
/////////////////////////////////////////////////////////////////////



//constructor
Game::Game(void){
	currTime	= 0;
	currLevel	= 0;
	
	InitiallizingAllegro();

	spriteH			= new SpriteHolder();
	animationH		= new AnimationHolder();
	collisionC		= new CollisionChecker();
	inputManager	= new InputManager();
	assert(spriteH || collisionC || inputManager);

	StateHolder::Init();
	InitiallizingFilmsInfo();
	InitiallizingBitmapLoader();
	InitiallizingAnimationFilmHolder();

	terrain = new Terrain(CONFIG_FILE, animationFH, collisionC, animationH, spriteH);
	assert(terrain);
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




Board * Game::CreatingBoard(int playerNo){
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
	collisionC->AddMovable(dynamic_cast<Sprite *>(theBoard));
	spriteH->Insert(BOARD, dynamic_cast<Sprite *>(theBoard));

	//Add to animation Holder
	MovingAnimation * mov = new MovingAnimation(x, y, 1, true, countAnimationID);
	countAnimationID++;
	animationH->Insert(BOARD, mov );
	
	//Add to animator Holder
	board = new MovingAnimator();
	board->Start(spriteH->GetSprite(BOARD), mov, 0);
	AnimatorHolder::Register(board);

	return theBoard;
}
/////////////////////////////////////////////////////////////////////



Ball * Game::CreatingBall(void){
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
	collisionC->AddMovable(dynamic_cast<Sprite *>(theBall));
	spriteH->Insert(BALL, dynamic_cast<Sprite *>(theBall));

	//Add to animation Holder
	MovingAnimation * mov = new MovingAnimation(x, y, 1, true, countAnimationID);
	countAnimationID++;
	animationH->Insert(BALL, mov );
	
	//Add to animator Holder
	ball = new MovingAnimator();
	ball->Start(spriteH->GetSprite(BALL), mov, 0);
	AnimatorHolder::Register(ball);

	return theBall;
}
/////////////////////////////////////////////////////////////////////


void Game::DisplayALL(BITMAP *baground, BITMAP *buffer){
	Sprite *board = board = spriteH->GetSprite(BOARD); 
	Sprite *ball = spriteH->GetSprite(BALL);
	
	assert(baground || buffer || board || ball);
	
	blit(baground, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	
	if( board->IsVisible() )
		board->Display(buffer);

	if( ball->IsVisible() )
		ball->Display(buffer);

	terrain->DisplayTerrain(buffer, spriteH);
	blit(buffer , screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	return;
}
/////////////////////////////////////////////////////////////////////

void Game::SetMouseCoordinates(MovingAnimation * mov){
	//elegxoume an pame na bgoume apo ta oria tou terrain
	int x		= terrain->coordinates.GetX();
	int boardW	= dynamic_cast<Board*>(spriteH->GetSprite(BOARD))->GetWidth();

	if( inputManager->GetOldMouseX() < x )
		inputManager->SetOldMouseX(x);
	else if ( inputManager->GetOldMouseX() > (x + terrain->width) - boardW )
		inputManager->SetOldMouseX((x + terrain->width) - boardW);
				
	mov->SetDx( inputManager->GetOldMouseX() );		//alazoume to dx tou board
	return;
}

void Game::CheckBoardInput( bool input ){
	static bool isRunning	= false;
	static bool isSuspended	= true;		//otan kanoume register mpenei kai sto suspend
	MovingAnimation * mov = dynamic_cast<MovingAnimation*>(animationH->GetAnimation(BOARD));
	
	if(input){
		dynamic_cast<Board*>(spriteH->GetSprite(BOARD))->SetKey(StateHolder::stateKey);
		if( StateHolder::stateKey.Key_Mouse_Left	|| 
			StateHolder::stateKey.Key_Mouse_Right	||
			StateHolder::stateKey.Key_Left			||
			StateHolder::stateKey.Key_Right) 
		{
			SetMouseCoordinates(mov);
			if( !isRunning ){		//Gia prwth fora mpenei sthn lista me ta running
				AnimatorHolder::MarkAsRunning(board);
				isRunning	= true;
				isSuspended	= false;
			}
		}//end second if
	}//end first if
	else{
		if( !isSuspended ){	//Gia prwth fora sthn lista me ta suspended
			AnimatorHolder::MarkAsSuspended(board);
			isRunning	= false;
			isSuspended	= true;
		}
	}//end else
	return;
}
/////////////////////////////////////////////////////////////////////



void Game::GameLoop(BITMAP *baground, BITMAP *buffer){
	bool input = false;

	while( !key[KEY_ESC] && (currLevel < terrain->GetLevelsNo()) ) {
		SetGameTime();

		spriteH->GetEnd();
		input = inputManager->CheckInput();
		CheckBoardInput(input);

		collisionC->CollisionCheck();
		AnimatorHolder::Progress(GetGameTime());
		DisplayALL(baground, buffer);
	}
	return;
}


void Game::PlayGame(void){
	//bitmaps
	BITMAP * buffer		= bitmaps->Load(BUFFER_IMAGE);
	BITMAP * baground	= bitmaps->Load(BAGROUND_IMAGE);
	//sprites
	Ball* theBall		= CreatingBall();
	Board* theBoard		= CreatingBoard(1);

	AnimatorHolder::MarkAsRunning(ball);
	assert(buffer || baground || theBall || theBoard);
	
	countAnimationID = terrain->LoadingTerrain(countAnimationID, currLevel);
	GameLoop(baground, buffer);

	return;
}