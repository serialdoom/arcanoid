/*
 *author: koutsop
 */
//TODO na dw na mporw na ala3w to static buffer pou exw edw kai pou ton 
//xrisimopiw gia thn SwitchIn
#ifndef GAMEEDITOR_H
#define GAMEEDITOR_H


#include <map>
#include <string>

#include "Terrain.h"
#include "OkCancel.h"
#include "LoadData.h"
#include "StoreData.h"
#include "BricksFilm.h"
#include "InputManager.h"


using namespace std;

typedef map<string, BITMAP *>Map;

class GameEditor {
private:
	Map			 bitmaps;
	LoadData	 data;
	BricksFilm	 bricks;
	Terrain		 terrain;
	InputManager inputManager;
	OkCancel	 choice;
	static bool		 areLoadData;	//Elegxoume an exoun fwrto8ei ta dedomena
	static BITMAP*	 terrainBackground;

	//////////////////////////////////  private functions
	static void SwitchIn();

	/* @target: Kanei init thn allegro kai to Map bitmaps
	 */
	void Init(void);

	/* @target: Kanei load ta data apoto configure file
	 */
	void LoadData(void);

	/* @target: Kanei load ta dedomena gia thn dimiourgeia tou terrain
	 */
	void LoadTerrainInfo(void);
	
	/* @target: Kanei load ta blitmaps
	 */
	void LoadBitmaps(void);

	/* @target: Kanei blit ta bitmaps
	 */
	void BlitBitmaps(void);

	/* @target: Diagrafei ola ta bitmaps pou exoun dimiourgi8ei
	 */
	void Deinit(void);


public:
	GameEditor(void);
	~GameEditor(void);

	/* @target: Na dimiourgei thn arxh enos neou game editor
	 */
	void StartEditor(void);		
};

#endif GAMEEDITOR_H