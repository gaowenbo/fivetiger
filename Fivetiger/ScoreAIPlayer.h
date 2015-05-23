#pragma once
#include "aiplayer.h"
class ScoreAIPlayer :
	public AIPlayer
{
public:
	ScoreAIPlayer(void);
	ScoreAIPlayer(GameLogic* logic, bool isFensive = false);
	~ScoreAIPlayer(void);
	int getDropScore( Step & step );
	int getPickScore(Step& step);
	int getMoveScore(Step& step);
};

