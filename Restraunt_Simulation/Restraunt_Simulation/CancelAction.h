#pragma once
#include "Action.h"
class CancelAction :public Action
{
private:
	int id;
public:
	CancelAction(Restaurant* r,int i);
	void Act();
};


CancelAction::CancelAction(Restaurant* r,int i) :Action(r)
{
	id = i;
}

void CancelAction::Act()
{
	// send this ID to reastaurant class fn that cancel order from OVC orders and send 
	// it to canceled list

	pRes->CancelOrder(id);
}
