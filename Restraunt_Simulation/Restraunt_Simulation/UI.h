#pragma once
#include"Queue.h"
#include"PriQueue.h"
#include"Stack.h"
#include"Action.h"
#include"Order.h"
#include"Pending_OVC.h"
#include"Fit_Tables.h"
#include"RDY_OV.h"
#include"Cooking_Orders.h"

#include"EnumTypes.h"

#include"Restaurant.h"
class Action;
class Restaurant;
class UI
{
private:
	Restaurant* pRes; // to set program mode in restaurant
public:
	UI(Restaurant* p);

	void Print(const Queue<Action*>& ActionListR, const Queue<Action*> &ActionListC,
		const Queue<Order*> &Pend_ODG, const Queue<Order*> &Pend_ODN, const Queue<Order*> &Pend_OT, const Queue<Order*> &Pend_OVN,
		const Pending_OVC<Order*> &Pend_OVC, const Queue<Order*> &Pend_OVG, const Queue<Order*> &Ready_OT, const Queue<Order*>& Ready_OD,
		const RDY_OV<Order*> &Ready_OV, const Cooking_Orders<Order*> &Cooking_orders, const Queue<Order*> &Cancelled_Orders,
		const Stack<Order*> &Finished_Orders, const PriQueue<Order*> &InServ, const PriQueue<Order*> &Compo,
		const Queue<Chef*> &Free_CS, const Queue<Chef*>& Free_CN, const PriQueue<Scooter*> &Free_Scooters,
		const Queue<Scooter*> &Maint_Scooters, const PriQueue<Scooter*> &Busy_Scooters, const Fit_Tables &Free_Tables,
		const Fit_Tables &Busy_Sharable, const Fit_Tables &Busy_No_Share);

	void chooseMode();

	void setProgramMode(Mode m);

	void WaitForClick();

};
