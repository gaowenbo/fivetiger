#pragma once
#include <qstring.h>
class Step
{
public:
	Step(void);
	Step(QString &stepStr);
	~Step(void);
	static const char DROP = 's';
	static const char MOVEUP = 'u';
	static const char MOVEDOWN = 'd';
	static const char MOVELEFT = 'l';
	static const char MOVERIGHT = 'r';	
	static const char PICK = 'p';

	int getFlag() const { return flag; }
	void setFlag(int val) { flag = val; }
	char getAction() const { return action; }
	void setAction(char val) { action = val; }
	int getPX() const { return pX; }
	void setPX(int val) { pX = val; }
	int getPY() const { return pY; }
	void setPY(int val) { pY = val; }
	bool isLegal();
	int getDestX();
	int getDestY();
	QString toString();
private:
	int flag;
	char action;
	int pX;
	int pY;
};

