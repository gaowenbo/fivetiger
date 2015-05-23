#include "Fivetiger.h"
#include <qpainter.h>
#include <qmessagebox.h>
#include "ScoreAIPlayer.h"
#include "MidLevelAIPlayer.h"

Fivetiger::Fivetiger(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	startChess = NULL;
	current = NULL;
	phrase = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			chessNode[i][j] = NULL;
		}
	}
	game = NULL;
	aiPlayer = NULL;
	currentPersonPlayer = NULL;
	mainPlayer = NULL;
	annexPlayer = NULL;
	wantToMove = NULL;
	isToComputer = false;
	gameIsOver = true;
}

Fivetiger::~Fivetiger()
{
	ChessNode* node = startChess;
	ChessNode* temp = node;
	while (node != NULL)
	{
		temp = node;
		node = node->next;
		delete temp;
	}
	if (game == NULL)
	{
	}
	delete game;
	if (mainPlayer == NULL)
	{
		delete mainPlayer;
	}
	if (annexPlayer == NULL)
	{
		delete annexPlayer;
	}
	if (aiPlayer == NULL)
	{
		delete aiPlayer;
	}
	if (wantToMove != NULL)
	{
		delete wantToMove;
	}
}

void Fivetiger::paintEvent( QPaintEvent *event )
{
	QPainter painter(this);
	painter.setPen(Qt::SolidLine);
	//QPoint ptStart;
	//QPoint ptEnd;
	//横线
	for(int i = 0; i < 5; i++){
		//ptStart.setX(N1);
		//ptStart.setY(N2);
		//ptEnd.setX(N1);
		//ptEnd.setY(N2);
		painter.drawLine(P_STARTX, P_STARTY + C_DISTANCE * i, P_STARTX + C_DISTANCE * 4, 
			P_STARTY + C_DISTANCE * i );
	}
	//竖线
	for(int i = 0; i < 5; i++){
		painter.drawLine(P_STARTX + C_DISTANCE * i, P_STARTY, P_STARTX + C_DISTANCE * i, 
			P_STARTY + C_DISTANCE*4);
	}

	drawChessman();
	drawWantToMove();
}

void Fivetiger::drawChessman()
{
	QPainter painter(this);
	ChessNode* chessNode = startChess;
	while(chessNode != NULL){
		painter.setBrush(chessNode->color);
		painter.drawEllipse(QPoint(chessNode->x, chessNode->y), C_SIZE, C_SIZE);
		chessNode = chessNode->next;
	}
}

void Fivetiger::drawWantToMove()
{
	if (wantToMove == NULL)
	{
		return;
	}
	QPainter painter(this);
	if(wantToMove != NULL){
		painter.setBrush(Qt::red);
		painter.drawEllipse(QPoint(wantToMove->x(), wantToMove->y()), 3, 3);
	}
}


void Fivetiger::mousePressEvent(QMouseEvent *event)
{
	if (gameIsOver || currentPersonPlayer == NULL)
	{
		return;
	}
	int indexX = getSquares(P_STARTX, C_DISTANCE, event->x());
	int indexY = getSquares(P_STARTY, C_DISTANCE, event->y());
	if (indexX < 0 || indexX > 4 || indexY < 0 || indexY > 4)
	{
		return;
	}
	ui.lblInfo->setText(QString(""));
	int phrase = game->getPhase();
	if (phrase == DROP_PHASE )
	{
		currentPersonPlayer->dropChess(indexX, indexY);
	}else if (phrase == MOVE_PHASE)
	{
		if (!currentPersonPlayer->getDragState())
		{
			currentPersonPlayer->startMoveChess(indexX, indexY);
			if (wantToMove == NULL)
			{
				wantToMove = new QPoint(P_STARTX + (C_DISTANCE * indexX), P_STARTY + (C_DISTANCE * indexY));
				repaint();
			}
		}
		else{
			if (wantToMove != NULL)
			{
				delete wantToMove;
				wantToMove = NULL;
			}
			currentPersonPlayer->endMoveChess(indexX, indexY);
		}
	}
	else{
		currentPersonPlayer->pickChess(indexX, indexY);
	}
	if (isToComputer && aiPlayer != NULL && !gameIsOver && currentPersonPlayer == NULL)
	{
		aiPlayer->Go();
	}
}

inline int Fivetiger::getSquares( int start, int distance, int value )
{
	return (2 * value - 2 * start + distance)/(2 * distance);
}

void Fivetiger::updateDropChess( int flag, int x, int y )
{
	// 更新界面信息
	ChessNode* temp = new ChessNode;
	temp->x = P_STARTX + (C_DISTANCE * x);
	temp->y = P_STARTY + (C_DISTANCE * y);
	temp->next = NULL;
	temp->last = current;
	if(flag == FENSIVE_FLAG){
		temp->color = Qt::black;
	}else{
		temp->color = Qt::white;
	}
	chessNode[x][y] = temp;
	if(startChess == NULL){
		startChess = temp;
		current = temp;
	}else{
		current->next = temp;
		current = temp;
	}
	updateInfo();
	repaint();
}

void Fivetiger::updateMoveChess( int flag, int startX, int startY, int endX, int endY )
{
	ChessNode* node = chessNode[startX][startY];
	node->x = P_STARTX + (C_DISTANCE * endX); 
	node->y = P_STARTY + (C_DISTANCE * endY);
	chessNode[endX][endY] = node;
	chessNode[startX][startY] = NULL;
	updateInfo();
	repaint();
}

void Fivetiger::updatePickChess( int flag, int x, int y )
{
	ChessNode* node = chessNode[x][y];
	if(node == NULL){
		return;
	}
	if (node == startChess)
	{
		startChess = node->next;
	}
	ChessNode* last = node->last;
	if (last != NULL)
	{
		last->next = node->next;
	}
	ChessNode* next = node->next;
	if (next != NULL)
	{
		next->last = node->last;
	}
	chessNode[x][y] = NULL;
	delete node;
	updateInfo();
	repaint();
}

void Fivetiger::updateInfo()
{
	ui.lblFGoal->setText(QString::number(game->getPlayerGoal(true)));
	ui.lblDGoal->setText(QString::number(game->getPlayerGoal(false)));
	if (game->getAvailableFlag() == FENSIVE_FLAG)
	{
		ui.lblcurrentFlag->setText(QStringLiteral("先手方"));
	}else{
		ui.lblcurrentFlag->setText(QStringLiteral("后手方"));
	}
	if (game->getPhase() == DROP_PHASE)
	{
		ui.lblPhrase->setText(QStringLiteral("落子"));
	}else if (game->getPhase() == MOVE_PHASE)
	{
		ui.lblPhrase->setText(QStringLiteral("走子"));
	}else{
		ui.lblPhrase->setText(QStringLiteral("提子"));
	}

	ui.lblInfo->setText(QString::fromUtf8(""));
}

void Fivetiger::changePlayer( int flag )
{
	if (mainPlayer->getFlag() == flag)
	{
		currentPersonPlayer = mainPlayer;
	}else if (!isToComputer)
	{
		currentPersonPlayer = annexPlayer;
	}else{
		currentPersonPlayer = NULL;
	}
}

void Fivetiger::showResult( int result, bool isOver )
{
	gameIsOver = isOver;
	if (isToComputer)
	{
		switch(result){
		case RESULT_FENSIVE_WIN:
			QMessageBox::about(this, QStringLiteral("结果"), QStringLiteral("您赢了！"));
			break;
		case RESULT_DEFENSIVE_WIN:
			QMessageBox::about(this, QStringLiteral("结果"), QStringLiteral("您输了！"));;
			break;
		case RESULT_NOBODY_WIN:
			QMessageBox::about(this, QStringLiteral("结果"), QStringLiteral("平局！"));
			break;
		case RESULT_UNKNOW_WIN:
			ui.lblInfo->setText(QString::fromUtf8(""));
			break;
		default:
			ui.lblInfo->setText(QStringLiteral("走棋错误!"));
		}
	}else{
		switch(result){
		case RESULT_FENSIVE_WIN:
			QMessageBox::about(this, QStringLiteral("结果"), QStringLiteral("先手胜！"));
			break;
		case RESULT_DEFENSIVE_WIN:
			QMessageBox::about(this, QStringLiteral("结果"), QStringLiteral("后手胜！"));
			break;
		case RESULT_NOBODY_WIN:
			QMessageBox::about(this, QStringLiteral("结果"), QStringLiteral("平局！"));
			break;
		case RESULT_UNKNOW_WIN:
			ui.lblInfo->setText(QString::fromUtf8(""));
			break;
		default:
			ui.lblInfo->setText(QStringLiteral("走棋错误!"));
		}
	}
}

void Fivetiger::startToEasyClick()
{
	destroyOldGame();

	game = new GameLogic;
	game->start();
	mainPlayer = new PersonPlayer(game, true);
	mainPlayer->setObserver(this);
	annexPlayer = NULL;
	aiPlayer = new ScoreAIPlayer(game, false);
	aiPlayer->setObserver(this);
	currentPersonPlayer = mainPlayer;
	gameIsOver = false;
	isToComputer = true;
	
	//清空棋盘
	ChessNode* node = startChess;
	ChessNode* temp = node;
	while (node != NULL)
	{
		temp = node;
		node = node->next;
		delete temp;
	}
	startChess = NULL;
	current = NULL;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			chessNode[i][j] = NULL;
		}
	}
	updateInfo();
	repaint();
}

void Fivetiger::startToSelfClick()
{
	destroyOldGame();
	game = new GameLogic;
	game->start();
	mainPlayer = new PersonPlayer(game, true);
	mainPlayer->setObserver(this);
	aiPlayer = NULL;
	annexPlayer = new PersonPlayer(game, false);
	annexPlayer->setObserver(this);
	currentPersonPlayer = mainPlayer;
	gameIsOver = false;
	isToComputer = false;

	//清空棋盘
	ChessNode* node = startChess;
	ChessNode* temp = node;
	while (node != NULL)
	{
		temp = node;
		node = node->next;
		delete temp;
	}
	startChess = NULL;
	current = NULL;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			chessNode[i][j] = NULL;
		}
	}
	updateInfo();
	repaint();
}

void Fivetiger::destroyOldGame()
{
	if (game != NULL)
	{
		delete game;
	}
	if (mainPlayer != NULL)
	{
		delete mainPlayer;
	}
	if (annexPlayer != NULL)
	{
		delete annexPlayer;
	}
	if (aiPlayer != NULL)
	{
		delete aiPlayer;
	}
}

void Fivetiger::helpClick()
{
	QMessageBox::about(this, QStringLiteral("帮助"), QStringLiteral("五虎棋，棋盘是横5条、纵5条直线垂直交叉成16个方格，两个人在交叉点上轮流布子。目的是把棋子排成小斗、三斜、四斜、通天、五虎等阵型,并阻止对方排成阵型，成功排成一个阵型就可以提掉对方一个棋子。棋盘全部摆满以后看双方各排成多少阵型，开始提子。后手棋者先提，先手棋者后提，然后后手棋者在空当处先走棋。走棋的目的也是排成上述阵型，成一个就马上提对方一个棋子，直到把对方的棋子全部提完为止。注意：移动棋子时，一个阵型中的棋子在自己的位置上，不可以通过进一步再退一步（再回到原来位置）的方法重复排成同一个阵型。"));
}

void Fivetiger::startToMidClick()
{
	destroyOldGame();

	game = new GameLogic;
	game->start();
	mainPlayer = new PersonPlayer(game, true);
	mainPlayer->setObserver(this);
	annexPlayer = NULL;
	aiPlayer = new MidLevelAIPlayer(game, false);
	aiPlayer->setObserver(this);
	currentPersonPlayer = mainPlayer;
	gameIsOver = false;
	isToComputer = true;

	//清空棋盘
	ChessNode* node = startChess;
	ChessNode* temp = node;
	while (node != NULL)
	{
		temp = node;
		node = node->next;
		delete temp;
	}
	startChess = NULL;
	current = NULL;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			chessNode[i][j] = NULL;
		}
	}
	updateInfo();
	repaint();
}

