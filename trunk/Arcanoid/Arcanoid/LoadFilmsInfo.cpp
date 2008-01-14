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
//constructor
LoadFilmsInfo::LoadFilmsInfo(const char* path){
	filmsNo = 0;
	assert(path);
	set_config_file(path);
	LoadInfo();
}

//////////////////////////////////////////////////////////////////////////////
//destructor
LoadFilmsInfo::~LoadFilmsInfo(void){
	filmsInfo.clear();
}//end of cunstructor

//////////////////////////////////////////////////////////////////////////////

/*
#[FILMS]
#number_of_films = interger
#id_i		= string
#bitmap_i	= string path
#bboxes_i	= string path
*/
void LoadFilmsInfo::LoadInfo(void){
	filmIdentifire =  get_config_string("FILMS", "film_identifire", "");
	filmsNo = get_config_int("FILMS", "number_of_films", -1);	//O ari8mos ton film pou uparxoun
	
	if( !filmIdentifire.compare("") ) { assert(0); } 
	assert( filmsNo != -1 );

	for(int i = 0; i < filmsNo; i++){			//Diabazw thn info gia to ka8e film
		string id		= get_config_string("FILMS", Append("id_", i), "");
		string bboxe	= get_config_string("FILMS", Append("bboxes_", i), "");	
		string bitmap	= get_config_string("FILMS", Append("bitmap_", i), "");	

		if( !id.compare("")		||
			!bboxe.compare("")	||
			!bitmap.compare("")
		   ) { assert(0); } 
		filmsInfo.insert( make_pair(id, std::pair<string, string>(bboxe, bitmap)) );
	}//end for
	return;
}