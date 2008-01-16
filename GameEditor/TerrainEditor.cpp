/*
 *author: koutsop
 */
#include "TerrainEditor.h"

bool TerrainEditor::areLoadData;
BITMAP*	 TerrainEditor::terrainBackground;


TerrainEditor::TerrainEditor(void){
	areLoadData = false;
}

TerrainEditor::~TerrainEditor(void){
	bitmaps.clear();
}


void TerrainEditor::SwitchIn(){
	if(areLoadData){
		scare_mouse();
		blit(terrainBackground, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);	
		unscare_mouse();
	}
	return;
}

void TerrainEditor::Init(void){
	allegro_init();			// Initialize Allegro
	install_timer();
	install_keyboard();		// Initialize keyboard routines
	install_mouse();

	set_color_depth(16);	// Set the color depth
	set_gfx_mode(GFX_AUTODETECT, 640,480,0,0); 
	//set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640,480,0,0); // Change our graphics mode to 640x480
	
	set_window_title("Game Editor (koutsop@csd.uoc.gr)");	
	set_display_switch_mode(SWITCH_AMNESIA);
	set_display_switch_callback(SWITCH_IN, TerrainEditor::SwitchIn);

	bitmaps.insert( Map::value_type("okCancel", NULL) );
	bitmaps.insert( Map::value_type("background", NULL) );
	bitmaps.insert( Map::value_type("bufferBack", NULL) );
	bitmaps.insert( Map::value_type("bricksFilm", NULL) );

	return;
}

void TerrainEditor::LoadData(void){
	data.LoadOkCancel(choice);
	data.LoadTerrainInfo(terrain);
	data.LoadBricksFilmInfo(bricks);
	data.LoadBricksFilm(bricks);
	data.LoadFileNameToWrite();
	areLoadData = true;
	return;
}

void TerrainEditor::LoadTerrainInfo(void){
	terrain.LoadTerrain(bricks.GetBrickWidth(), bricks.GetBrickHeight());
	terrain.PrintTerrainBricksCor();
	return;
}

void TerrainEditor::LoadBitmaps(void){
	bitmaps.find("background")->second  = terrain.LoadBitmapTerrain( bitmaps.find("background")->second );
	bitmaps.find("bufferBack")->second  = terrain.LoadBitmapTerrain( bitmaps.find("bufferBack")->second );
	bitmaps.find("bricksFilm")->second  = bricks.LoadBitmapBricks( bitmaps.find("bricksFilm")->second );
	bitmaps.find("okCancel")->second	= choice.LoadBitmapOkCancel(bitmaps.find("okCancel")->second);
	return;
}

void TerrainEditor::BlitBitmaps(void){
	bricks.BlitBricks(bitmaps.find("bricksFilm")->second, bitmaps.find("background")->second);
	choice.BlitOkCancel(bitmaps.find("okCancel")->second, bitmaps.find("background")->second);
	terrain.BlitTerrain(bitmaps.find("background")->second, bitmaps.find("bufferBack")->second);
	terrain.BlitTerrain(bitmaps.find("bufferBack")->second, screen);		//Edw blit to background sthn o8onh
	
	terrainBackground = bitmaps.find("bufferBack")->second;
	set_mouse_cursor_bitmap(MOUSE_CURSOR_ARROW, NULL);
	show_mouse(screen);

	return;
}

void TerrainEditor::Deinit(void){
	destroy_bitmap(bitmaps.find("background")->second);
	destroy_bitmap(bitmaps.find("bufferBack")->second);
	destroy_bitmap(bitmaps.find("bricksFilm")->second);
	destroy_bitmap(bitmaps.find("okCancel")->second);
	allegro_exit();
	return;
}


void TerrainEditor::StartEditor(void){
	Init();
	LoadData();
	LoadTerrainInfo();
	LoadBitmaps();
	BlitBitmaps();

	BITMAP* bricksFilm = bitmaps.find("bricksFilm")->second;
	BITMAP* background = bitmaps.find("background")->second;
	BITMAP* buffer = bitmaps.find("bufferBack")->second;

	while(!key[KEY_ESC]) {
		inputManager.CheckBricks(terrain, bricks, bricksFilm, background, buffer);
		inputManager.CheckOkCancel(choice);
		if( choice.PushOk() ){
			StoreData storeData(data.GetFileNameToWrite());
			storeData.StoreGame(terrain);
			break;
		}
		if( choice.PushCancel() )
			break;
	}//end while

	Deinit();
	return;
}