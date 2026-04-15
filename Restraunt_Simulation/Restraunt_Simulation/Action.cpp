#include "Action.h"
#include<iostream>
using namespace std;

Action::Action()
{
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
	orderType = o;
}

