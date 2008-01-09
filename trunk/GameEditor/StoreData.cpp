/*
 *author: koutsop
 */
#include "StoreData.h"


StoreData::~StoreData(void)
{
}


/*
[0, 0] {farme Number = 1} up{up.x=4, up.y=4}  down{down.x=28,
down.y=16} {Width = 24} {Height = 12} {canBreak = 1} {time to break =
1} {score = 10}
*/
void StoreData::StoreGame(const Terrain& terrain) const{
	ofstream out(fileName.c_str());
	
	Brick* tmp = (Brick*)0;
	int row		= terrain.GetTerrainRow();
	int colum	= terrain.GetTerrainColum();

	for(int i = 0; i < row; i++){				//Diatrexoume olon ton pinaka
		for(int j = 0; j < colum; j++){
			tmp = terrain.GetTerrainBrick(i, j);
			assert(tmp);

			if( tmp->IsActive() ){				//Grafoume mono osa kelia tou pinaka exoun energopiei8oi
				out<<"["<<i<<", "<<j<<"] ";		//dhl exoume balei mesa se auta ena brick

				out<< "{farme Number = "	<< tmp->GetFrameNum()				<<"} ";
				out<< "up{up.x="			<< tmp->GetPointUpLeft().GetX();
				out<<", up.y="				<< tmp->GetPointUpLeft().GetY()		<<"}  ";
				out<<"down{down.x="			<< tmp->GetPointDownRight().GetX();
				out<<", down.y="			<< tmp->GetPointDownRight().GetY()	<<"} ";
				out<<"{Width = "			<< tmp->GetWidth()					<<"} ";
				out<<"{Height = "			<< tmp->GetHeight()					<<"} ";
				out<<"{canBreak = "			<< tmp->GetCanBreak()				<<"} ";
				out<<"{time to break = "	<< tmp->GetTimesToBreak()			<<"} ";
				out<<"{score = "			<< tmp->GetScore()					<<"}\n";
			}//if
		}//for i
	}//for i
	return;
}
