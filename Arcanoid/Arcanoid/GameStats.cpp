/* Implementation file for GameStats.h */

#include "GameStats.h"

int GameStats::score;
char GameStats::life;
bool GameStats::scoreHasChanged;

int GameStats::GetScore(void){
	scoreHasChanged = false;
	return score;
}

int GameStats::GetLife(void){
	return life;
}

int GameStats::ScoreChanged(void){
	return scoreHasChanged;
}

void GameStats::SetScore(int _score){
	score = _score;
	scoreHasChanged = true;
	return;
}

void GameStats::SetLife(char _life){
	/* Nana na nana*/ life = _life;
	return;
}

void GameStats::IncreaseScore(int ammount){
	scoreHasChanged = true;
	score += ammount;
	return;
}

void GameStats::IncreaseLife(char ammount){
	life += ammount;
	return;
}


void GameStats::Init(int _score, char _life){
	score = _score;
	life = _life;
	scoreHasChanged = true;
	return;
}

void GameStats::Terminate(void){
	return;
}