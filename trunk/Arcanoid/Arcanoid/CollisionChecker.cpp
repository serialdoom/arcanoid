#include "CollisionChecker.h"
//#include <list>


CollisionChecker::~CollisionChecker(void){
	movable.clear();
	unmovable.clear();
}



void CollisionChecker::AddMovable(Sprite *toadd){
	//Debugging, use only with CollisionCHeckerTest.cpp std::cout << "Adding " << toadd->x << " to movables.\n";
	movable.push_back(toadd);
}

void CollisionChecker::AddUnmovable(Sprite *toadd){
	//Debugging, use only with CollisionCHeckerTest.cpp std::cout << "Adding " << toadd->x << " to UNmovables.\n";
	unmovable.push_back(toadd);
}

void CollisionChecker::CollisionCheck(void){
	//Compare all the movable objects with all the movable objects.
	for( std::list<Sprite *>::iterator iteMovable = movable.begin(); iteMovable != movable.end() ; ++iteMovable){
		for(std::list<Sprite *>::iterator iteMovable2 = movable.begin(); iteMovable2 != movable.end(); ++iteMovable2){
			// TODO: do some serious collision checking here.
			// Debugging checking, use only with CollisionCHeckerTest.cpp if((*iteMovable)->x == (*iteMovable2)->x) std::cout << "Mov with Mov: Collision detected for : " << (*iteMovable)->x << " and " << (*iteMovable2)->x  << std::endl ; //debugging
			if(iteMovable != iteMovable2) CheckSprites(*iteMovable, *iteMovable2);
		}
		for(std::list<Sprite *>::iterator iteUnmovable = unmovable.begin(); iteUnmovable != unmovable.end(); ++iteUnmovable){
			// TODO: make some serious collision detection here.
			// Debuging checking, use only with CollisionCheckerTest.cpp if( (*iteMovable)->x == (*iteUnmovable)->x ) std::cout << "Mov with Unmov: Collision detected for : " << (*iteMovable)->x << " and " << (*iteUnmovable)->x << std::endl ; // debugging
			CheckSprites(*iteMovable, *iteUnmovable);
		}
	}
	return;
}

bool CollisionChecker::CheckSprites(Sprite *first, Sprite *sec){
	//TODO: write some code biatch
	return true;
}