#include "GameLogic.h"


GameLogic::GameLogic(void)
{
	chessBoard = new ChessBoard();
	fensiveInfo = new FlagInfo();
	defensiveInfo = new FlagInfo();
	list = new QStringList();
}

GameLogic::GameLogic( const GameLogic& gameLogic )
{
	dropFinished = gameLogic.dropFinished;
	availableFlag = gameLogic.availableFlag;
	phase = gameLogic.phase;
	dropFinished = gameLogic.dropFinished;
	startMove = gameLogic.startMove;
	result = gameLogic.result;
	fensiveInfo = new FlagInfo(*gameLogic.fensiveInfo);
	defensiveInfo = new FlagInfo(*gameLogic.defensiveInfo);
	chessBoard = new ChessBoard(*gameLogic.chessBoard);
	list = new QStringList(*gameLogic.list);
}


GameLogic::~GameLogic(void)
{
	delete chessBoard;
	delete fensiveInfo;
	delete defensiveInfo;
	delete list;
}

void GameLogic::start()
{
	fensiveInfo->setFlag(FENSIVE_FLAG);
	defensiveInfo->setFlag(DEFENSIVE_FLAG);
	phase = DROP_PHASE;
	result = RESULT_UNKNOW_WIN;
	dropFinished = false;
	availableFlag = 1;
	startMove = false;
}

void GameLogic::go( Step &step )
{
	if(allowMove(step)){
		moveOnBoard(step);
		FlagInfo* flagInfo;
		FlagInfo* otherFlagInfo;
		if (step.getFlag() == FENSIVE_FLAG){
			flagInfo = fensiveInfo;
			otherFlagInfo = defensiveInfo;
		}else{
			flagInfo = defensiveInfo;
			otherFlagInfo = fensiveInfo;
		}
		flagInfo->setGoal(flagInfo->getGoal() + calculateGoal(step));
		judgePhase(flagInfo, otherFlagInfo);
		judgeWin(flagInfo, otherFlagInfo);
	}
}

bool GameLogic::allowMove( Step & step )
{
	if(step.getFlag() != availableFlag){
		result = RESULT_FLAG_ERR;
		return false;
	}

	if(DROP_PHASE == phase){
		if(step.getAction() != Step::DROP){
			result = RESULT_PHRASE_DROP;
			return false;
		}

		if(chessBoard->getPoint(step.getPX(), step.getPY()) != 0){
			result = RESULT_PHRASE_DROP_EXIST;
			return false;
		}
	}

	int otherFlag;
	FlagInfo* flagInfo;
	if(step.getFlag() == FENSIVE_FLAG){
		otherFlag = DEFENSIVE_FLAG;
		flagInfo = fensiveInfo;
	}else{
		otherFlag = FENSIVE_FLAG;
		flagInfo = defensiveInfo;
	}

	if(PICK_PHASE == phase){
		if(Step::PICK != step.getAction()){
			result = RESULT_PHRASE_PICK;
			return false;
		}

		//不是对方的子
		if (chessBoard->getPoint(step.getPX(), step.getPY()) != otherFlag)
		{
			result = RESULT_PHRASE_PICK_NOTOTHER;
			return false;
		}
	}									

	if(MOVE_PHASE == phase){
		if(Step::PICK != step.getAction() && 
			Step::MOVEDOWN != step.getAction() &&
			Step::MOVELEFT != step.getAction() &&
			Step::MOVERIGHT != step.getAction() &&
			Step::MOVEUP != step.getAction()){
				result = RESULT_PHRASE_MOVE;
				return false;
		}

		//不是自己的子
		if(chessBoard->getPoint(step.getPX(), step.getPY()) != flagInfo->getFlag()){
			result = RESULT_PHRASE_MOVE_NOTSELF;
			return false;
		}

		//不是空地
		if(chessBoard->getPoint(step.getDestX(), step.getDestY()) != 0){
			result = RESULT_PHRASE_MOVE_NOTBLANK;
			return false;
		}
	}
	return true;
}

void GameLogic::moveOnBoard( Step & step)
{

	if(Step::DROP == step.getAction()){
		chessBoard->setPoint(step.getPX(), step.getPY(), step.getFlag());
	}else if(Step::MOVEUP == step.getAction()){
		chessBoard->setPoint(step.getPX(), step.getPY(), 0);
		chessBoard->setPoint(step.getPX(), step.getPY() - 1, step.getFlag());			
	}else if(Step::MOVEDOWN == step.getAction()){
		chessBoard->setPoint(step.getPX(), step.getPY(), 0);
		chessBoard->setPoint(step.getPX(), step.getPY() + 1, step.getFlag());			
	}else if(Step::MOVELEFT == step.getAction()){
		chessBoard->setPoint(step.getPX(), step.getPY(), 0);
		chessBoard->setPoint(step.getPX() - 1, step.getPY(), step.getFlag());
	}else if(Step::MOVERIGHT == step.getAction()){
		chessBoard->setPoint(step.getPX(), step.getPY(), 0);
		chessBoard->setPoint(step.getPX() + 1, step.getPY(), step.getFlag());	
	}else if(Step::PICK == step.getAction()){
		chessBoard->setPoint(step.getPX(), step.getPY(), 0);
	}
}

int GameLogic::calculateGoal(Step & step )
{
	if (step.getAction() == Step::PICK){
		return -1;
	}else{
		int goal = 0;
		int x = step.getDestX();
		int y = step.getDestY();
		int flag = step.getFlag();
		
		//宝井 1 
		if (chessBoard->getPoint(x - 1, y - 1) == flag && chessBoard->getPoint(x - 1, y) == flag
			&& chessBoard->getPoint(x, y - 1) == flag){
				QString s;
				s.append(QString::number(flag));
				s.append(QString::number(1));
				s.append(QString::number(x - 1));
				s.append(QString::number(y - 1));
				if (list->indexOf(s) == -1)
				{
					list->append(s);
					goal = goal + 1;
				}
		}
		if (chessBoard->getPoint(x - 1, y + 1) == flag && chessBoard->getPoint(x - 1, y) == flag
			&& chessBoard->getPoint(x, y + 1) == flag){
				QString s;
				s.append(QString::number(flag));
				s.append(QString::number(1));
				s.append(QString::number(x - 1));
				s.append(QString::number(y));
				if (list->indexOf(s) == -1)
				{
					list->append(s);
					goal = goal + 1;
				}
		}
		if (chessBoard->getPoint(x + 1, y - 1) == flag && chessBoard->getPoint(x + 1, y) == flag
			&& chessBoard->getPoint(x, y - 1) == flag){
				QString s;
				s.append(QString::number(flag));
				s.append(QString::number(1));
				s.append(QString::number(x));
				s.append(QString::number(y - 1));
				if (list->indexOf(s) == -1)
				{
					list->append(s);
					goal = goal + 1;
				}
		}
		if (chessBoard->getPoint(x + 1, y + 1) == flag && chessBoard->getPoint(x + 1, y) == flag
			&& chessBoard->getPoint(x, y + 1) == flag){
				QString s;
				s.append(QString::number(flag));
				s.append(QString::number(1));
				s.append(QString::number(x));
				s.append(QString::number(y));
				if (list->indexOf(s) == -1)
				{
					list->append(s);
					goal = goal + 1;
				}
		}
		//三斜 1
		if (chessBoard->getToEdgeLength(x, y, flag, 2) == 3){
			//获得第一个点
			int pX = x;
			int pY = y;
			while (pX > 0)
			{
				pX--;
				pY++;
			}
			QString s;
			s.append(QString::number(flag));
			s.append(QString::number(2));
			s.append(QString::number(pX));
			s.append(QString::number(pY));
			if (list->indexOf(s) == -1)
			{
				list->append(s);
				goal = goal + 1;
			}
		}
		if (chessBoard->getToEdgeLength(x, y, flag, 3) == 3){
			//获得第一个点
			int pX = x;
			int pY = y;
			while (pX > 0 && pY > 0)
			{
				pX--;
				pY--;
			}
			QString s;
			s.append(QString::number(flag));
			s.append(QString::number(3));
			s.append(QString::number(pX));
			s.append(QString::number(pY));
			if (list->indexOf(s) == -1)
			{
				list->append(s);
				goal = goal + 1;
			}
		}
		//四斜 2 
		if (chessBoard->getToEdgeLength(x, y, flag, 2) == 4){
			//获得第一个点
			int pX = x;
			int pY = y;
			while (pX > 0)
			{
				pX--;
				pY++;
			}
			QString s;
			s.append(QString::number(flag));
			s.append(QString::number(4));
			s.append(QString::number(pX));
			s.append(QString::number(pY));
			if (list->indexOf(s) == -1)
			{
				list->append(s);
				goal = goal + 2;
			}
		}
		if (chessBoard->getToEdgeLength(x, y, flag, 3) == 4){
			//获得第一个点
			int pX = x;
			int pY = y;
			while (pX > 0 && pY > 0)
			{
				pX--;
				pY--;
			}
			QString s;
			s.append(QString::number(flag));
			s.append(QString::number(5));
			s.append(QString::number(pX));
			s.append(QString::number(pY));
			if (list->indexOf(s) == -1)
			{
				list->append(s);
				goal = goal + 2;
			}
		}
		//通天 3
		if (chessBoard->getToEdgeLength(x, y, flag, 2) == 5){
			//获得第一个点
			int pX = x;
			int pY = y;
			while (pX > 0)
			{
				pX--;
				pY++;
			}
			QString s;
			s.append(QString::number(flag));
			s.append(QString::number(6));
			s.append(QString::number(pX));
			s.append(QString::number(pY));
			if (list->indexOf(s) == -1)
			{
				list->append(s);
				goal = goal + 3;
			}
		}
		if (chessBoard->getToEdgeLength(x, y, flag, 3) == 5){
			//获得第一个点
			int pX = x;
			int pY = y;
			while (pX > 0 && pY > 0)
			{
				pX--;
				pY--;
			}
			QString s;
			s.append(QString::number(flag));
			s.append(QString::number(7));
			s.append(QString::number(pX));
			s.append(QString::number(pY));
			if (list->indexOf(s) == -1)
			{
				list->append(s);
				goal = goal + 3;
			}
		}
		//五虎 5
		if (chessBoard->getToEdgeLength(x, y, flag, 0) == 5){
			QString s;
			s.append(QString::number(flag));
			s.append(QString::number(8));
			s.append(QString::number(0));
			s.append(QString::number(y));
			if (list->indexOf(s) == -1)
			{
				list->append(s);
				goal = goal + 5;
			}
		}
		if (chessBoard->getToEdgeLength(x, y, flag, 1) == 5){
			QString s;
			s.append(QString::number(flag));
			s.append(QString::number(9));
			s.append(QString::number(x));
			s.append(QString::number(0));
			if (list->indexOf(s) == -1)
			{
				list->append(s);
				goal = goal + 5;
			}
		}		
		
		
		return goal;


	}
}

int GameLogic::run( QString &runStr )
{
	Step step(runStr);
	go(step);
	return result;
}

int GameLogic::getPlayerGoal(bool isFensive){
	if (isFensive)
	{
		return fensiveInfo->getGoal();
	}else{
		return defensiveInfo->getGoal();
	}
}

void GameLogic::judgePhase( FlagInfo* flagInfo, FlagInfo* otherFlagInfo )
{
	if(phase == DROP_PHASE){
		//已走满
		if (chessBoard->isFull()){
			if(flagInfo->getGoal() == 0){
				if(otherFlagInfo->getGoal() == 0){
					//没人赢
				}else{
					phase = PICK_PHASE;
					availableFlag = otherFlagInfo->getFlag();
				}
			}else{
				phase = PICK_PHASE;
				if (otherFlagInfo->getGoal() != 0)
				{
					availableFlag = otherFlagInfo->getFlag();
				}
			}
			dropFinished = true;
		}else{
			availableFlag = otherFlagInfo->getFlag();
		}
	}else if(phase == PICK_PHASE){
		if (flagInfo->getGoal() == 0){
			if (!chessBoard->CanMove(otherFlagInfo->getFlag()))
			{
				if (otherFlagInfo->getGoal() != 0)
				{
					availableFlag = otherFlagInfo->getFlag();
				}else{
					phase = MOVE_PHASE;
				}
			}else if (flagInfo->getFlag() == FENSIVE_FLAG){
				//先手
				phase = MOVE_PHASE;
				availableFlag = otherFlagInfo->getFlag();
			}else{
				//后手
				if (otherFlagInfo->getGoal() == 0){
					phase = MOVE_PHASE;
					if (startMove)
					{
						availableFlag = otherFlagInfo->getFlag();
					}
				}else{
					availableFlag = otherFlagInfo->getFlag();
				}
			}
		}
	}else{
		startMove = true;
		if (flagInfo->getGoal() == 0)
		{
			if (chessBoard->CanMove(otherFlagInfo->getFlag()))
			{
				availableFlag = otherFlagInfo->getFlag();
			}
		}else{
			phase = PICK_PHASE;
		}
	}

}

void GameLogic::judgeWin( FlagInfo* flagInfo, FlagInfo* otherFlagInfo )
{
	result = RESULT_UNKNOW_WIN;
	//如果是提子阶段或走子阶段，有一方没有子了
	if(phase == PICK_PHASE || phase == MOVE_PHASE){
		if (!chessBoard->containFlag(otherFlagInfo->getFlag())){
			//赢了
			if (flagInfo->getFlag() == FENSIVE_FLAG){
				result = RESULT_FENSIVE_WIN;
			}else{
				result = RESULT_DEFENSIVE_WIN;
			}
		}
	}else{
		//走棋阶段满了
		if (chessBoard->isFull())
		{
			result = RESULT_NOBODY_WIN;
		}
	}
}
