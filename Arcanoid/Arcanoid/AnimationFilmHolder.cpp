/*
 * author: koutsop
 */
#include <allegro.h>
#include "AnimationFilmHolder.h"


#define MAX_TMP_SIZE 100
static char tmpString[MAX_TMP_SIZE]; //tmp table gia to append string me ari8mou


static char * Append( string str, int i){
	sprintf_s(tmpString, MAX_TMP_SIZE, "%s%d", str.c_str(), i);
	return tmpString;
}

//////////////////////////////////////////////////////////////////////////////

AnimationFilmHolder::~AnimationFilmHolder(void){ 
	filmMap.clear();
}

/////////////////////////////////////////////////////////////////////////////

AnimationFilmHolder::AnimationFilmHolder(const char* path){
	assert(path);
	set_config_file(path);
	LoadData();
}

//////////////////////////////////////////////////////////////////////////////

void AnimationFilmHolder::LoadData(void){
	int filmsNo = get_config_int("FILMS", "number_of_films", -1);		//O ari8mos ton film pou uparxoun
	assert( filmsNo != -1 );

	string filmsPath = get_config_string("FILMS", "films_path", "");	//Pou briskontai ta films
	if( !filmsPath.compare("") ) { assert(0); }

	for( int i = 0; i < filmsNo; i++ ){ LoadFilm(filmsPath, i); }
	return;
}

////////////////////////////////////////////////////////////////////////////
/*
H domh pou exei to configuretion file gia ta films
[FILMS]
number_of_films = integer
films_path		= string	#gia to blit ./images/film_name_i
film_name_i		= string
snapshots_num_i	= integer
film_x_i_j		= integer
film_y_i_j		= integer
film_width_i_j	= integer
film_height_i_j	= integer
*/
void AnimationFilmHolder::LoadFilm(string path, int i){
	vector<Oblong> boxes;
	BITMAP* bitmap	= NULL;
	int snapshotsNo = 0;

	string filmName = get_config_string("FILMS", Append("film_name_", i), "");
	snapshotsNo		= get_config_int("FILMS", Append("snapshots_num_", i), -1);
	
	if( !filmName.compare("") ) { assert(0); }
	assert(snapshotsNo != -1);

	for( int j = 0; j < snapshotsNo; j++ ){
		int x		= get_config_int("FILMS", Append(strcat(Append("film_x_", i), "_"), j), -1);
		int y		= get_config_int("FILMS", Append(strcat(Append("film_y_", i), "_"), j), -1);
		int width	= get_config_int("FILMS", Append(strcat(Append("film_width_", i), "_"), j), -1);
		int height	= get_config_int("FILMS", Append(strcat(Append("film_height_", i), "_"), j), -1);
		assert( (x != -1) && (y != -1) && (width != -1) && (height != -1) );
		boxes.push_back( *(new Oblong(x, y, 0, 0, width, height)) );
	}

	bitmap = load_bitmap( path.append(filmName).c_str(), NULL);
	filmMap.insert( make_pair(filmName, new AnimationFilm(bitmap, boxes, filmName)) );
	return;
}


//////////////////////////////////////////////////////////////////////////////

const AnimationFilm *AnimationFilmHolder::GetFilm (const std::string id) const {
	FilmMap::const_iterator i = filmMap.find(id);
	assert(i != filmMap.end());
	return i->second;
}

