/* Testing file for TerrainBuilder.h */


#include <iostream>
#include "TerrainBuilder.h"
#include "CollisionChecker.h"

int main(){
	CollisionChecker *asd;

	asd = new CollisionChecker();
	TerrainBuilder apixiscool(asd);

	if(!apixiscool.Load("kanoniko.lvl")) return 1;
	std::cout << "Collision checking is going to happen ..." << std::endl;
	asd->CollisionCheck();

	std::cout << "All ok !" << std::endl;
	system("pause");
	return 0;
}