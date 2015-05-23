#pragma once
class ChessBoard
{

public:
	ChessBoard(void);
	ChessBoard(const ChessBoard& chessBoard);
	~ChessBoard(void);
	static const int BOARD_LENGTH = 5;
	int getPoint(int x, int y);
	void setPoint(int x, int y, int flag);
	bool containFlag(int flag);
	bool isFull();
	int getToEdgeLength(int x, int y, int flag, int type);
	bool CanMove( int flag );
	bool CanPointMove( int i, int j, int flag );
	int GetChessCount();
private:
	int board[BOARD_LENGTH][BOARD_LENGTH];
};

