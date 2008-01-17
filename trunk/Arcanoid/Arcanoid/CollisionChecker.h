/*Collision checker class */

#ifndef __COLLISIONCHECKER_H_
#define __COLLISIONCHECKER_H_



#include <list>
#include <iostream>

#include "Sprite.h"



class CollisionChecker {
private:
	std::list<Sprite *> movable;
	std::list<Sprite *> unmovable;
	bool CheckSprites( Sprite *first, Sprite *sec);

public:
	void AddMovable(Sprite *toadd);
	void AddUnmovable(Sprite *toadd);
	void CollisionCheck(void);

	CollisionChecker(void){}
	~CollisionChecker(void);
};

#endif