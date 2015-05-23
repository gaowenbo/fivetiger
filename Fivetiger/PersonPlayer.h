#pragma once
#include "IPlayer.h"
#include "GameLogic.h"
#include "GoChessObserver.h"

class PersonPlayer 
{
public:
	PersonPlayer(void);
	PersonPlayer( GameLogic* logic, bool isFensive = true);
	~PersonPlayer(void);

	bool getIsTurn();
	int getGoal();
	int getFlag(){return isFensive?FENSIVE_FLAG:DEFENSIVE_FLAG;}
	bool getDragState() const { return dragState; }
	void setDragState(bool val) { dragState = val; }
	void dropChess( int indexX, int indexY );
	void startMoveChess( int indexX, int indexY );
	void endMoveChess( int indexX, int indexY );
	void pickChess( int indexX, int indexY );
	void setObserver(GoChessObserver* val){observer = val;};
private:
	bool dragState;
	int startMoveX;
	int startMoveY;
	bool isFensive;
	GameLogic* logic;
	GoChessObserver* observer;
};

