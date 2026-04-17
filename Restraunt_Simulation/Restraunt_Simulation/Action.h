#pragma once
#include"Order.h"
#include "Restaurant.h" 

class Action
{
protected:
	Order* pOrder;
	int timeStep;
	Restaurant* pRes;  
public:
	Action(Restaurant* r); 
	virtual bool Act() = 0;
	void setTimeStep(int t);
	int getTimeStep();
	void setOrderType(Order* o);
};

