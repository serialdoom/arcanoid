/*
 * author: koutsop
 */
#ifndef ANIMATIONFILMHOLDER_H
#define ANIMATIONFILMHOLDER_H

#include <map>
#include <string>
#include <cassert>

#include "LoadFilmsInfo.h"
#include "AnimationFilm.h"

using std::string;

class AnimationFilmHolder {
private:
	typedef std::map<string, AnimationFilm*> FilmMap;
    FilmMap		filmMap;

	void LoadData(void);
	void LoadFilm(string path, int i);
	
public:
    const AnimationFilm *GetFilm(const string id) const;

	//const char* path to path pou briskete ta configs files
    AnimationFilmHolder(const char* path); // Decoder constructor.
    ~AnimationFilmHolder();
};

#endif