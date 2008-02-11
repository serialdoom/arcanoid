/*
 *author: koutsop
 */

#ifndef BRICK_H
#define BRICK_H

#include <string>
#include <cassert>
#include <allegro.h>	//Eidea den exw giati xriazete ala stamata na peta la8oi h allgero

#include <iostream>

#include "Oblong.h"
#include "Point.h"
#include "Sprite.h"
#include "AnimationFilm.h"
#include "GameStats.h"

using namespace std;

class Brick : public Sprite{
private:
	int  score;
	char timesToBreak;
	bool canBreak, isActive;
	string id;
	string gift; // mas enhmerwnei an exei paowerup to Brick
	//To isActive 8a to xriastoume gia na 3eroume an ena brick tou pinaka exei
	//sxediastei apo ton xristi h' oxi.
bool up;

public:
	//constructor
	Brick(	int x, int y,
			AnimationFilm* film,
			const int w, const int h,
			const int _score,
			const char frameNo,
			const bool _isActive,
			const bool _canBreak, 
			const char _timesToBreak,
			const string _id); 

	//overload constructor 1
	Brick(	const Point  point,
			AnimationFilm* film,
			const int w, const int h,
			const int _score,
			const char frameNo,
			const bool _isActive,
			const bool _canBreak, 
			const char _timesToBreak,
			const string _id ); 

	//overload constructor 2
	Brick(	const Point * const point,
			AnimationFilm* film,
			const int w, const int h,
			const int _score,
			const char frameNo,
			const bool _isActive,
			const bool _canBreak, 
			const char _timesToBreak,
			const string _id ); 

	//destructor
	~Brick(void){}
	
	int GetScore(void)			const { return score; }
	bool GetCanBreak(void)		const { return canBreak; }
	bool IsActive(void)			const { return isActive; }
	int GetTimesToBreak(void)	const { return timesToBreak; }

	string GetID(void) const { return id; }
	void SetID(const string _id) { id = _id; }
	void SetScore(const int score)	{ this->score = score; }
	void SetCanBreak(const bool cn) { canBreak = cn; }
	void SetIsActive(const bool is) { isActive = is; }
	void SetTimesToBreak(const int times) {timesToBreak = times; }
	

	/* @target: Na kanei dep copy ena tou brick pou dinete san orisma ston euato tou.
	 * @param : To brick pou exei thn pliroforia pou 8eloume.
	 */
	void Copy(Brick* brick);

	void Move(const int dx, const int dy);

	virtual void Collide(Sprite *s);
	bool QuestionDeath(void);
};

#endif