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
	
	/* @target: Na diabazei ola ta bboxes pou uparxoun se ena cfg file
	 *		  :gia ena sugkekrimeno film. Kai telos na kanei thn eisagwnei tou neou
	 *		  :animationFilm mesa sto FilmMap
	 */
	void LoadBBoxes(string id, BITMAP* bitmap);

public:
	/* @target: diagafei olla ta periexomena tou AnimationFilmHolder
	 */
	void Clear(void);

	/* @target: Ka8ara gia debug skopous
	 * @return: To pli8os ton AnimationFilms pou exei.
	 */
	size_t GetSize(void) const { return filmMap.size(); }


	/* @param : To id gia ena sugkekrimeno AnimationFilm
	 * @return: To animationFilm me to sugkekrimeno Id. An
	 *		  :den uparxei AfinmationFilm me tetio id xtipa assert
	 */
    const AnimationFilm *GetFilm(const string id) const;

    /* @param : const char* path to path pou briskete ta configs files
	 *		  :dhl to ./configs_files/bboxes/
	 * @param : LoadFilmsInfo, 
	 * @param : BitmapLoader
	 */
	AnimationFilmHolder(const LoadFilmsInfo &filmsInfo, 
						const BitmapLoader &bitmaps);
    ~AnimationFilmHolder();

	//gia debug skopous
	void PrintAnimationFilmHolder(void);
};

#endif