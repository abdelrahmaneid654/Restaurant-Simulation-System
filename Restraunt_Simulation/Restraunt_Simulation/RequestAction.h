#pragma once
#include "Action.h"
class RequestAction : public Action
{
private:
	Order* pOrder;
public:
	RequestAction(Restaurant* r,ActionType t,Order* p);
	void Act();

};


