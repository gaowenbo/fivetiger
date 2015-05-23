#include "Step.h"

Step::~Step(void)
{
}

Step::Step(void){
	Step(QString(""));
}

Step::Step( QString &stepStr )
{
	flag = -1;
	action = 0;
	pX = -1;
	pY = -1;

	if (stepStr == ""){
		return;
	}
	if (stepStr.length() != 4){
		return;
	}
	flag = stepStr.at(0).digitValue();

	setAction(stepStr.at(1).unicode());	
	pX = stepStr.at(2).digitValue();
	pY = stepStr.at(3).digitValue();
}

int Step::getDestX()
{
	if (action == MOVELEFT)
	{
		return pX - 1;
	}
	else if (action == MOVERIGHT)
	{
		return pX + 1;
	}
	else{
		return pX;
	}
}

int Step::getDestY()
{
	if (action == MOVEDOWN)
	{
		return pY + 1;
	}
	else if (action == MOVEUP)
	{
		return pY - 1;
	}
	else{
		return pY;
	}
}

QString Step::toString()
{
	QString s;
	s.append(QString::number(flag));
	s.append(getAction());
	s.append(QString::number(pX));
	s.append(QString::number(pY));
	return s;
}

bool Step::isLegal()
{
	return flag != -1 && action != 0 && pX != -1 && pY != -1;
}
