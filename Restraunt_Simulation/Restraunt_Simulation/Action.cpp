#include"Action.h"
Action::Action(Restaurant* r,ActionType t)
{
	pRes = r;
	type = t;
}

void Action::setTimeStep(int t)
{
	timeStep = t;
}

int Action::getTimeStep()
{
	return timeStep;
}

