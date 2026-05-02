#pragma once
#include "Action.h"
class CancelAction :public Action
{
private:
	int id;
public:
	CancelAction(Restaurant* r,ActionType t,int i);
	void Act();
	int getOrderID();
};


