/* Implementation file for GameStats.h */

#include "GameStats.h"

int GameStats::score;
char GameStats::life;
bool GameStats::scoreHasChanged;
bool GameStats::lifeHasChanged;
int GameStats::bricksToGo;
bool GameStats::lifeLost;
bool GameStats::doubleblicks;

int GameStats::GetBricksToGo(void){
	return bricksToGo;
}

void GameStats::IncreaseBrick(int ammount){
	bricksToGo += ammount;
	return;
}

int GameStats::GetScore(void){
	scoreHasChanged = false;
	return score;
}

void GameStats::LifeLost(void){
	lifeLost = true;
	if( --life < 0) life = 0;
	return;
}

bool GameStats::IsLifeLost(void){
	return lifeLost;
}

void GameStats::SetDoubleBricks(bool v){
	doubleblicks = v;
}

void GameStats::ResetLifeLost(void){
	lifeLost = false;
	return;
}

int GameStats::GetLife(void){
	lifeHasChanged = false;
	return life;
}

bool GameStats::ScoreChanged(void){
	return scoreHasChanged;
}

void GameStats::SetScore(int _score){
	score = _score;
	scoreHasChanged = true;
	return;
}

bool GameStats::LifeChanged(void){
	return lifeHasChanged;
}

void GameStats::SetLife(char _life){
	/* Nana na nana*/ life = _life;
	lifeHasChanged = false;
	return;
}

void GameStats::IncreaseScore(int ammount){
	scoreHasChanged = true;
	score += (doubleblicks)?(ammount*2):ammount;
	return;
}

void GameStats::IncreaseLife(char ammount){
	lifeHasChanged = true;
	life += ammount;
	if(life < 0) life = 0;
	return;
}


void GameStats::Init(int _score, char _life){
	score = _score;
	life = _life;
	scoreHasChanged = true;
	lifeHasChanged = false;
	return;
}

void GameStats::Terminate(void){
	return;
}