/* header file for game statistics */

#ifndef __GAMESTATS_H__
#define __GAMESTATS_H__

class GameStats {
private:
	static int score;
	static char life;
	static bool scoreHasChanged;

public:
	static int GetScore(void);
	static int GetLife(void);
	static int ScoreChanged(void);
	static void SetScore(int score);
	static void IncreaseScore(int ammount);
	static void IncreaseLife(char ammount);
	static void SetLife(char life);
	static void Init(int score, char life);
	static void Terminate(void);
};


#endif