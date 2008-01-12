/*Collision checker class */

#ifndef __COLLISIONCHECKER_H_
#define __COLLISIONCHECKER_H_

#include "Sprite.h"
#include <list>
#include <iostream>

class CollisionChecker {
private:
	std::list<Sprite *> movable;
	std::list<Sprite *> unmovable;
	bool CheckSprites( Sprite *first, Sprite *sec);

public:
	CollisionChecker();
	void AddMovable(Sprite *toadd);
	void AddUnmovable(Sprite *toadd);
	void CollisionCheck(void);
};

#endif