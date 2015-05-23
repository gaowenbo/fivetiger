#include "StepManager.h"


StepManager::StepManager(void)
{
	currentStepNode = NULL;
}


StepManager::~StepManager(void)
{
	while(currentStepNode != NULL){
		StepNode* tempNode = currentStepNode;
		currentStepNode = currentStepNode->last;
		delete tempNode;
	}
}

void StepManager::addStep(Step& step){

}


void StepManager::deleteLastStep(){

}

void StepManager::addGoalIndex(const int index){

}