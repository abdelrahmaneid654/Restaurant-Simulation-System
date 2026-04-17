#pragma once
#include "Action.h"
class RequestAction : public Action
{
private:

public:
	RequestAction(Restaurant* r);
	void Act();
};

