/* TerrainBuilder.cpp */

#include "TerrainBuilder.h"

#define BUFF_SZ 9999

#define PREFIX_FRAME_NUMBER		"farme Number = "
#define PREFIX_UP_POINT_X		"up.x="
#define PREFIX_UP_POINT_Y		"up.y="
#define PREFIX_DOWN_POINT_X		"down.x="
#define PREFIX_DOWN_POINT_Y		"down.y="
#define PREFIX_WIDTH			"Width = "
#define PREFIX_HEIGHT			"Height = "
#define PREFIX_CAN_BREAK		"canBreak = "
#define PREFIX_TIMES_TO_BREAK	"time to break = "
#define PREFIX_SCORE			"score = "
#define BRICK_NAME_PREFIX		"Brick_"

TerrainBuilder::TerrainBuilder(CollisionChecker *_cc, 
							   SpriteHolder *_sp, 
							   AnimationFilmHolder *_afm, 
							   AnimationHolder * _ah){
	cc	= _cc;
	sp	= _sp;
	afm = _afm;
	ah	= _ah;
	return;
}

animid_t TerrainBuilder::Load(const char *filename, 
							  const char *brick_id, 
							  animid_t countAnimationID, 
							  AnimatorMap &bricksAnimator)
{
	std::ifstream input; // input stream
	char buffy[BUFF_SZ];
	const char *test;
	int counter = 0, x, y;
	// variable to hold brick data.
	Brick *newBrick = 0;

	input.open(filename);
	if(!input.good()) {
		KeyLogger::Write("FAIL.\n");
		exit(1);
	}
	KeyLogger::Write("DONE.\n");
	while(input.good()){
		memset(buffy, 0, BUFF_SZ);
		input.getline(buffy, BUFF_SZ, '\n');
		if(!strlen(buffy)) continue; // In case there is a line in the file with just an enter...

		++counter;
		std::string *brick_id_str = new std::string(brick_id);
		
		AnimationFilm* tmp = const_cast<AnimationFilm*>(afm->GetFilm( (*brick_id_str) ));
		assert(tmp);
		newBrick = new Brick(	(x = getNumber(buffy, PREFIX_UP_POINT_X)), (y = getNumber(buffy, PREFIX_UP_POINT_Y)), //point
								tmp, //AnimationFilm
								getNumber(buffy, PREFIX_WIDTH), // w
								getNumber(buffy, PREFIX_HEIGHT), //h
								getNumber(buffy, PREFIX_SCORE), //score
								getNumber(buffy, PREFIX_FRAME_NUMBER), //frameNo
								false, // isActive
								(getNumber(buffy, PREFIX_CAN_BREAK))?(true):(false), //CanBreak
								getNumber(buffy, PREFIX_TIMES_TO_BREAK) //Times to break
							);
				
		delete(brick_id_str);

		cc->AddUnmovable(dynamic_cast<Sprite *>(newBrick));
		sp->Insert(test = AppendIntegerToString(BRICK_NAME_PREFIX, counter), dynamic_cast<Sprite *>(newBrick));
		
		//add to animationHolder
		MovingAnimation * mov = new MovingAnimation(x, y, 1, true, countAnimationID);
		countAnimationID++;
		ah->Insert(test, mov );

		//add to animator Holder
		MovingAnimator * brick = new MovingAnimator();
		brick->Start(sp->GetSprite(test), mov, 2000);
		bricksAnimator.insert( make_pair(test, brick) );
		AnimatorHolder::Register(brick);
		AnimatorHolder::MarkAsRunning(brick);
	}
	return countAnimationID;
}

int TerrainBuilder::getNumber(char *buffer, const char *pattern){
	char *tmp = 0;
	char temp[BUFF_SZ];
	int counter = 0;

	memset(temp, 0, BUFF_SZ);
	tmp = strstr(buffer, pattern);
	tmp += strlen(pattern);
	counter = 0;
	//DEBUG:: KeyLogger::Write("The string im trying to print is \"%s\" and  pattern \"%s\".\n", buffer, pattern);
	while(tmp && isdigit(*tmp)) temp[counter++] = *(tmp++);
	return atoi(temp);
}


const char * TerrainBuilder::AppendIntegerToString( string str, int i){
	char tmpString[BUFF_SZ];
	assert( (str.size()+ i) < BUFF_SZ);
	sprintf_s(tmpString, BUFF_SZ, "%s%d", str.c_str(), i);
	return _strdup(tmpString);
}