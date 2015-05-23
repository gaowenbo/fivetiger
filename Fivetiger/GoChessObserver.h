#pragma once
#include "qstring.h"

class GoChessObserver
{
public:
	virtual void updateDropChess(int flag, int x, int y) = 0;
	virtual void updateMoveChess(int flag, int startX, int startY, int endX, int endY) = 0;
	virtual void updatePickChess(int flag, int x, int y) = 0;
	virtual void changePlayer(int flag) = 0;
	virtual void showResult(int result, bool isOver) = 0;
	virtual ~GoChessObserver(void){}
};
