#include "PersonPlayer.h"


PersonPlayer::PersonPlayer(void)
{
	PersonPlayer(NULL);
}

PersonPlayer::PersonPlayer( GameLogic* logic, bool isFensive)
{
	dragState = false;
	this->isFensive = isFensive;
	startMoveX = 0;
	startMoveY = 0;
	this->logic = logic;
	this->observer = NULL;
}


PersonPlayer::~PersonPlayer(void)
{
}

bool PersonPlayer::getIsTurn()
{
	return  (isFensive && logic->getAvailableFlag() == FENSIVE_FLAG)
		|| (!isFensive && logic->getAvailableFlag() != FENSIVE_FLAG);
}

void PersonPlayer::dropChess( int indexX, int indexY )
{
	//生成步数代码。
	QString s;
	s.append(QString::number(getFlag()));
	s.append("s");
	s.append(QString::number(indexX));
	s.append(QString::number(indexY));
	int result = logic->run(s);

	//
	if (observer == NULL)
	{
		return;
	}
	if (result >= 0)
	{
		observer->updateDropChess(getFlag(), indexX, indexY);
		observer->changePlayer(logic->getAvailableFlag());
	}

	observer->showResult(result, result>0);
}

void PersonPlayer::startMoveChess( int indexX, int indexY )
{
	dragState = true;
	startMoveX = indexX;
	startMoveY = indexY;
}

void PersonPlayer::endMoveChess( int indexX, int indexY )
{
	//生成步数代码。
	dragState = false;
	QString s;
	s.append(QString::number(isFensive?FENSIVE_FLAG:DEFENSIVE_FLAG));
	if(indexX == startMoveX - 1 && indexY == startMoveY){
		s.append("l");
	}else if (indexX == startMoveX + 1 && indexY == startMoveY){
		s.append("r");
	}else if (indexX == startMoveX && indexY == startMoveY - 1)
	{
		s.append("u");
	}else if (indexX == startMoveX && indexY == startMoveY + 1){
		s.append("d");
	}else{
		return;
	}
	s.append(QString::number(startMoveX));
	s.append(QString::number(startMoveY));
	int result = logic->run(s);
	if (observer == NULL)
	{
		return;
	}
	if (result >= 0)
	{
		observer->updateMoveChess(getFlag(), startMoveX, startMoveY, indexX, indexY);
		if (logic->getAvailableFlag() != getFlag())
		{
			observer->changePlayer(logic->getAvailableFlag());
		}
	}
	observer->showResult(result, result>0);
}

void PersonPlayer::pickChess( int indexX, int indexY )
{
	//生成步数代码。
	QString s;
	s.append(QString::number(isFensive?FENSIVE_FLAG:DEFENSIVE_FLAG));
	s.append("p");

	s.append(QString::number(indexX));
	s.append(QString::number(indexY));
	int result = logic->run(s);
	if (observer == NULL)
	{
		return;
	}

	if (result >= 0)
	{
		observer->updatePickChess(getFlag(), indexX, indexY);
		if (logic->getAvailableFlag() != getFlag())
		{
			observer->changePlayer(logic->getAvailableFlag());
		}
	}
	observer->showResult(result, result>0);
}
