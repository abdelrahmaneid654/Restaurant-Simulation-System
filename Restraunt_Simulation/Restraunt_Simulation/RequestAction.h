#pragma once
#include "Action.h"
class RequestAction : public Action
{
private:
	Order* pOrder;

public:
	RequestAction(Restaurant* r,Order* p);
	void Act();
	void setOrder(Order* o);

};


