/* Testing file for Acranoid project */

#include <iostream>

using std::cout;
using std::endl;

#include "LoadFilmsInfo.h"
#include "Game.h"

int main(){
	//Game *theGame = new Game();
	allegro_init();


//////////////////////////////////////////////////////////////////////
//xrhsh ths LoadFilmsInfo
	LoadFilmsInfo filmsInfo("./configs_files/films.cfg");

	FilmsInfoMap test = filmsInfo.GetFilmsInfo();
	cout<<">"<<filmsInfo.GetFilmsNo()<<"<"<<endl;
	
	FilmsInfoMap::iterator start	= test.begin();
	FilmsInfoMap::iterator end		= test.end();

	while( start != end ){
		cout<<"id\t:"<<(*start).first<<endl;
		cout<<"bboxes\t:"<<(*start).second.first<<endl;
		cout<<"bitmap\t:"<<(*start).second.second<<endl;
		start++;
	}
/////////////////////////////////////////////////////////////////////



	return 0;
}
END_OF_MAIN()