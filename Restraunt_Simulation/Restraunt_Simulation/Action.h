#pragma once
#include"Order.h"
#include "Restaurant.h" 
class Restaurant;
class Action
{
protected:
	int timeStep;
	Restaurant* pRes;  
public:
	Action(Restaurant* r); 
	virtual void Act() = 0;
	void setTimeStep(int t);
	int getTimeStep();
};

