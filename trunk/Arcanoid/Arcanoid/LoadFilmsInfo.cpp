/*
 * author: koutsop
 */

#include <allegro.h>
#include "LoadFilmsInfo.h"

#define MAX_TMP_SIZE 100
static char tmpString[MAX_TMP_SIZE]; //tmp table gia to append string me ari8mou

//////////////////////////////////////////////////////////////////////////////

static char * Append( string str, int i){
	sprintf_s(tmpString, MAX_TMP_SIZE, "%s%d", str.c_str(), i);
	return tmpString;
}

//////////////////////////////////////////////////////////////////////////////

LoadFilmsInfo::LoadFilmsInfo(const char* path){
	assert(path);
	set_config_file(path);

}

//////////////////////////////////////////////////////////////////////////////

LoadFilmsInfo::~LoadFilmsInfo(void){
	FilmsMap::iterator start	= filmsMap.begin();
	FilmsMap::iterator end		= filmsMap.end();

	while( start != end ){			//Clear to eswteriko map apo to Arxiko mas map
		(*start).second.clear();
		start++;
	}
	filmsMap.clear();
}//end of cunstructor

/*
#[FILMS]
#number_of_films = interger
#id_i		= string
#bitmap_i	= string path
#bboxes_i	= string path
*/
void LoadFilmsInfo::LoadInfo(void){
	
}