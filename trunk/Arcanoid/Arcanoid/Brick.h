/*
 *author: koutsop
 */

#ifndef BRICK_H
#define BRICK_H

#include <string>
#include <cassert>
#include <allegro.h>	//Eidea den exw giati xriazete ala stamata na peta la8oi h allgero
#include <iostream>

#include "PowerUp.h"
#include "Point.h"
#include "Oblong.h"
#include "Sprite.h"
#include "GameStats.h"
#include "AnimationFilm.h"


using namespace std;

class Brick : public Sprite{
private:
	int speed;
	int  score;
	char timesToBreak;
	bool canBreak, isActive;
	string id;
	bool up;		//mas leei an to brick paei panw h' katw
	bool isRunning;
	powerups_t gift; // mas enhmerwnei an exei paowerup to Brick
	
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
	

	int GetSpeed(void) const { return speed; }
	void SetSpeed(int newSpeed) { speed = newSpeed; }
	int GetScore(void)			const { return score; }
	bool GetCanBreak(void)		const { return canBreak; }
	
	bool IsRunning(void)	const { return isRunning; }
	void SetIsRunning(bool b)	{ isRunning = b; }
	
	bool IsActive(void)			const { return isActive; }
	void SetIsActive(bool b){ isActive = b;}
	int GetTimesToBreak(void)	const { return timesToBreak; }

	string GetID(void) const { return id; }
	void SetID(const string _id) { id = _id; }
	void SetScore(const int score)	{ this->score = score; }
	void SetCanBreak(const bool cn) { canBreak = cn; }
	void SetTimesToBreak(const int times) {timesToBreak = times; }
	

	/* @target: Na kanei dep copy ena tou brick pou dinete san orisma ston euato tou.
	 * @param : To brick pou exei thn pliroforia pou 8eloume.
	 */
	void Copy(Brick* brick);

	void SetGift(powerups_t _gift) { gift = _gift; }
	powerups_t GetGift(void) const { return gift; }

	void Move(const int dx, const int dy);

	virtual void Collide(Sprite *s);
	bool QuestionDeath(void);
};

#endif