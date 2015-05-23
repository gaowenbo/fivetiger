#include "ChessBoard.h"


ChessBoard::ChessBoard(void)
{
	//初始化
	for(int i=0;i<BOARD_LENGTH;i++){
		for(int j=0;j<BOARD_LENGTH;j++){
			board[i][j] = 0;
		}
	}
	
}

ChessBoard::ChessBoard( const ChessBoard& chessBoard )
{
	//初始化
	for(int i=0;i<BOARD_LENGTH;i++){
		for(int j=0;j<BOARD_LENGTH;j++){
			board[i][j] = chessBoard.board[i][j];
		}
	}
}


ChessBoard::~ChessBoard(void)
{
	//for(int i=0;i<BOARD_LENGTH;i++){
	//	delete board[i];
	//}
	//delete board;
}

int ChessBoard::getPoint( int x, int y )
{
	if(x >= BOARD_LENGTH || x < 0){
		return -1;
	}
	if(y >= BOARD_LENGTH || y < 0){
		return -1;
	}
	return board[x][y];
}

void ChessBoard::setPoint( int x, int y, int flag )
{
	if(x >= BOARD_LENGTH || x < 0){
		return;
	}
	if(y >= BOARD_LENGTH || y < 0){
		return;
	}
	board[x][y] = flag;
}

bool ChessBoard::containFlag( int flag )
{
	bool isContained = false;
	for(int i=0;i<BOARD_LENGTH;i++){
		for(int j=0;j<BOARD_LENGTH;j++){
			if (board[i][j] == flag){
				isContained = true;
			}
		}
	}
	return isContained;
}

bool ChessBoard::isFull()
{
	return !containFlag(0);
}

int ChessBoard::getToEdgeLength( int x, int y, int flag, int type )
{
	int length = 1;
	int pX = x;
	int pY = y;
	//横
	if (type == 0){
		pX--;
		while(pX >= 0){
		
			if(getPoint(pX, pY) == flag){
				length++;
			}else{
				return 0;
			}
			pX--;
		}
		pX = x;
		pX++;
		while(pX < 5){
			
			if(getPoint(pX, pY) == flag){
				length++;
			}else{
				return 0;
			}
			pX++;
		}
	}
	//竖
	else if (type == 1){
		pY--;
		while(pY >= 0){
			if(getPoint(pX, pY) == flag){
				length++;
			}else{
				return 0;
			}
			pY--;
		}
		pY = y;
		pY++;
		while(pY < 5){
			if(getPoint(pX, pY) == flag){
				length++;
			}else if(getPoint(pX, pY) == 0){
				return 0;
			}
			pY++;
		}
	}		
	//撇
	else if (type == 2){
		pY--;
		pX++;
		while(pY >= 0 && pX < 5){
			if(getPoint(pX, pY) == flag){
				length++;
			}else{
				return 0;
			}
			pY--;
			pX++;
		}
		pX = x;
		pY = y;
		pY++;
		pX--;
		while(pY < 5 && pX >=0){
			if(getPoint(pX, pY) == flag){
				length++;
			}else{
				return 0;
			}
			pY++;
			pX--;
		}
	}
	//捺
	else if (type == 3){
		pY++;
		pX++;
		while(pY < 5 && pX < 5){
			if(getPoint(pX, pY) == flag){
				length++;
			}else{
				return 0;
			}
			pY++;
			pX++;
		}
		pX = x;
		pY = y;
		pY--;
		pX--;
		while(pY >= 0 && pX >=0){

			if(getPoint(pX, pY) == flag){
				length++;
			}else{
				return 0;
			}
			pY--;
			pX--;
		}
	}
	return length;
}

bool ChessBoard::CanMove( int flag )
{
	for (int i = 0; i < BOARD_LENGTH; i++)
	{
		for (int j = 0; j < BOARD_LENGTH; j++)
		{
			
			if (CanPointMove(i, j, flag))
			{
				return true;
			}
		}
	}
	return false;
}

bool ChessBoard::CanPointMove( int i, int j, int flag )
{
	if (getPoint(i,j) != flag)
	{
		return false;
	}

	if (getPoint(i + 1,j) != 0 && 
		getPoint(i,j + 1) != 0 && 
		getPoint(i - 1,j) != 0 && 
		getPoint(i,j - 1) != 0)
	{
		return false;
	}
	return true;
}

int ChessBoard::GetChessCount()
{
	int count = 0;
	for(int i=0;i<BOARD_LENGTH;i++){
		for(int j=0;j<BOARD_LENGTH;j++){
			if (board[i][j] != 0){
				count++;
			}
		}
	}
	return count;
}
