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
#define BUFFER_IMAGE	"./images/BufferGameScreen.bmp"
#define BAGROUND_IMAGE	"./images/GameScreen.bmp"

#define BALL			"ball"
#define PAUSE			"pause"
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


//constructor
Game::Game(void){
	currLevel	= 0;
	for(int i=SCORE_MAX_DIGIT-1; i>=0;--i)
		scoreDigit[i] = -1;
	InitiallizingAllegro();
}

//Destructor
Game::~Game(){
	delete bitmaps;
	delete spriteH;
	delete terrain;
	delete filmsInfo;
	delete collisionC;
	delete animationFH;
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
	movBoard = new MovingAnimation(x, y, 1, true, countAnimationID);
	countAnimationID++;
	animationH->Insert(BOARD, movBoard );
	
	//Add to animator Holder
	board = new MovingAnimator();
	AnimatorHolder::Register(board);

	return theBoard;
}
/////////////////////////////////////////////////////////////////////

void Game::ResetBoard(void){
	spriteH->GetSprite(BOARD)->SetPosition(
		get_config_int("BOARD", "start_x", -1), get_config_int("BOARD", "start_y", -1));
	return;
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
							  filmID.c_str(),
							  spriteH);
	assert(theBall);
	collisionC->AddMovable(dynamic_cast<Sprite *>(theBall));
	spriteH->Insert(BALL, dynamic_cast<Sprite *>(theBall));

	//Add to animation Holder
	movBall = new MovingAnimation(x, y, 20, true, countAnimationID);
	countAnimationID++;
	animationH->Insert(BALL, movBall );
	
	//Add to animator Holder
	ball = new MovingAnimator();
	AnimatorHolder::Register(ball);

	return theBall;
}
/////////////////////////////////////////////////////////////////////

//precodition na exei dimiourgi8ei poio prhn to terrain
NainSpin * Game::CreateNain(void){
		int x = theBoard->GetPosition().GetX() + (theBoard->GetWidth() / 2);
		int y = theBall->GetPosition().GetY();
	nainID	= get_config_string("FILMS", "nainSpin", "");
	if( !nainID.compare("") ) { assert(0); }

	nain = new NainSpin(x,y,const_cast<AnimationFilm *>(animationFH->GetFilm(nainID))); 
	assert(nain);

	nain->SetVisibility(true);

	spriteH->Insert(nainID, dynamic_cast<Sprite *>(nain));
	nainAn = new FrameRangeAnimation(0, 39, x,y,20, true, countAnimationID);
	countAnimationID++;
	animationH->Insert(nainID, nainAn);
	
	//Add to animator Holder
	nainAr = new FrameRangeAnimator();
	nainAr->Start(nain, nainAn, 100);
	AnimatorHolder::Register(ball);
	AnimatorHolder::MarkAsRunning(dynamic_cast<Animator*>(nainAr));
	
	return nain;
}
/////////////////////////////////////////////////////////////////////

void Game::ResetBall(){
	spriteH->GetSprite(BALL)->SetPosition(
		get_config_int("BALL", "start_x", -1), get_config_int("BALL", "start_y", -1));
	AnimatorHolder::MarkAsSuspended(ball);
	ball->Stop();
	return;
}

/////////////////////////////////////////////////////////////////////

void Game::SetUpStats(){
	scoreDigitPos[0] = get_config_int("SCORE", "start_x", -1);
	scoreDigitPos[1] = get_config_int("SCORE", "start_y", -1);
	lifeDigitPos[0] =  get_config_int("LIFE", "start_x", -1);
	lifeDigitPos[1] = get_config_int("LIFE", "start_y", -1);
	levelDigitPos[0] = get_config_int("LEVEL", "start_x", -1);
	levelDigitPos[1] = get_config_int("LEVEL", "start_y", -1);

	if(scoreDigitPos[0] == -1 || scoreDigitPos[1] == -1 ||
		lifeDigitPos[0] == -1 || lifeDigitPos[1] == -1	||
		levelDigitPos[0] == -1 || levelDigitPos[0] == -1 ) assert(0);
}


/////////////////////////////////////////////////////////////////////

void Game::DisplayALL(){
	assert(baground || buffer || theBoard || theBall || nain);
	
	blit(baground, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	
	if( theBoard->IsVisible() )
		theBoard->Display(buffer);

	if( theBall->IsVisible() )
		theBall->Display(buffer);

	DisplayScore(buffer);
	DisplayLife(buffer);
	DisplayLevel(buffer);

	terrain->DisplayTerrain(buffer, spriteH);

	if( nain->IsVisible() )
		nain->Display(buffer);

	PowerUp::DesplayAll(buffer, spriteH);
	blit(buffer , screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	return;
}
/////////////////////////////////////////////////////////////////////

void Game::DisplayLevel(BITMAP *buffy){
	AnimationFilm *film = const_cast<AnimationFilm *>(animationFH->GetFilm("numbersFilm"));
	assert(film);
	film->DisplayFrame(buffy, new Point(levelDigitPos[0], levelDigitPos[1]), currLevel);
	return;
}

/////////////////////////////////////////////////////////////////////
void Game::DisplayLife(BITMAP *buffy){
	AnimationFilm *film = const_cast<AnimationFilm *>(animationFH->GetFilm("numbersFilm"));
	assert(film);
	film->DisplayFrame(buffy, new Point(lifeDigitPos[0], lifeDigitPos[1]), GameStats::GetLife());
	return;
}

/////////////////////////////////////////////////////////////////////
void Game::DisplayScore(BITMAP *buffy){
	AnimationFilm *film = const_cast<AnimationFilm *>(animationFH->GetFilm("numbersFilm"));
	assert(film);
	if(GameStats::ScoreChanged()){
		int i = GameStats::GetScore();
		for(int digit = 0;digit < SCORE_MAX_DIGIT; ++digit){
			scoreDigit[digit] = i%10;
			i  /= 10;
		}
	}
	int x=	scoreDigitPos[0];
	for(int i = SCORE_MAX_DIGIT-1;i>=0;--i){
		if(scoreDigit[i] != -1){
			film->DisplayFrame(buffy, new Point(x, scoreDigitPos[1]), scoreDigit[i]);
			x += (film->GetFrameBox(scoreDigit[i]))->GetWidth();
		}
	}
	return;
}


/////////////////////////////////////////////////////////////////////

void Game::DeleteAll(){
	delete bitmaps;
	delete spriteH;
	delete terrain;
	delete filmsInfo;
	delete collisionC;
	delete animationFH;
	InputManager::Clear();
	PowerUp::clear();
}
/////////////////////////////////////////////////////////////////////

void Game::NextLevel(void){
	if(currLevel >= terrain->GetLevelsNo()-1)	//eimatse sto teleuteo level
		currLevel = -1;							//Pame pali apo thn arxh
	DeleteAll();
	currLevel++;
	AnimatorHolder::Clear();
	countAnimationID = 0;
	CreateAll();
	return;
}


void Game::CheckF1(void){
	if( InputManager::inputKey.Key_F1 ){
		NextLevel();
	}
	return;
}
/////////////////////////////////////////////////////////////////////


//precodition: prepei thn prwth fora pou kaloume thn methon na einai
//to fps 0 
static void FPSCalculation(int &fps){
	timestamp_t theTime	= MyTime::GetSystemTime();
	static timestamp_t msec	= 0;
	
	if( !msec )  { msec = theTime;}		
	else{
		if( MyTime::GetSystemDiffTimeInSec(theTime, msec) >= 1 ) {//upologizoume an perase ena sec
			std::cout<<"fps:"<<fps<<std::endl;
			fps = 0;
			msec = 0;
		}
	}//else
	fps++;

	//rest( (fps > 60) ? difftime(theTime, msec) : 0);
	return;
}
/////////////////////////////////////////////////////////////////////



void Game::CheckBoardInput(){
	MovingAnimation * mov = dynamic_cast<MovingAnimation*>(animationH->GetAnimation(BOARD));
		
	if( !StateHolder::IsStoped()){
		if( board->HasFinished() ){//8eloume na ton baloume mia mono fora sthn lista me tous ranning
			board->Start(spriteH->GetSprite(BOARD), movBoard, 0);
			AnimatorHolder::MarkAsRunning(board);
		}
		//gia na 3erei me ti egine h khnhsh 
		dynamic_cast<Board*>(spriteH->GetSprite(BOARD))->SetKey(InputManager::inputKey);
		mov->SetDx( InputManager::GetOldMouseX() );
	}
	else{
		if( !board->HasFinished() ){	//8eloume na ton baloume mia mono fora sthn lista me tous suspended
			board->Stop();
			AnimatorHolder::MarkAsSuspended(board);
		}
	}
	return;
}
/////////////////////////////////////////////////////////////////////



void Game::SystemLoopDispatching(void){

	if(StateHolder::IsRunning()){
		if(InputManager::inputKey.Key_P){
			StateHolder::Pause();
			AnimatorHolder::Pause();
		}
		else{
			if( InputManager::inputKey.Key_Left || InputManager::inputKey.Key_Mouse_Left)
				StateHolder::GoLeft();	//board paei aristera
				
			else if(InputManager::inputKey.Key_Right || InputManager::inputKey.Key_Mouse_Right)
				StateHolder::GoRight();	//board paei de3ia
			else
				StateHolder::Stop();	//board einai ekinito

			if(InputManager::inputKey.Key_Enter && ball->HasFinished()){
				ball->Start(theBall, movBall, 0);
				AnimatorHolder::MarkAsRunning(ball);
			}	//moleis 3ekinise to paixnidi kai prepei na patiseis enter gia na arxisei
			else if( ball->HasFinished() ) {
				int x = theBoard->GetPosition().GetX() + (theBoard->GetWidth() / 2);
				int y = theBall->GetPosition().GetY();
				theBall->SetPosition(x, y);
			}
			CheckBoardInput();
			CheckF1();
		}
	}//first if
	else{ //paused
		if(InputManager::inputKey.Key_P){//Pati8ike to P
			StateHolder::Run();			//To paixnidi htan paused kai to arxizoume pali
			AnimatorHolder::Resum();
		}
	}
	return;
}
/////////////////////////////////////////////////////////////////////



void Game::GameLoop(void){
	int fps = 0;

	while( !key[KEY_ESC] && (currLevel < terrain->GetLevelsNo()) ) {
		if(!GameStats::GetLife()) return;
		if(GameStats::GetBricksToGo() <= 0) NextLevel();
		if(GameStats::IsLifeLost()) {
			GameStats::ResetLifeLost();
			ResetBall();
			ResetBoard();
		}
		MyTime::SetGameTime();

		InputManager::CheckInput();
			
		ai->AIBricks(spriteH);
		ai->AINain(nain, theBoard->GetPosition().GetX() + (theBoard->GetWidth() / 2), 0);
	

		collisionC->CollisionCheck();
		
		AnimatorHolder::Progress( MyTime::GetGameTime() );
		//spriteH->PrintSizeOfSpriteHolder();//Na diagrafei kata thn paradwsh
		collisionC->CleanUp();
		terrain->BricksCleanUp(spriteH);
		PowerUp::ApplyBonus(spriteH, animationH);
		//terrain->BricksCleanUp(spriteH, powerup);
		//powerup->ApplyBonus(spriteH, animationH);		
		
		DisplayALL();
		FPSCalculation(fps);
		
		SystemLoopDispatching();
		//spriteH->PrintSizeOfSpriteHolder();//Na diagrafei kata thn paradwsh
		//AnimatorHolder::printSize();//Na diagrafei kata thn paradwsh
		//for(int i=0; i < 5000000;++i);
	}
	return;
}

void Game::CreateAll(void){
	spriteH			= new SpriteHolder();
	animationH		= new AnimationHolder();
	collisionC		= new CollisionChecker();
	assert(spriteH || collisionC );

	InitiallizingFilmsInfo();
	InitiallizingBitmapLoader();

	animationFH = new AnimationFilmHolder((*filmsInfo), (*bitmaps));
	assert(animationFH);

	terrain = new Terrain(CONFIG_FILE, animationFH, collisionC, animationH, spriteH);
	assert(terrain);

	buffer		= bitmaps->Load(BUFFER_IMAGE);
	baground	= bitmaps->Load(BAGROUND_IMAGE);

	theBall	 = CreatingBall();
	theBoard = CreatingBoard(PAYER_ONE);
	nain	 = CreateNain();
	countAnimationID = terrain->LoadingTerrain(countAnimationID, currLevel);
	
	ai = new AI();
	PowerUp::Init(animationH, animationFH, spriteH, countAnimationID, theBall,theBoard );
	assert(buffer || baground || theBall || theBoard || ai);
	//powerup = new PowerUp(animationH, animationFH, spriteH, countAnimationID, theBall,theBoard );
	//assert(buffer || baground || theBall || theBoard || powerup || ai);

	GameStats::Init(0, 3);
	SetUpStats();


	return;
}

void Game::PlayGame(void){
	KeyLogger::Init("ArcanoidBigBrother.txt");
	KeyLogger::Enable();

	CreateAll();
	StateHolder::Init();
	InputManager::Init();

	
	GameLoop();
	KeyLogger::Terminate();
	return;
}

/* @precodition: Prepei panta na ektelite meta thn BricksCleanUp()
 */

//Geia test skopou htan auth na doume an kalounte oi dunamoi
//Ekei pou kaloume emeis tis dunamhs 8a prepei na kanoume oti leei to xartaki :)
/*
void Game::ExecuteBonus(){
	/*powerUpVector *allThePowers		= powerup->GetPowersToExecute();
	powerUpVector::iterator start	= allThePowers->begin();
	powerUpVector::iterator end		= allThePowers->end();

	while( start != end ){	
		switch( start->first){
			case MAX:			powerup->ApplyBonus( MAX, spriteH); break;//powerup->Max(theBoard); break;
			case MIN:			powerup->Max(theBoard); break;
			case STIC:			std::cout<<"STIC"<<std::endl; break;
			case LIFE_UP:		//powerup->LifeUp(); break;
			case CLONE_BALL:	std::cout<<"clone"<<std::endl;break;
			case SPEED_UP:		powerup->SpeedUp(theBall); break;
			case SPEED_DOWN:	powerup->SpeedDown(theBall); break;
			case DESTRUCTION:	std::cout<<"DESTRUCTION"<<std::endl; break;
			case EXPLOSION:		std::cout<<"EXPLOSION"<<std::endl; break;
			case BUCKLER:		std::cout<<"BUCKLER"<<std::endl; break;
			case BAD:			std::cout<<"BAD"<<std::endl; break;
			case MONEY:			//powerup->Money(); break;
			case BOMB:			std::cout<<"bomb"<<std::endl; break;
			case BANANA:		std::cout<<"banana"<<std::endl; break;
			case FIRE:			std::cout<<"fire"<<std::endl; break;
			case MONEY_X2:		std::cout<<"MONEY_X2"<<std::endl; break;
			case NONE:			std::cout<<"none"<<std::endl; break;
			default: assert(0);
		}//end of chitc
		start++;
	}
	powerup->ClearPowersToExecute();
	return;
}
*/