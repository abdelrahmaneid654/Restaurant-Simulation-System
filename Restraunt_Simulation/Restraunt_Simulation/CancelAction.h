#pragma once
#include "Action.h"
class CancelAction :public Action
{
private:
	// orderType here is just an order that holds order ID that need to be cancelled
public:
	CancelAction(Restaurant* r);
	void Act();
};

