#include "RequestAction.h"

RequestAction::RequestAction(Restaurant* r):Action(r)
{
}

void RequestAction::Act()
{

	// orderType pointer will be setted when reading from file, so we just need 
	// to send it to restaurant

	pRes->AddToPending(pOrder);
	

}

