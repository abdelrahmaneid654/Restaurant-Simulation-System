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

CancelAction::CancelAction(Restaurant* r) :Action(r)
{
}

void CancelAction::Act()
{
	// send this ID to reastaurant class fn that cancel order from OVC orders and send 
	// it to canceled list

	pRes->CancelOrder(pOrder->getID());
}
