#ifndef FIVETIGER_H
#define FIVETIGER_H

#include <QtWidgets/QMainWindow>
#include <qevent.h>
#include "ui_Fivetiger.h"
#include "GameLogic.h"
#include "personPlayer.h"
#include "AIPlayer.h"
#include "GoChessObserver.h"
#include "qpoint.h"

struct ChessNode{
	int x;
	int y;
	Qt::GlobalColor color;
	struct ChessNode* next;
	struct ChessNode* last;
};

const int P_STARTX = 100;
const int P_STARTY = 100;
const int C_DISTANCE = 100;
const int C_SIZE = 35;

class Fivetiger : public QMainWindow, public GoChessObserver
{
	Q_OBJECT

public:
	Fivetiger(QWidget *parent = 0);
	~Fivetiger();
	void paintEvent(QPaintEvent *event);
	void drawChessman();
	void drawWantToMove();
	void updateDropChess(int flag, int x, int y);
	void updateMoveChess(int flag, int startX, int startY, int endX, int endY);
	void updatePickChess(int flag, int x, int y);
	void changePlayer(int flag);
	void showResult(int result, bool isOver);
protected:
	void mousePressEvent(QMouseEvent *event);
	inline int getSquares( int start, int distance, int value );
	PersonPlayer* getCurrentPlayer();
	void updateInfo();
private:
	Ui::FivetigerClass ui;
	ChessNode* chessNode[5][5];
	ChessNode* startChess;
	ChessNode* current;
	QPoint* wantToMove;
	GameLogic* game;
	int phrase;
	PersonPlayer* mainPlayer;
	PersonPlayer* annexPlayer;
	AIPlayer* aiPlayer;
	PersonPlayer* currentPersonPlayer;
	bool isToComputer;
	bool gameIsOver;
	void destroyOldGame(); 
private slots:
	void startToEasyClick();
	void startToMidClick();
	void startToSelfClick();
	void helpClick();
};



#endif // FIVETIGER_H
