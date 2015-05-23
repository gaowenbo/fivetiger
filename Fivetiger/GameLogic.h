#pragma once
#include "FlagInfo.h"
#include "ChessBoard.h"
#include "Step.h"
#include <QString>
#include <qstringlist.h>
#include "ChessGlobal.h"

struct StepNode {
	Step s;
	int goalIndex[5];
	int goallength;
	struct StepNode* last;
	struct StepNode* next;
};

class GameLogic
{
public:
	GameLogic(void);
	GameLogic(const GameLogic& gameLogic);
	~GameLogic(void);

	int getAvailableFlag() const { return availableFlag; }
	ChessBoard* getChessBoard() const { return chessBoard; }
	int getDropFinished() const { return dropFinished; }
	int getResult() const { return result; }
	int getPhase() const { return phase; }
	void start();
	int run(QString &runStr);
	int getPlayerGoal(bool isFensive);
	void moveOnBoard( Step & step );
	int calculateGoal(Step & step );
private:
	FlagInfo* fensiveInfo;
	FlagInfo* defensiveInfo;	
	int availableFlag;
	ChessBoard* chessBoard;
	QStringList* list;
	int phase;
	int dropFinished;
	int result;
	bool startMove;
	void go(Step &step);
	bool allowMove( Step & step );
	void updateInfo( Step & step );
	void judgePhase( FlagInfo* flagInfo, FlagInfo* otherFlagInfo );
	void judgeWin( FlagInfo* flagInfo, FlagInfo* otherFlagInfo );
};

