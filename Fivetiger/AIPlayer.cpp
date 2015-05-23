#include "AIPlayer.h"
#include <time.h>
#include <windows.h>


AIPlayer::AIPlayer(void)
{
	AIPlayer(NULL);
}

AIPlayer::AIPlayer( GameLogic* logic, bool isFensive)
{
	this->logic = logic;
	this->isFensive = isFensive;
	isOver = false;
	this->chessBoard = logic->getChessBoard();
	srand(int(time(0)));
}


AIPlayer::~AIPlayer(void)
{
}

void AIPlayer::Go()
{
	Sleep(300);
	if (logic->getPhase() == DROP_PHASE)
	{
		dropChess();
	}else if(logic->getPhase() == MOVE_PHASE){
		moveChess();
	}else{
		pickChess();
	}
	if (logic->getAvailableFlag() == getFlag() && !isOver)
	{
		Go();
	}else{
		observer->changePlayer(isFensive?DEFENSIVE_FLAG:FENSIVE_FLAG);
	}
}

void AIPlayer::dropChess()
{
	int maxGoal = -10000000;
	Step step;
	step.setFlag(getFlag());
	step.setAction('s');
	Step tempStep;
	tempStep.setFlag(getFlag());
	tempStep.setAction('s');
	//遍历所有可行的步数，判断每个步数的分数，取分数最大的那一步
	for(int i=0; i< 5; i++){
		for (int j=0; j< 5; j++)
		{
			if (chessBoard->getPoint(i, j) != 0)
			{
				continue;
			}
			else{
				tempStep.setPX(i);
				tempStep.setPY(j);
				int goal = getDropScore(tempStep);
				if (goal > maxGoal)
				{
					maxGoal = goal;
					step.setPX(i);
					step.setPY(j);
				}
			}
		}
	}
	if (!step.isLegal())
	{
		//异常
		return;
	}
	int result = logic->run(step.toString());
	if (result < 0)
	{
	}else if (result == 0)
	{
		observer->updateDropChess(getFlag(), step.getPX(), step.getPY());
		if (logic->getAvailableFlag() != getFlag())
		{
			observer->changePlayer(logic->getAvailableFlag());
		}
	}
	else{
		observer->updateDropChess(getFlag(), step.getPX(), step.getPY());
		observer->showResult(result, true);
		isOver = true;
	}
}

void AIPlayer::moveChess()
{
	int maxGoal = -10000000;
	Step step;
	step.setFlag(getFlag());
	Step tempStep;
	tempStep.setFlag(getFlag());
	QString action;
	//遍历所有可行的步数，判断每个步数的分数，取分数最大的那一步
	for(int i=0; i< 5; i++){
		for (int j=0; j< 5; j++)
		{
			if (chessBoard->getPoint(i, j) != getFlag())
			{
				continue;
			}
			else{
				//左右上下
				tempStep.setPX(i);
				tempStep.setPY(j);
				int goal = 0;
				if (chessBoard->getPoint(i-1,j) == 0)
				{
					tempStep.setAction('l');
					goal =  getMoveScore(tempStep);
					if (goal > maxGoal)
					{
						maxGoal = goal;
						step.setPX(tempStep.getPX());
						step.setPY(tempStep.getPY());
						step.setAction(tempStep.getAction());
					}
				}
				if (chessBoard->getPoint(i+1,j) == 0)
				{
					tempStep.setAction('r');
					goal =  getMoveScore(tempStep);
					if (goal > maxGoal)
					{
						maxGoal = goal;
						step.setPX(tempStep.getPX());
						step.setPY(tempStep.getPY());
						step.setAction(tempStep.getAction());
					}
				}
				if (chessBoard->getPoint(i,j - 1) == 0)
				{
					tempStep.setAction('u');
					goal =  getMoveScore(tempStep);
					if (goal > maxGoal)
					{
						maxGoal = goal;
						step.setPX(tempStep.getPX());
						step.setPY(tempStep.getPY());
						step.setAction(tempStep.getAction());
					}
				}
				if (chessBoard->getPoint(i,j + 1) == 0)
				{
					tempStep.setAction('d');
					goal =  getMoveScore(tempStep);
					if (goal > maxGoal)
					{
						maxGoal = goal;
						step.setPX(tempStep.getPX());
						step.setPY(tempStep.getPY());
						step.setAction(tempStep.getAction());
					}
				}
			}
		}
	}
	if (!step.isLegal())
	{
		return;
	}
	int result = logic->run(step.toString());
	if (result < 0)
	{
	}else if (result == 0)
	{
		
		observer->updateMoveChess(getFlag(), step.getPX(), step.getPY(), step.getDestX(), step.getDestY());
		if (logic->getAvailableFlag() != getFlag())
		{
			observer->changePlayer(logic->getAvailableFlag());
		}
	}
	else{
		observer->updateMoveChess(getFlag(), step.getPX(), step.getPY(), step.getDestX(), step.getDestY());
		observer->showResult(result, true);
		isOver = true;
	}
}

void AIPlayer::pickChess()
{
	int maxGoal = -10000000;
	Step step;
	step.setFlag(getFlag());
	step.setAction('p');
	Step tempStep;
	tempStep.setFlag(getFlag());
	tempStep.setAction('p');
	//遍历所有可行的步数，判断每个步数的分数，取分数最大的那一步
	for(int i=0; i< 5; i++){
		for (int j=0; j< 5; j++)
		{
			if (chessBoard->getPoint(i, j) != (isFensive?DEFENSIVE_FLAG:FENSIVE_FLAG))
			{
				continue;
			}
			else{
				tempStep.setPX(i);
				tempStep.setPY(j);
				int goal = getPickScore(tempStep);
				if (goal > maxGoal)
				{
					maxGoal = goal;
					step.setPX(i);
					step.setPY(j);
				}
			}
		}
	}

	if (!step.isLegal())
	{
		return;
	}
	int result = logic->run(step.toString());
	if (result < 0)
	{
	}else if (result == 0)
	{
		observer->updatePickChess(getFlag(), step.getPX(), step.getPY());
		if (logic->getAvailableFlag() != getFlag())
		{
			observer->changePlayer(logic->getAvailableFlag());
		}
	}
	else{
		observer->updatePickChess(getFlag(), step.getPX(), step.getPY());
		observer->showResult(result, true);
		isOver = true;
	}
}

int AIPlayer::getFlag()
{
	return isFensive?FENSIVE_FLAG:DEFENSIVE_FLAG;
}

int AIPlayer::getOtherFlag()
{
	return isFensive?DEFENSIVE_FLAG:FENSIVE_FLAG;
}

int AIPlayer::getDropScore( Step & step )
{
	return rand();
}

int AIPlayer::getPickScore( Step& step )
{
	return rand();
}

int AIPlayer::getMoveScore( Step& step )
{
	return rand();
}
