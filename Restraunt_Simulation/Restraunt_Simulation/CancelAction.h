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


