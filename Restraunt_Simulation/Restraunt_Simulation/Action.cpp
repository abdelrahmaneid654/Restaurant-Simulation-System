#include"Action.h"
Action::Action(Restaurant* r)
{
	pRes = r;
}

void Action::setTimeStep(int t)
{
	timeStep = t;
}

int Action::getTimeStep()
{
	return timeStep;
}

