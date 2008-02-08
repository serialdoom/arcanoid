/*
 * author: koutsop
 */

#include "AnimationFilmHolder.h"
#include <iostream>
#define MAX_TMP_SIZE 100
static char tmpString[MAX_TMP_SIZE]; //tmp table gia to append string me ari8mou


static char * Append( string str, int i){
	sprintf_s(tmpString, MAX_TMP_SIZE, "%s%d", str.c_str(), i);
	return tmpString;
}
//////////////////////////////////////////////////////////////////////////////



AnimationFilmHolder::~AnimationFilmHolder(void){
	/*FilmMap::iterator start = filmMap.begin();
	FilmMap::iterator end	= filmMap.end();

	while( start != end ){
		destroy_bitmap( start->second->GetBitmap() );
		start++;
	}*/
	filmMap.clear();
}
/////////////////////////////////////////////////////////////////////////////



AnimationFilmHolder::AnimationFilmHolder(const LoadFilmsInfo &filmsInfo, 
										 const BitmapLoader &bitmaps)
{
	FilmsInfoMap films				= filmsInfo.GetFilmsInfo();
	FilmsInfoMap::iterator start	= films.begin();
	FilmsInfoMap::iterator end		= films.end();

	while( start != end ){	//diabazw olh thn pliroforia gia ta bbox twn films
		set_config_file( (*start).second.first.c_str() );
		BITMAP * tmp = const_cast<BitmapLoader &>(bitmaps).Load( (*start).second.second.c_str() );
		LoadBBoxes((*start).first, tmp);
		start++;
	}
}
//////////////////////////////////////////////////////////////////////////////



/*
H domh pou exei to configuretion file gia ta films
[BBOXES]
frames			= integer

film_x_i		= integer
film_y_i		= integer
film_width_i	= integer
film_height_i	= integer
*/
void AnimationFilmHolder::LoadBBoxes(string id,BITMAP * bitmap){
	assert(bitmap);
	vector<Oblong> boxes;
	int framesNo = get_config_int("BBOXES", "frames", -1);		//O ari8mos ton film pou uparxoun
	assert( framesNo != -1 );

	for( int i = 0; i < framesNo; i++ ){
		int x		= get_config_int("BBOXES", Append("film_x_", i), -1);
		int y		= get_config_int("BBOXES", Append("film_y_", i), -1);
		int width	= get_config_int("BBOXES", Append("film_width_", i), -1);
		int height	= get_config_int("BBOXES", Append("film_height_", i), -1);

		assert( (x != -1) && (y != -1) && (width != -1) && (height != -1) );
		boxes.push_back( *(new Oblong(x, y, 0, 0, width, height)) );
	}
	filmMap.insert( make_pair(id, new AnimationFilm(bitmap, boxes, id)) );
	return;
}
//////////////////////////////////////////////////////////////////////////////



const AnimationFilm *AnimationFilmHolder::GetFilm (const string id)const {
	
	//std::cout<<"Animation Film Holder: "<<id<<std::endl;
	FilmMap::const_iterator i = filmMap.find(id);
	assert(i != filmMap.end());
	return i->second;
}

void AnimationFilmHolder::Clear(void){
	filmMap.clear();
	return;
}


void AnimationFilmHolder::PrintAnimationFilmHolder(void){
	FilmMap::iterator start = filmMap.begin();
	FilmMap::iterator end	= filmMap.end();

	while(start != end){
		std::cout<<start->first<<endl;
		start++;
	}
	return;
}
