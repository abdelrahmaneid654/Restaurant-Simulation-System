#include "Restaurant.h"

Restaurant::Restaurant()
{
	//Here I will initialze all variables we use ,after the random function called it will overwrte this,and in phase 2 the input will overwirte 
	CurrTimeStep = 0;
	numCN = numCS = 0;
	numScooter = 0;
	mainDur = 0;
	OverWaitTime = 0;
	////////////////////////////////////
	ScooterSpeed = 0;
	SpeedCN = SpeedCS = 0;
	BeforeMainOrders = 0;
	////////////////////////////////////
	OverWaitTime = 0;
	OrdersOD = OrdersOT = OrdersOV = 0;
	FinishedOrders = 0;
	CancelledOrders = 0;
	OverWaitOrders = 0;
	///////////////////////////////////
	TotalChefsBusyTime = 0;
	TotalScootersBusyTime = 0;
	//DON'T forget the point6 variables
	pUI = new UI();

}
/*
void Restaurant::LoadFromFile()
{

}

void Restaurant::SaveToFile()
{

}

void Restaurant::TakeOrderInputFile()
{

}
*/

//Now I comment this function ,for a later time .
void Restaurant::MoveOrderLists()
{/*
 I Write this only to make the reader to understand the logic : we move from back to front [in the sequence of the order]
 so we start from Ready lists and put the orders in the IN_Serv lists then put in  finished lists and for each type : OV make all need implementations for
 Scooters and for OT [it is the most easiest logic] move to finish list,and for OD  make all need implementations for
 Tables Sharing and non_Sharing

 */

	while (!Ready_OV.isEmpty() && !Free_Scooters.isempty())
	{
		Order* pOrder;
		Scooter* pScooter;
		Free_Scooters.dequeue(pScooter);
		Ready_OV.dequeue(pOrder);

		InServ.enqueue(pOrder);
		pOrder->SetScooter(pScooter);
		Busy_Scooters.enqueue(pScooter);
		//Time to return back:Time Travel is 2* distance/ScooterSpeed
		int TravelTime = 2 * pOrder->getDistance() / ScooterSpeed;
		pScooter->SetReturnTime(CurrTimeStep + TravelTime);

		pOrder->SetFinishTime(CurrTimeStep + TravelTime/2);
		Finished_Orders.push(pOrder);
		Busy_Scooters.dequeue(pScooter);
		Free_Scooters.enqueue(pScooter);


	}
	while (!Ready_OT.isempty())
	{
		Order* pOrder;
		Ready_OT.dequeue(pOrder);

		pOrder->SetFinishTime(CurrTimeStep);
		Finished_Orders.push(pOrder);

	}

	//It is for Dine in Orders but Still not Finished
	while (!Ready_OD.isempty())
	{
		Order* pOrder;
		Table* pTable;
		Ready_OD.peek(pOrder);
		bool ShareableFlag = pOrder->getFlag();// Function getFlag is specialized only about the Sharable flag .
		Free_Tables.peek(pTable);
		bool TableFlag = pTable->getType();
		int NeededSeats=pOrder->getNumSeats();
		switch (ShareableFlag)
		{
		case 0: //Shareable Order
			if (!TableFlag)// 0 For sharable table
			{
				//int AvailableSeats = pTable->getAvailableSeats(); In this I tried to use variable to be better  in shape but I don't like it after that,Even It is still an option to me
				if (NeededSeats <= pTable->getAvailableSeats())
				{
					pTable->SetAvailableSeats(pTable->getAvailableSeats() , NeededSeats);
					if (pTable->getAvailableSeats() == 0)
					{
						Free_Tables.dequeue(pTable);
						Busy_Sharable.enqueue(pTable);
						InServ.enqueue(pOrder);
							

					
						Finished_Orders.push(pOrder);
					}

				}

			}

			break;

		case 1://Not Shareable Order

			break;
		}


	}
}

int Restaurant::GetCurrentTimestep() const
{
	return CurrTimeStep;
}

void Restaurant::UpdateInterface()
{
	//Don't forget that you didn't add any variable for point 6 

	
	//Joke :Cnrl C Cntrl V function
	pUI->PrintFullLists(ActionListR, ActionListC, Pend_ODG, Pend_ODN, Pend_OT, Pend_OVN, Pend_OVC, Pend_OVG, Ready_OT, Ready_OD, Ready_OV, Cooking_orders, Cancelled_Orders, Finished_Orders, InServ, Compo, Free_CS, Free_CN, Free_Scooters, Free_Tables, Busy_Sharable, Busy_No_Share);
	pUI->PrintFullVariables(CurrTimeStep, numCN, numCS, numScooter, SpeedCN, SpeedCS, BeforeMainOrders, OverWaitTime, TotalOrders, OrdersOD, OrdersOT, OrdersOV, FinishedOrders, CancelledOrders, OverWaitOrders, TotalChefs, FinishedOrderPercentage, CancelledOrderPercentage, OverWaitOrderPercentage, TotalChefsBusyTime, TotalScootersBusyTime);
}

void Restaurant::RandomSimulation()
{
	CurrTimeStep = 1;
	//This loop for creataing random chefs and tables, and create scooters
	for (int i = 0; i < 10; i++)
	{
		Chef* pChef = CreateRandomChefs(i + 1);
		if (pChef->getType() == CN)
			Free_CN.enqueue(pChef);
		else
			Free_CS.enqueue(pChef);

		Table* pTable = CreateRandomTables(i + 1);
		if (pTable->getType() == Sharable)
		{
			Free_Tables.enqueue(pTable);
			pTable->setFlag(0);
		}
		else
		{
			pTable->setFlag(1);
			Free_Tables.enqueue(pTable);
		}
		Scooter* pScooter = new Scooter(i + 1);
		Free_Scooters.enqueue(pScooter);
	}
	//This loop for creating random orders and add them to the pending lists
	for (int i = 0; i < 500; i++)
	{
		Order* pOrder = CreateRandomOrder(CurrTimeStep);
		AddToPending(pOrder);

	}
	while (!AreAllOrdersFinishedOrCancelled())
	{
		for (int i = 0; i < 30; i++)
		{
			Order* pOrder = pickRandomOrderFromPendingLists();
			if (pOrder)//IT is always true but I made it for double check if I forget any thing in AreAllOrdersFinishedOrCancelled function
			{	pOrder->setChef(pickRandomChefs());
			Cooking_orders.enqueue(pOrder);
				//Here I will make the needed implementations for each order type like for OV make the time of cooking and then move it to the ready list and for OD make the time of cooking and then move it to the ready list and for OT make the time of cooking and then move it to the ready list 
				//I will make a function for each order type to do all these implementations and I will call this function here
			}
		}
		if ((rand() % 100) < 75)
		{
			Order* pOrder;
			for (int i = 0; i < 15; i++)
			{
				if (Cooking_orders.dequeue(pOrder))
				{
					FromCookingToReadyByType(pOrder);

				}
			}

		}
		for (int i = 0; i < 10; i++)
		{
			Order* pOrder = pickRandomOrderFromReadyLists();
			if (pOrder)
			{
				switch (pOrder->getType())
				{
				case OT:
					Ready_OT.dequeue(pOrder);
					Finished_Orders.push(pOrder);
					break;
				case OVN:
				case OVG:
				case OVC:
					Ready_OV.dequeue(pOrder);

					pOrder->setScooter();
					InServ.enqueue(pOrder);
					break;
				case ODN:
				case ODG:
					Ready_OD.dequeue(pOrder);
					pOrder->setTable();
					InServ.enqueue(pOrder);
					break;
				}

			}

		}


		pUI->UpdateInterFace();
		pUI->WaitForClick();
		CurrTimeStep++;
}

}
void Restaurant::AddToPending(Order* pOrder)
{
	int OrderType = pOrder->getType();

	switch (OrderType)
	{
	case 0:
		Pend_ODG.enqueue(pOrder);
		break;
	case 1:
		Pend_ODN.enqueue(pOrder);
		break;
	case 2:
		Pend_OT.enqueue(pOrder);
		break;
	case 3:
		Pend_OVN.enqueue(pOrder);
		break;
	case 4:
		Pend_OVC.enqueue(pOrder);//erorr in enqueue because it is from derived class from the queue and there is no implementation for the class yet.
		break;
	case 5:
		Pend_OVG.enqueue(pOrder);//function in enqueue should be replaced by insert because it is a priority queue
		break;
	}
}
bool Restaurant::AreAllOrdersFinishedOrCancelled()
{
	if (Pend_ODG.isempty() &&
		Pend_ODN.isempty() &&
		Pend_OT.isempty() &&
		Pend_OVN.isempty() &&
		Pend_OVC.isempty() &&//error because it is from derived class
		Pend_OVG.isempty() &&
		Ready_OT.isempty() &&
		Ready_OD.isempty() &&
		Ready_OV.isempty() &&//error because it is from derived class
		Cooking_orders.isempty() &&//error because it is from derived class
		InServ.isempty())
		return true;
	else
		return false;
}
Order* Restaurant::CreateRandomOrder(int ArrivalTime)
{
	static int ID = 1;
	OrderType type;
	int RandomType = rand() % 5;
	switch (RandomType)
	{
	case 0:
		type = ODG;
		break;
	case 1:
		type = ODN;
		break;
	case 2:	
		type = OT;
		break;
	case 3:
		type = OVN;
		break;
	case 4:
		type = OVG;
		break;
	}
	Order* pOrder = new Order(ID++, type);

	if (type == OVN || type == OVG)
	{
		int distance = rand() % 100 + 1;//Distance form 1 to 100
		pOrder->setDistance(distance);
	}
	else if (type == ODN || ODG)
	{
		int SharableFlag = rand() % 2;
		int EatingTime = rand() % 35 + 10;//Eating time from 10 to 45
		int seats = rand() % 12 + 1;//Single person to combo Order
		pOrder->setNumSeats(seats);
		pOrder->setEatingTime(EatingTime);
		pOrder->setSharableFlag(SharableFlag);
	}
	pOrder->setArrivalTime(ArrivalTime);

	return pOrder;
}
Table* Restaurant::CreateRandomTables(int TableId)
{

	Table* pTable = new Table(TableId);
	int type = rand() % 2;
	if (type)
		pTable->setType(Sharable);
	else
		pTable->setType(Non_Sharable);

	return pTable;
}
Chef* Restaurant::CreateRandomChefs(int ChefID)
{
	Chef* pChef = new Chef(ChefID);
	int type = rand() % 2;
	if (type)
	{
		pChef->setType(CN);
	}
	else {
		pChef->setType(CS);
	}
	return pChef;
}
Order * Restaurant::pickRandomOrderFromPendingLists()
{
	Order* pOrder=nullptr;
	int RandomList = rand() % 5;
	switch (RandomList)
	{
	case 0:
		if (!Pend_ODG.isempty())
			Pend_ODG.peek(pOrder);
		break;
	case 1:
		if (!Pend_ODN.isempty())
			Pend_ODN.peek(pOrder);
		break;
	case 2:
		if (!Pend_OT.isempty())
			Pend_OT.peek(pOrder);
		break;
	case 3:
		if (!Pend_OVN.isempty())
			Pend_OVN.peek(pOrder);
		break;
	case 4:
		if (!Pend_OVC.isempty())
			Pend_OVC.peek(pOrder);
		break;
	case 5:
		if (!Pend_OVG.isempty())
			Pend_OVG.peek(pOrder);
		break;
	}
	return pOrder;
}
Chef* Restaurant::pickRandomChefs()
{
	Chef* pChef;
	int randomPick = rand() % 2;
	if (randomPick)
	{
		if (!Free_CN.isempty())
			Free_CN.peek(pChef);

	}
	else
	{
		if (!Free_CS.isempty())
			Free_CS.peek(pChef);
	}
	return pChef;
}
Order* Restaurant::pickRandomOrderFromReadyLists()
{
	Order* pOrder=nullptr;
	int RandomList = rand() % 5;
	switch (RandomList)
	{
	case 0:
		if (!Ready_OT.isempty())
			Ready_OT.peek(pOrder);
		break;
	case 1:
		if (!Ready_OD.isempty())
			Ready_OD.peek(pOrder);
		break;
	case 2:
		if (!Ready_OV.isempty())
			Ready_OV.peek(pOrder);
		break;
	
	}
	return pOrder;
}
Order* Restaurant::FromCookingToReadyByType(Order* pOrder)
{
	if (!pOrder)
		return NULL;
	OrderType type = pOrder->getType();
	switch(type)
	{
	case ODG: //Dine in Orders
	case ODN:
		Ready_OD.enqueue(pOrder);
		break;
	case OT://Take away Orders
		Ready_OT.enqueue(pOrder);
		break;
	case OVN://Delivery Orders
	case OVG:
		Ready_OV.enqueue(pOrder);
		break;
	default:
		// To avoid Crashing
		break;
	}
	return pOrder;
	//Remember : After calling this func in any place ,You must dequeue the pOrder from the CookingList
}
bool Restaurant::CancelOrder(int id) {
	Order* pOrd = nullptr;

	// 1. SEARCH IN PENDING LISTS
	pOrd = Pend_ODN.RemoveByID(id);
	if (!pOrd) pOrd = Pend_ODG.RemoveByID(id);
	if (!pOrd) pOrd = Pend_OT.RemoveByID(id);
	if (!pOrd) pOrd = Pend_OVN.RemoveByID(id);
	if (!pOrd) pOrd = Pend_OVC.RemoveByID(id);
	if (!pOrd) pOrd = Pend_OVG.RemoveByID(id);

	//  2. SEARCH IN PROCESSING LISTS 
	if (!pOrd) pOrd = Cooking_orders.RemoveByID(id);
	if (!pOrd) pOrd = Ready_OT.RemoveByID(id);
	if (!pOrd) pOrd = Ready_OD.RemoveByID(id);
	if (!pOrd) pOrd = Ready_OV.RemoveByID(id);
	if (!pOrd) pOrd = InServ.RemoveByID(id);

	// --- 3. RESOURCE RECLAMATION LOGIC ---
	if (pOrd != nullptr) {

		// A. If the order had a Chef, free the Chef
		if (pOrd->getChef() != nullptr) {
			Chef* pChef = pOrd->getChef();
			// Return to the correct free list based on type
			if (pChef->getType() == CN)
				Free_CN.enqueue(pChef);
			else
				Free_CS.enqueue(pChef);

			pOrd->setChef(nullptr); // Unlink the order from the chef
		}

		// B. If it had a Table (Dine-in), free the Table
		if (pOrd->getTable() != nullptr) {
			Table* pTable = pOrd->getTable();
			// Assuming your Table has a way to reset seats or availability
			pTable->releaseTable(pOrd->getPartySize());
			pOrd->setTable(nullptr);
		}

		if (pOrd->getScooter() != nullptr) {
			Scooter* pScooter = pOrd->getScooter();
			Back_Scooters.enqueue(pScooter);
			pOrd->setScooter(nullptr);
		}

		// --- 3. MOVE TO CANCELLED QUEUE ---
		pOrd->setStatus(CANCELLED); // Assuming CANCELLED is in your enum

		// This is the specific queue for cancelled orders
		Cancelled_Orders.enqueue(pOrd);

		return true;

	return false; // ID was not found in any active list
}
Restaurant::~Restaurant()
{
	delete pUI;

}