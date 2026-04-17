#include "CancelAction.h"


CancelAction::CancelAction(Restaurant* r):Action(r)
{
}

void CancelAction::Act()
{
	// send this ID to reastaurant class fn that cancel order from OVC orders and send 
	// it to canceled list

	pRes->CancelOrder(pOrder->getID());

	
}

