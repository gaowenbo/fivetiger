#pragma once
#include "aiplayer.h"
class MidLevelAIPlayer :
	public AIPlayer
{
public:
	MidLevelAIPlayer(void);
	MidLevelAIPlayer( GameLogic* logic, bool isFensive = false);
	~MidLevelAIPlayer(void);

	int getDropScore( Step & step );
	int getMoveScore( Step & step);
	int getPickScore(Step& step);
	static const int offsetX[4];
	static const int offsetY[4];
	static const char MOVE_ACTION[4];
	static const int POSITION_SCORE[5][5];

	int GetDropMaxScore(GameLogic* logic, Step & step, int deepth, int flag);
	int GetMoveMaxScore(GameLogic* logic, Step & step, int deepth, int flag);
};

