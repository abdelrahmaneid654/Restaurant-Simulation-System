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

void Action::setOrder(Order* o)
{
	pOrder = o;
}