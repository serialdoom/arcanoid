/*Collision checker class */

#ifndef __COLLISIONCHECKER_H_
#define __COLLISIONCHECKER_H_



#include <list>
#include <iostream>

#include "Sprite.h"
#include "Brick.h"
#include "KeyLogger.h"



class CollisionChecker {
private:
	std::list<Sprite *> movable;
	std::list<Sprite *> unmovable;
	std::list<Sprite *> todelete;
	bool CheckSprites( Sprite *first, Sprite *sec);

public:
	void AddMovable(Sprite *toadd);
	void AddUnmovable(Sprite *toadd);
	void ToDelete(Sprite *sprite);
	void CollisionCheck(void);
	void CleanUp(void);

	CollisionChecker(void){}
	~CollisionChecker(void);
};

#endif