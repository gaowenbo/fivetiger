#include "RandomAIPlayer.h"
#include <atlcomtime.h>


RandomAIPlayer::RandomAIPlayer(void)
{
}

RandomAIPlayer::RandomAIPlayer( GameLogic* logic, bool isFensive ):AIPlayer(logic, isFensive)
{
	srand(DATE());
}


RandomAIPlayer::~RandomAIPlayer(void)
{
}

void RandomAIPlayer::dropChess()
{
	int maxGoal = 0;
	int x = 0, y = 0;
	//遍历所有可行的步数，判断每个步数的分数，取分数最大的那一步
	for(int i=0; i< 5; i++){
		for (int j=0; j< 5; j++)
		{
			if (chessBoard->getPoint(i, j) != 0)
			{
				continue;
			}
			else{
				
				int goal = rand();
				if (goal > maxGoal)
				{
					maxGoal = goal;
					x = i;
					y = j;
				}
			}
		}
	}

	QString s;
	s.append(QString::number(getFlag()));
	s.append(QString("s"));
	s.append(QString::number(x));
	s.append(QString::number(y));
	int result = logic->run(s);
	if (result < 0)
	{
	}else if (result == 0)
	{
		observer->updateDropChess(getFlag(), x, y);
		if (logic->getAvailableFlag() != getFlag())
		{
			observer->changePlayer(logic->getAvailableFlag());
		}
	}
	else{
		observer->updateDropChess(getFlag(), x, y);
		observer->showResult(result, true);
		isOver = true;
	}
}

void RandomAIPlayer::moveChess()
{

	int maxGoal = 0;
	int x = 0, y = 0, endX = 0, endY = 0;
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
				int goal = 0;
				if (chessBoard->getPoint(i-1,j) == 0)
				{
					goal = rand();
					if (goal > maxGoal)
					{
						maxGoal = goal;
						x = i;
						y = j;
						endX = i - 1;
						endY = j;
						action = "l";
					}
				}
				if (chessBoard->getPoint(i+1,j) == 0)
				{
					goal = rand();
					if (goal > maxGoal)
					{
						maxGoal = goal;
						x = i;
						y = j;
						endX = i + 1;
						endY = j;
						action = "r";
					}
				}
				if (chessBoard->getPoint(i,j - 1) == 0)
				{
					goal = rand();
					if (goal > maxGoal)
					{
						maxGoal = goal;
						x = i;
						y = j;
						endX = i;
						endY = j - 1;
						action = "u";
					}
				}
				if (chessBoard->getPoint(i,j + 1) == 0)
				{
					goal = rand();
					if (goal > maxGoal)
					{
						maxGoal = goal;
						x = i;
						y = j;
						endX = i;
						endY = j + 1;
						action = "d";
					}
				}
			}
		}
	}


	QString s;

	s.append(QString::number(getFlag()));
	s.append(action);
	s.append(QString::number(x));
	s.append(QString::number(y));
	int result = logic->run(s);
	if (result < 0)
	{
	}else if (result == 0)
	{
		observer->updateMoveChess(getFlag(), x, y, endX, endY);
		if (logic->getAvailableFlag() != getFlag())
		{
			observer->changePlayer(logic->getAvailableFlag());
		}
	}
	else{
		observer->updateMoveChess(getFlag(), x, y, endX, endY);
		observer->showResult(result, true);
		isOver = true;
	}
}

void RandomAIPlayer::pickChess()
{
	int maxGoal = 0;
	int x = 0, y = 0;
	//遍历所有可行的步数，判断每个步数的分数，取分数最大的那一步
	for(int i=0; i< 5; i++){
		for (int j=0; j< 5; j++)
		{
			if (chessBoard->getPoint(i, j) != (isFensive?DEFENSIVE_FLAG:FENSIVE_FLAG))
			{
				continue;
			}
			else{

				int goal = rand();
				if (goal > maxGoal)
				{
					maxGoal = goal;
					x = i;
					y = j;
				}
			}
		}
	}

	QString s;
	s.append(QString::number(getFlag()));
	s.append(QString("p"));
	s.append(QString::number(x));
	s.append(QString::number(y));
	int result = logic->run(s);
	if (result < 0)
	{
	}else if (result == 0)
	{
		observer->updatePickChess(getFlag(), x, y);
		if (logic->getAvailableFlag() != getFlag())
		{
			observer->changePlayer(logic->getAvailableFlag());
		}
	}
	else{
		observer->updatePickChess(getFlag(), x, y);
		observer->showResult(result, true);
		isOver = true;
	}
}