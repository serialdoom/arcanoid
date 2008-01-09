/*
 * author: koutsop
 */

#include <iostream>
#include <cstring>
#include <sstream>
#include "LoadData.h"

#define MAX_TMP_SIZE 100
#define CFG_FILE_NAME "./gameEditorConfiguration.cfg"

using std::cout;

static char tmpString[MAX_TMP_SIZE]; //tmp table gia to append string me ari8mou


LoadData::LoadData(void){
	set_config_file(CFG_FILE_NAME);
}
LoadData::~LoadData(void){}


void LoadData::LoadFileNameToWrite(void){
	fileNameToWrite = get_config_string("FILE_NAME_CFG", "file_name_file", "");
	if( !fileNameToWrite.compare("") ) { assert(0); } 
	return;
}

void LoadData::LoadTerrainInfo(Terrain& terrain){
	terrain.coordinates.SetX( get_config_int("TERRAIN", "terrain_start_x", 0) );
	terrain.coordinates.SetY( get_config_int("TERRAIN", "terrain_start_y", 0) );
	
	terrain.fileNameBackgroundImage = get_config_string("TERRAIN", "terrain_background_file", "");
	terrain.width	= get_config_int("TERRAIN", "terrain_width", 0);
	terrain.height	= get_config_int("TERRAIN", "terrain_height", 0);
	terrain.colum	= get_config_int("TERRAIN", "terrain_colum", 0);
	terrain.row		= get_config_int("TERRAIN", "terrain_row", 0);
	
	if( !terrain.fileNameBackgroundImage.compare("") ) { assert(0); } 
	assert(terrain.coordinates.GetX() >= 0);
	assert(terrain.coordinates.GetY() >= 0);
	assert(terrain.width);
	assert(terrain.height);
	assert(terrain.colum);
	assert(terrain.row);
	return;
}


void LoadData::LoadOkCancel(OkCancel& oc){
	oc.imageFileName= get_config_string("OK_CANCE", "ok_cancel_file", "");

	oc.imageWidth	= get_config_int("OK_CANCE", "ok_cancel_image_width", 0);
	oc.imageHeight	= get_config_int("OK_CANCE", "ok_cancel_image_height", 0);
	oc.imageCort.SetX(get_config_int("OK_CANCE", "ok_cancel_cort_x", 0));
	oc.imageCort.SetY(get_config_int("OK_CANCE", "ok_cancel_cort_y", 0));
	
	oc.okUpCort.SetX(get_config_int("OK_CANCE", "ok_cancel_ok_up_x", 0));
	oc.okUpCort.SetY(get_config_int("OK_CANCE", "ok_cancel_ok_up_y", 0));
	oc.okDownCort.SetX(get_config_int("OK_CANCE", "ok_cancel_ok_down_x", 0));
	oc.okDownCort.SetY(get_config_int("OK_CANCE", "ok_cancel_ok_down_y", 0));

	oc.cancelUpCort.SetX(get_config_int("OK_CANCE", "ok_cancel_cancel_up_x", 0));
	oc.cancelUpCort.SetY(get_config_int("OK_CANCE", "ok_cancel_cancel_up_y", 0));
	oc.cancelDownCort.SetX(get_config_int("OK_CANCE", "ok_cancel_cancel_down_x", 0));
	oc.cancelDownCort.SetY(get_config_int("OK_CANCE", "ok_cancel_cancel_down_y", 0));
	
	if( !oc.imageFileName.compare("") ) { assert(0); }
	assert(oc.imageHeight);
	assert(oc.imageWidth);
	return;
}

//exoume kai ta friends class edw malaka
void LoadData::LoadBricksFilmInfo(BricksFilm& film){

	film.fileNameBricksFilm	= get_config_string("BRICKS_FILM", "bricks_film_file", "");
	film.numOfBricks		= get_config_int("BRICKS_FILM", "bricks_film_number_of_bricks", 0);
	film.width				= get_config_int("BRICKS_FILM", "bricks_film_w", 0);
	film.height				= get_config_int("BRICKS_FILM", "bricks_film_h", 0);

	if( !film.fileNameBricksFilm.compare("") ) { assert(0); } 
	assert(film.numOfBricks);
	assert(film.width);
	assert(film.height);
	return;
}

//prepei prwtoun kalesoume auth na exoume parei ton ari8mo apo ta bricks pou uparxoun mesa se 
// ena bricks film
void LoadData::LoadBricksFilm(BricksFilm& film){
	Point up, down;
	bool canBreak = false;
	int score = 0, frameNo = 0, timesToBreak = 0;
	assert(film.numOfBricks);
	
	for(int i = 0; i < film.numOfBricks; i++ ){
		up.SetX(get_config_int("BRICK", AppendIntegerToString("brick_up_x_", i), 0));
		up.SetY(get_config_int("BRICK", AppendIntegerToString("brick_up_y_", i), 0));
		down.SetX(get_config_int("BRICK", AppendIntegerToString("brick_down_x_",i), 0));
		down.SetY(get_config_int("BRICK", AppendIntegerToString("brick_down_y_",i), 0));
		
		score		 = get_config_int("BRICK", AppendIntegerToString("brick_score_",i), 0);
		frameNo		 = get_config_int("BRICK", AppendIntegerToString("brick_frame_num_",i), 0);
		timesToBreak = get_config_int("BRICK", AppendIntegerToString("brick_times_to_break_",i), 0);
		
		if(get_config_int("BRICK", AppendIntegerToString("brick_can_break_",i), 0))
			canBreak = true;
		else
			canBreak = false;	
	
		film.bricks.push_back( new Brick(	frameNo, 
											up, 
											down, 
											film.width, 
											film.height,
											canBreak, 
											timesToBreak,
											score,
											true)  
						 );
	}//end of for
	
	return;
}
const char * LoadData::AppendIntegerToString( string str, int i){
	assert( (str.size()+ i) < MAX_TMP_SIZE);
	sprintf_s(tmpString, MAX_TMP_SIZE, "%s%d", str.c_str(), i);
	return tmpString;
}

/*
void LoadData::LoadInit(brickContainer& bricks){
	LoadFileNameToWrite();
	LoadTerrainInfo();
	LoadBricksFilmInfo();
	LoadOkCancel();
	LoadBricksFilm(bricks);
}
*/