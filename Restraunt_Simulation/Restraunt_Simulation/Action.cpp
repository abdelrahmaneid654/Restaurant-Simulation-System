#include"Action.h"
#include"RequestAction.h"
#include"CancelAction.h"

Action::Action(Restaurant* r, ActionType t)
{
	pRes = r;
	type = t;
}

void Action::setTimeStep(int t)
{
	timeStep = t;
}

int Action::getTimeStep()
{
	return timeStep;
}

ActionType Action::gettype()
{
	return type;
}

ostream& operator<<(ostream& o, Action*p)
{
	if (p->gettype() == Q)
	{
		RequestAction* req = ((RequestAction*)p);
		OrderType t = req->getOrder()->gettype();

		o << "[ ";
		switch (t)
		{
		case ODG:
			o << "ODG, ";
			break;
		case ODN:
			o << "ODN, ";
			break;
		case OVG:
			o << "OVG, ";
			break;
		case OVC:
			o << "OVC, ";
			break;
		case OVN:
			o << "OVN, ";
			break;
		case OT_O:
			o << "OT, ";
			break;
		}
		
		o << p->getTimeStep() << ", " << req->getOrder()->getID() << " ] ";
	}
	else if (p->gettype() == X)
	{
		CancelAction* canc = ((CancelAction*)p);
		o << "( X, " << p->getTimeStep() << ", " << canc->getOrderID() << " )";
	}
	return o;
}
