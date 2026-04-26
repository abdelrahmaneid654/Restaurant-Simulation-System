#pragma once
#include "Action.h"
class RequestAction : public Action
{
private:
	Order* pOrder;

public:
	RequestAction(Restaurant* r);
	void Act();
	void setOrder(Order* o);

};

void RequestAction::setOrder(Order* o)
{
	pOrder = o;
}
RequestAction::RequestAction(Restaurant* r) :Action(r)
{
}

void RequestAction::Act()
{

	// orderType pointer will be setted when reading from file, so we just need 
	// to send it to restaurant

	pRes->AddToPending(pOrder);


}


