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
	//����
	for(int i = 0; i < 5; i++){
		//ptStart.setX(N1);
		//ptStart.setY(N2);
		//ptEnd.setX(N1);
		//ptEnd.setY(N2);
		painter.drawLine(P_STARTX, P_STARTY + C_DISTANCE * i, P_STARTX + C_DISTANCE * 4, 
			P_STARTY + C_DISTANCE * i );
	}
	//����
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
	// ���½�����Ϣ
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
		ui.lblcurrentFlag->setText(QStringLiteral("���ַ�"));
	}else{
		ui.lblcurrentFlag->setText(QStringLiteral("���ַ�"));
	}
	if (game->getPhase() == DROP_PHASE)
	{
		ui.lblPhrase->setText(QStringLiteral("����"));
	}else if (game->getPhase() == MOVE_PHASE)
	{
		ui.lblPhrase->setText(QStringLiteral("����"));
	}else{
		ui.lblPhrase->setText(QStringLiteral("����"));
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
			QMessageBox::about(this, QStringLiteral("���"), QStringLiteral("��Ӯ�ˣ�"));
			break;
		case RESULT_DEFENSIVE_WIN:
			QMessageBox::about(this, QStringLiteral("���"), QStringLiteral("�����ˣ�"));;
			break;
		case RESULT_NOBODY_WIN:
			QMessageBox::about(this, QStringLiteral("���"), QStringLiteral("ƽ�֣�"));
			break;
		case RESULT_UNKNOW_WIN:
			ui.lblInfo->setText(QString::fromUtf8(""));
			break;
		default:
			ui.lblInfo->setText(QStringLiteral("�������!"));
		}
	}else{
		switch(result){
		case RESULT_FENSIVE_WIN:
			QMessageBox::about(this, QStringLiteral("���"), QStringLiteral("����ʤ��"));
			break;
		case RESULT_DEFENSIVE_WIN:
			QMessageBox::about(this, QStringLiteral("���"), QStringLiteral("����ʤ��"));
			break;
		case RESULT_NOBODY_WIN:
			QMessageBox::about(this, QStringLiteral("���"), QStringLiteral("ƽ�֣�"));
			break;
		case RESULT_UNKNOW_WIN:
			ui.lblInfo->setText(QString::fromUtf8(""));
			break;
		default:
			ui.lblInfo->setText(QStringLiteral("�������!"));
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
	
	//�������
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

	//�������
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
	QMessageBox::about(this, QStringLiteral("����"), QStringLiteral("�廢�壬�����Ǻ�5������5��ֱ�ߴ�ֱ�����16�������������ڽ�������������ӡ�Ŀ���ǰ������ų�С������б����б��ͨ�졢�廢������,����ֹ�Է��ų����ͣ��ɹ��ų�һ�����;Ϳ�������Է�һ�����ӡ�����ȫ�������Ժ�˫�����ųɶ������ͣ���ʼ���ӡ������������ᣬ�������ߺ��ᣬȻ����������ڿյ��������塣�����Ŀ��Ҳ���ų��������ͣ���һ����������Է�һ�����ӣ�ֱ���ѶԷ�������ȫ������Ϊֹ��ע�⣺�ƶ�����ʱ��һ�������е��������Լ���λ���ϣ�������ͨ����һ������һ�����ٻص�ԭ��λ�ã��ķ����ظ��ų�ͬһ�����͡�"));
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

	//�������
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

