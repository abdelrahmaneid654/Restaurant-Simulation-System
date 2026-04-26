#include "RequestAction.h"

void RequestAction::setOrder(Order* o)
{
	pOrder = o;
}
RequestAction::RequestAction(Restaurant* r, Order* p) :Action(r)
{
}

void RequestAction::Act()
{

	// orderType pointer will be setted when reading from file, so we just need 
	// to send it to restaurant

	pRes->AddToPending(pOrder);


}
