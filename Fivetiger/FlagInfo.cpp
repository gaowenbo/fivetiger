#include "FlagInfo.h"


FlagInfo::FlagInfo(void)
{
	goal = 0;
	flag = 1;
	isOnTheOffensive = false;
}

FlagInfo::FlagInfo( const FlagInfo& info )
{
	flag = info.flag;
	goal = info.goal;
	isOnTheOffensive = info.isOnTheOffensive;
}


FlagInfo::~FlagInfo(void)
{

}
