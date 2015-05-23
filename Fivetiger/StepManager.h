#pragma once
#include "Step.h"
struct StepNode{
	Step step;
	int scoalIndex[5];
	int scoalLenth;
	struct StepNode* last;
	struct StepNode* next;
};

class StepManager
{
public:
	StepManager(void);
	~StepManager(void);
	StepNode* currentStepNode;
	void addStep(Step& step);
	void deleteLastStep();
	void addGoalIndex(const int index);
};

