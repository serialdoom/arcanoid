/* Implementation of the Game.h */

#include "Game.h"


#define CONFIG_FILE "./game.cfg"
#define BUFF_SZ 20321



Game::Game(void){
	//Innits
	KeyLogger::Init("arcanoid.log");
	KeyLogger::Write("KeyLogger is up and running.\n");

	KeyLogger::Write("Initiallizing ColLision Checker...\n");
	cc = new CollisionChecker();
	KeyLogger::Write("Initiallizing StateHolder...\n");
	StateHolder::Init();
	KeyLogger::Write("Initiallizing SpriteHolder...\n");
	sp = new SpriteHolder();
	KeyLogger::Write("Initiallizing Terrain Builder...\n");
	tbuilder = new TerrainBuilder(cc, sp);

	//Open file for data extraction
	KeyLogger::Write("Opening \"%s\" to read the data...\n", CONFIG_FILE);
	set_config_file(CONFIG_FILE);

	KeyLogger::Write("Reading a random number... %d. \n", get_config_int("GENERAL", "random", 666));
	KeyLogger::Write("Reading a random String... \"%s\".\n", get_config_string("FILE_NAME_CFG", "file_name_file", ""));

	KeyLogger::Write("Loading the terrain...\n");
	tbuilder->Load(get_config_string("GENERAL", "level_file", ""));

	KeyLogger::Write("Creating the ball...\n");
	return;
}