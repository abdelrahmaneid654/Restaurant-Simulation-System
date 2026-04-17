#include "CancelAction.h"


CancelAction::CancelAction(Restaurant* r):Action(r)
{
}

bool CancelAction::Act()
{
	// send this ID to reastaurant class fn that cancel order from OVC orders and send 
	// it to canceled list

	return pRes->CancelOrder(pOrder->getID());

	
}

