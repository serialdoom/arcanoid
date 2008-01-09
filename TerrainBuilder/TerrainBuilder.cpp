/* TerrainBuilder.cpp */

#include "TerrainBuilder.h"

#define BUFF_SZ 9999

#define PREFIX_FRAME_NUMBER "farme Number = "
#define PREFIX_UP_POINT_X "up.x="
#define PREFIX_UP_POINT_Y "up.y="
#define PREFIX_DOWN_POINT_X "down.x="
#define PREFIX_DOWN_POINT_Y "down.y="
#define PREFIX_WIDTH "Width = "
#define PREFIX_HEIGHT "Height = "
#define PREFIX_CAN_BREAK "canBreak = "
#define PREFIX_TIMES_TO_BREAK "time to break = "
#define PREFIX_SCORE "score = "

TerrainBuilder::TerrainBuilder(CollisionChecker *_cc){
	cc = _cc;
	return;
}

bool TerrainBuilder::Load(char *filename){
	std::ifstream input; // input stream
	char buffy[BUFF_SZ];
	int counter = 0;
	// variable to hold brick data.
	Brick *newBrick = 0;

	// DEBUG: std::cout << "Opening file\n";
	input.open(filename);
	if(!input.good()) return false;
	while(input.good()){
		memset(buffy, 0, BUFF_SZ);
		input.getline(buffy, BUFF_SZ, '\n');
		if(!strlen(buffy)) continue; // In case there is a line in the file with just an enter...
		// DEBUG: std::cout << "got line: " << buffy << std::endl;

		++counter;
		// Get the frame number
		newBrick = new Brick(	getNumber(buffy, PREFIX_FRAME_NUMBER),
								new Point(getNumber(buffy, PREFIX_UP_POINT_X), getNumber(buffy, PREFIX_UP_POINT_Y)),
								new Point(getNumber(buffy, PREFIX_DOWN_POINT_X), getNumber(buffy, PREFIX_DOWN_POINT_Y)),
								getNumber(buffy, PREFIX_WIDTH),
								getNumber(buffy, PREFIX_HEIGHT),
								(getNumber(buffy, PREFIX_CAN_BREAK))?(true):(false),
								getNumber(buffy, PREFIX_TIMES_TO_BREAK),
								getNumber(buffy, PREFIX_SCORE),
								true // _isActive
								);
		Register( dynamic_cast<Sprite *>(newBrick) ); // Collision checker registering
		//TODO: add the Sprite holder register.
		// DEBUG: std::cout << "I have a new brick with " << newBrick->frameNum << " times to break: " << newBrick->timesToBreak << " and score : " << newBrick->score << std::endl; 
	}
	std::cout << "You have :" << counter << " bricks." << std::endl;
	return true;
}

int TerrainBuilder::getNumber(char *buffer, const char *pattern){
	char *tmp = 0;
	char temp[BUFF_SZ];
	int counter = 0;

	tmp = strstr(buffer, pattern);
	tmp += strlen(pattern);
	counter = 0;
	while(tmp && isdigit(*tmp)) temp[counter++] = *(tmp++);
	return atoi(temp);
}

void TerrainBuilder::Register(Sprite *toreg){
	cc->AddUnmovable(toreg);
	
	// Debuging purpose :  cc->AddMovable(toreg);
	return;
}