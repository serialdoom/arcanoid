/*
 *author: koutsop
 */

#ifndef BRICK_H
#define BRICK_H

#include <string>
#include <cassert>
#include "Oblong.h"
#include "Point.h"
#include "Sprite.h"

using namespace std;

class Brick : public Oblong, public Sprite{
private:
	int frameNum, timesToBreak, score;
	bool canBreak, isActive;	
	//To isActive 8a to xriastoume gia na 3eroume an ena brick tou pinaka exei
	//sxediastei apo ton xristi h' oxi.

public:
	//constructor
	Brick(	const int _frameNum, 
			const Point _up, 
			const Point _down, 
			const int w, const int h, 
			const bool _canBreak, 
			const int _timesToBreak, 
			const int _score, 
			const bool _isActive);

	//overload constructor
	Brick(	const int _frameNum, 
			const Point * const _up, 
			const Point * const _down, 
			const int w, const int h, 
			const bool _canBreak, 
			const int _timesToBreak, 
			const int _score, 
			const bool _isActive);

	//destructor
	~Brick(void);

	int GetScore(void)			const { return score; }
	int GetFrameNum(void)		const { return frameNum; }
	bool GetCanBreak(void)		const { return canBreak; }
	bool IsActive(void)			const { return isActive; }
	int GetTimesToBreak(void)	const { return timesToBreak; }

	void SetScore(const int score)	{ this->score = score; }
	void SetFrameNum(const int num)	{ frameNum = num; }
	void SetCanBreak(const bool cn) { canBreak = cn; }
	void SetIsActive(const bool is) { isActive = is; }
	void SetTimesToBreak(const int times) {timesToBreak = times; }
	

	/* @target: Na kanei dep copy ena tou brick pou dinete san orisma ston euato tou.
	 * @param : To brick pou exei thn pliroforia pou 8eloume.
	 */
	void Copy(Brick* brick);

};

#endif