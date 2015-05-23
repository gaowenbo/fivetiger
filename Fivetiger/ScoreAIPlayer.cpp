#include "ScoreAIPlayer.h"
#include<time.h>


ScoreAIPlayer::ScoreAIPlayer(void)
{
}

ScoreAIPlayer::ScoreAIPlayer( GameLogic* logic, bool isFensive /*= false*/ ):AIPlayer(logic, isFensive)
{
}


ScoreAIPlayer::~ScoreAIPlayer(void)
{
}

int ScoreAIPlayer::getDropScore( Step & step )
{
	GameLogic* tempLogic = new GameLogic(*logic);
	tempLogic->moveOnBoard(step);
	int goal = tempLogic->calculateGoal(step) * 1000;
	if(goal == 0){
		if (step.getDestX() == 0 && step.getDestY() == 2)
		{
			goal += 10;
		}else if(step.getDestX() == 2 && step.getDestY() == 0){
			goal += 10;
		}else if (step.getDestX() == 4 && step.getDestY() == 2)
		{
			goal += 10;
		}else if (step.getDestX() == 2 && step.getDestY() == 4)
		{
			goal += 10;
		}
	}

	Step s;
	s.setFlag(getOtherFlag());
	s.setAction('s');
	s.setPX(step.getDestX());
	s.setPY(step.getDestY());
	tempLogic->moveOnBoard(s);
	int dropOtherGoal = tempLogic->calculateGoal(s) * 900;
	goal += dropOtherGoal;

	delete tempLogic;
	return goal + rand()%10;
}

int ScoreAIPlayer::getPickScore( Step& step )
{
	return rand()%1000;
}

int ScoreAIPlayer::getMoveScore( Step& step )
{
	GameLogic* tempLogic = new GameLogic(*logic);
	tempLogic->moveOnBoard(step);
	int goal = tempLogic->calculateGoal(step) * 1000;
	Step s;
	s.setFlag(getOtherFlag());
	s.setAction('s');
	s.setPX(step.getDestX());
	s.setPY(step.getDestY());
	tempLogic->moveOnBoard(s);
	int dropOtherGoal = tempLogic->calculateGoal(s) * 900;
	goal += dropOtherGoal;
	s.setPX(step.getPX());
	s.setPY(step.getPY());
	tempLogic->moveOnBoard(s);
	int leaveGoal = tempLogic->calculateGoal(s) *(-800);
	goal += leaveGoal;

	delete tempLogic;
	return goal + rand()%10;
}
