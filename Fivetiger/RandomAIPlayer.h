#pragma once
#include "aiplayer.h"
class RandomAIPlayer :
	public AIPlayer
{
public:
	RandomAIPlayer(void);
	RandomAIPlayer(GameLogic* logic, bool isFensive = false);
	~RandomAIPlayer(void);
	void dropChess();
	void moveChess();
	void pickChess();
};

