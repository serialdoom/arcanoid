/* header file for game statistics */

#ifndef __GAMESTATS_H__
#define __GAMESTATS_H__

class GameStats {
private:
	static int score;
	static char life;
	static int bricksToGo;
	static bool scoreHasChanged;
	static bool lifeHasChanged;
	static bool lifeLost;
	static bool doublebricks;

public:
	static int GetScore(void);
	static int GetLife(void);
	static int GetBricksToGo(void);
	static void IncreaseBrick(int ammount);
	static bool ScoreChanged(void);
	static bool LifeChanged(void);
	static void SetScore(int score);
	static void IncreaseScore(int ammount);
	static void IncreaseLife(char ammount);
	static void SetLife(char life);
	static void LifeLost(void);
	static void ResetLifeLost(void);
	static bool IsLifeLost(void);
	static void SetDoubleBricks(bool v);

	static void Init(int score, char life);
	static void Terminate(void);
};


#endif