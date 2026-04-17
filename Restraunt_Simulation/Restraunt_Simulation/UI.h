#pragma once
#include"Queue.h"
#include"PriQueue.h"
#include"Stack.h"
#include"Action.h"
#include"Order.h"
#include"Pending_OVC.h"
#include"Fit_Tables.h"
#include"RDY_OV.h"
#include"Cook_Order.h"
#include"EnumTypes.h"

#include"Restaurant.h"

class UI
{
private:
	Restaurant* pRes; // to set program mode in restaurant
public:
	UI(Restaurant* p);

	void Print(Queue<Action*> ActionListR, Queue<Action*> ActionListC,
		Queue<Order*> Pend_ODG, Queue<Order*> Pend_ODN, Queue<Order*> Pend_OT, Queue<Order*> Pend_OVN,
		Pending_OVC Pend_OVC, Queue<Order*> Pend_OVG, Queue<Order*> Ready_OT, Queue<Order*> Ready_OD,
		RDY_OV Ready_OV, Cook_Order Cooking_orders, Queue<Order*> Cancelled_Orders, Stack<Order*> Finished_Orders,
		PriQueue<Order*> InServ, PriQueue<Order*> Compo, Queue<Chef*> Free_CS, Queue<Chef*> Free_CN,
		PriQueue<Scooter*> Free_Scooters, Queue<Scooter*> Maint_Scooters, PriQueue<Scooter*> Busy_Scooters,
		Fit_Tables Free_Tables,Fit_Tables Busy_Sharable,Fit_Tables Busy_No_Share);

	void chooseMode();

	void setProgramMode(Mode m);


};

