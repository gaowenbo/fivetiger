#include "MidLevelAIPlayer.h"


MidLevelAIPlayer::MidLevelAIPlayer(void)
{
}

MidLevelAIPlayer::MidLevelAIPlayer( GameLogic* logic, bool isFensive /*= false*/ ):AIPlayer(logic, isFensive)
{

}

MidLevelAIPlayer::~MidLevelAIPlayer(void)
{
}

const int MidLevelAIPlayer::offsetX[4] = {0,0,-1,1};
const int MidLevelAIPlayer::offsetY[4] = {-1,1,0,0};	
const char MidLevelAIPlayer::MOVE_ACTION[4] = {'u','d','l','r'};
const int MidLevelAIPlayer::POSITION_SCORE[5][5] = {{0, 1, 5, 1, 0},
													{1, 6, 4, 6, 1},
													{4, 4, 5, 3, 4},
													{1, 6, 4, 6, 1},
													{0, 1, 5, 1, 0}};

int MidLevelAIPlayer::getDropScore( Step & step )
{
	GameLogic game(*logic);
	
	if (game.getChessBoard()->GetChessCount() < 6)
	{
		return GetDropMaxScore(&game, step, 1, getFlag()) 
			+  POSITION_SCORE[step.getDestX()][step.getDestY()] * 10 + rand()%10;;
	}
	return GetDropMaxScore(&game, step, 3, getFlag()) 
		+  POSITION_SCORE[step.getDestX()][step.getDestY()] * 10 + rand()%10;
}

int MidLevelAIPlayer::getMoveScore( Step & step )
{
	GameLogic game(*logic);
	if ( game.getChessBoard()->GetChessCount() < 16 && game.getChessBoard()->GetChessCount() > 10)
	{
		return GetMoveMaxScore(&game, step, 4, getFlag()) 
			+ POSITION_SCORE[step.getDestX()][step.getDestY()] * 10 + rand()%10;
	}
	return GetMoveMaxScore(&game, step, 5, getFlag()) 
		+ POSITION_SCORE[step.getDestX()][step.getDestY()] * 10 + rand()%10;
}

int MidLevelAIPlayer::GetDropMaxScore(GameLogic* logic, Step & step, int deepth , int flag)
{
	GameLogic game(*logic);
	game.moveOnBoard(step);
	int score = game.calculateGoal(step) * 1000 * (flag==getFlag()?1:-1) * (deepth + 10) / 10;
	if (deepth == 0)
	{
		return score;
	}
	int thisFlag = flag==getFlag()?getOtherFlag():getFlag();
	Step tempStep;
	tempStep.setFlag(thisFlag);
	tempStep.setAction('s');
	int maxScore = 0;
	bool canDrop = false;
	for (int i = 0; i< 5; i++)
	{
		for (int j = 0; j < 5; j ++)
		{
			if (game.getChessBoard() ->getPoint(i, j) != 0)
			{
				continue;
			}
			else{
				tempStep.setPX(i);
				tempStep.setPY(j);
				int tempScore = GetDropMaxScore(&game, tempStep, deepth - 1, thisFlag);
				if (!canDrop)
				{
					maxScore = tempScore;
				}
				if (thisFlag == getFlag())
				{
					if (tempScore > maxScore)
					{
						maxScore = tempScore;
					}
				}else{
					if (tempScore < maxScore)
					{
						maxScore = tempScore;
					}
				}
				
				canDrop = true;
			}
		}
	}

	return score + (canDrop?maxScore:0);
}

int MidLevelAIPlayer::GetMoveMaxScore( GameLogic* logic, Step & step, int deepth, int flag )
{
	GameLogic game(*logic);
	game.moveOnBoard(step);
	int score = game.calculateGoal(step) * 1000 * (flag==getFlag()?1:-1) * (deepth * 4 + 1) / 10;
	if (deepth == 0)
	{
		return score;
	}
	int thisFlag = flag==getFlag()?getOtherFlag():getFlag();
	Step tempStep;
	tempStep.setFlag(thisFlag);
	int maxScore = 0;
	bool canMove = false;
	for (int i = 0; i< 5; i++)
	{
		for (int j = 0; j < 5; j ++)
		{
			if (game.getChessBoard() ->getPoint(i, j) != thisFlag)
			{
				continue;
			}
			else{
				tempStep.setPX(i);
				tempStep.setPY(j);
				for (int m = 0; m < 4; m++)
				{
					if (game.getChessBoard()->getPoint(i + offsetX[m],j + offsetY[m]) != 0)
					{
						continue;
					}
					tempStep.setAction(MOVE_ACTION[m]);
					int tempScore = GetMoveMaxScore(&game, tempStep, deepth - 1, thisFlag);
					if (!canMove)
					{
						maxScore = tempScore;
					}
					if (thisFlag == getFlag())
					{
						if (tempScore > maxScore)
						{
							maxScore = tempScore;
						}
					}else{
						if (tempScore < maxScore)
						{
							maxScore = tempScore;
						}
					}

					canMove = true;
				}
			}
		}
	}

	return score + (canMove?maxScore:0);
}

int MidLevelAIPlayer::getPickScore( Step& step )
{
	return POSITION_SCORE[step.getDestX()][step.getDestY()] * 10 + rand()%10;
}



