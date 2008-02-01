/*
 * author: koutsop
 */
//TODO tropo na diabazoume ola ta terrain pou uparxoun
#include <string>
#include <cassert>

#include "Game.h"

#define BUFF_SZ			20321
#define PARSE_ONE_SEC	1

#define CONFIG_FILE		"./configs_files/game.cfg"
#define BUFFER_IMAGE	"./images/bufferEditorsScreen.bmp"
#define BAGROUND_IMAGE	"./images/editorsScreen.bmp"

#define BALL			"ball"
#define WALL_12			"upper_wall"
#define WALL_3			"right_wall"
#define WALL_6			"down_wall"
#define WALL_9			"left wall"

#define PAYER_ONE 1
#define PAYER_TWO 2

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

//	CreateAll();
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





/* precodition: Prepei na exei dimiourgi8ei o animation Film Holder
			  : o collision Checker o sprite Holder kai telos o animation Holder
 */
Board * Game::CreatingBoard(int playerNo){
	int x, y;
	string filmID;
	set_config_file(CONFIG_FILE);
	
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


/* precodition: Prepei na exei dimiourgi8ei o animation Film Holder
			  : o collision Checker o sprite Holder kai telos o animation Holder
 */
Ball * Game::CreatingBall(void){
	int x, y;
	string filmID;
	set_config_file(CONFIG_FILE);
	
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


void Game::DisplayALL(){
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
			//SetMouseCoordinates(mov);
			mov->SetDx( inputManager->GetOldMouseX() );
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

/*
void Game::BuildAll(){
	//CreateAll();
	theBall	 = CreatingBall();
	theBoard = CreatingBoard(currLevel);
	countAnimationID = terrain->LoadingTerrain(countAnimationID, currLevel);
	AnimatorHolder::MarkAsRunning(ball);

	assert(theBall || theBoard || (countAnimationID > 0));
	return;
}
*/

void Game::DeleteAll(){
	delete bitmaps;
	delete spriteH;
	delete terrain;
	delete filmsInfo;
	delete collisionC;
	delete animationFH;
	delete inputManager;
}

void Game::CheckF1(bool input){
	if(currLevel >= terrain->GetLevelsNo()-1)	//simenh oti eimatse sto teleuteo level kai den kaeni na proxorisoume
			return;
	if( StateHolder::stateKey.Key_F1 ){
		DeleteAll();
		currLevel++;
		countAnimationID = 0;
		CreateAll();
	}
	return;
}
/////////////////////////////////////////////////////////////////////



static void FPSCalculation(void){
	static unsigned long sec = 0;
	static unsigned long fps = 0;
	
	if( !sec )  { sec = time((time_t *)0); }		
	else{
		//std::cout<<time((time_t *)0)<<std::endl;
		if( (time((time_t *)0)- sec) >= PARSE_ONE_SEC ) {//upologizoume an perase ena sec
			std::cout<<"fps:"<<fps<<std::endl;
			fps = 0;
			sec = 0;
		}
		else	{fps++;} 
	}//else
	return;
}
/////////////////////////////////////////////////////////////////////



void Game::SystemLoopDispatching( bool input ){
	
	CheckBoardInput(input);
	return CheckF1(input);
}
/////////////////////////////////////////////////////////////////////



void Game::GameLoop(){
	bool input = false;

	//spriteH->PrintSpriteHolder();

	while( !key[KEY_ESC] && (currLevel < terrain->GetLevelsNo()) ) {
		SetGameTime();

		input = inputManager->CheckInput();


		collisionC->CollisionCheck();
		AnimatorHolder::Progress(GetGameTime());

		DisplayALL();
		
		collisionC->CleanUp();
		terrain->BricksCleanUp(spriteH);
	
		FPSCalculation();
		SystemLoopDispatching(input);
		//for(int i = 0;i < 1000000;++i);
	}
	return;
}

void Game::CreateAll(void){
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

	buffer		= bitmaps->Load(BUFFER_IMAGE);
	baground	= bitmaps->Load(BAGROUND_IMAGE);

	theBall	 = CreatingBall();
	theBoard = CreatingBoard(PAYER_ONE);
	countAnimationID = terrain->LoadingTerrain(countAnimationID, currLevel);
	AnimatorHolder::MarkAsRunning(ball);
	
	assert(buffer || baground || theBall || theBoard);

}

void Game::PlayGame(void){
	//bitmaps
	KeyLogger::Init("test.txt");
	KeyLogger::Enable();

	CreateAll();

	GameLoop();
	KeyLogger::Terminate();
	return;
}