#include "CancelAction.h"


CancelAction::CancelAction(Restaurant* r,ActionType t, int i) :Action(r,t)
{
	id = i;
}

void CancelAction::Act()
{
	// send this ID to reastaurant class fn that cancel order from OVC orders and send 
	// it to canceled list
	pRes->CancelOrder(id);
}

int CancelAction::getOrderID()
{
	return id; 
}
