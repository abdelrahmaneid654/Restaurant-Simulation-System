#include "Action.h"
#include<iostream>
using namespace std;

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

void Action::setOrderType(Order* o)
{
	pOrder = o;
}

