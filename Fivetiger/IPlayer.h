#pragma once
#include "qstring.h"

class IPlayer
{
public:
	virtual int run(QString &stepStr) = 0;
	virtual ~IPlayer(void){}
};

