#include "RequestAction.h"

RequestAction::RequestAction(Restaurant* r, ActionType t,Order* p) :Action(r,t)
{
	pOrder = p;
}

void RequestAction::Act()
{

	// orderType pointer will be setted when reading from file, so we just need 
	// to send it to restaurant

	pRes->AddToPending(pOrder);


}
