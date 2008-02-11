
#include <string>
#include "PowerUp.h"






//Elegxei gia kathe brick an periexei dwraki h' oxi
void PowerUp::ApplyBonus(string gift){
	
	if(gift.compare("none"))
		;
	else{
		for(int i=0; i<MAX_POWER; i++){
			if(this->NamePorewUp[i].compare(gift)){

				;
			}
		}
	}

}	