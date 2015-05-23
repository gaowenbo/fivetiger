#pragma once
#include "GameLogic.h"
#include "GoChessObserver.h"
class AIPlayer
{
public:
	AIPlayer(void);
	AIPlayer(GameLogic* logic, bool isFensive = false);
	void Go();
	void setObserver(GoChessObserver* val){observer = val;}
	~AIPlayer(void);
	virtual void dropChess();
	virtual void moveChess();
	virtual void pickChess();
	int getFlag();
	int getOtherFlag();
	virtual int getDropScore( Step & step );
	virtual int getPickScore(Step& step);
	virtual int getMoveScore(Step& step);
protected:
	bool isFensive;
	GameLogic* logic;
	ChessBoard* chessBoard;
	GoChessObserver* observer;
	bool isOver;
};

