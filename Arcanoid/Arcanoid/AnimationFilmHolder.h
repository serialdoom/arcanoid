/*
 * author: koutsop
 */
#ifndef ANIMATIONFILMHOLDER_H
#define ANIMATIONFILMHOLDER_H

#include <map>
#include <string>
#include <cassert>
#include <allegro.h>

#include "BitmapLoader.h"
#include "LoadFilmsInfo.h"
#include "AnimationFilm.h"

using std::string;

class AnimationFilmHolder {
private:
	typedef std::map<string, AnimationFilm*> FilmMap;
    FilmMap		filmMap;

	void LoadData(string id, BITMAP* bitmap);
	//void LoadBBoxes(string id, int i, const BitmapLoader &bitmpas);
	
public:
    const AnimationFilm *GetFilm(const string id) const;

	//const char* path to path pou briskete ta configs files
	//dhl to ./configs_files/bboxes/
    AnimationFilmHolder(const string &path, const LoadFilmsInfo &filmsInfo, const BitmapLoader &bitmaps);
    ~AnimationFilmHolder();
};

#endif