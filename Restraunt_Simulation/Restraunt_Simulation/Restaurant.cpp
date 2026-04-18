#include "Restaurant.h"
#include "Action.h"
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
	Restaurant* temp = this;
	pUI = new UI(temp);

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

	while (!Ready_OV.isempty() && !Free_Scooters.isempty())
	{
		Order* pOrder;
		Scooter* pScooter;
		Free_Scooters.dequeue(pScooter);
		Ready_OV.dequeue(pOrder);
		OV* temp = (OV*)pOrder;
		InServ.enqueue(pOrder);
		temp->set_assigned_scooter(pScooter);
		//Time to return back:Time Travel is 2* distance/ScooterSpeed
		int TravelTime = 2 * temp->get_distance()/ ScooterSpeed;
		pScooter->set_return_time(CurrTimeStep + TravelTime);
		pScooter->update_info(temp->get_distance(), TravelTime);

		pOrder->set_TF(CurrTimeStep + TravelTime/2);
		Finished_Orders.push(pOrder);
		Busy_Scooters.dequeue(pScooter);
		Free_Scooters.enqueue(pScooter);


	}
	while (!Ready_OT.isempty())
	{
		Order* pOrder;
		Ready_OT.dequeue(pOrder);

		pOrder->set_TF(CurrTimeStep);
		Finished_Orders.push(pOrder);

	}

	//It is for Dine in Orders but Still not Finished
	while (!Ready_OD.isempty())
	{
		OD* pOrder; 
		Table* pTable;
		Ready_OD.peek(pOrder);
		bool ShareableFlag = ((OD*)pOrder)->IS_Sharable();// Function getFlag is specialized only about the Sharable flag .
		OD* temp = (OD*)pOrder;
		pTable=Free_Tables.getBest(temp);
		bool TableFlag = pTable->get_Is_sharable();
		int NeededSeats= temp->get_num_of_seats();
		switch (ShareableFlag)
		{
		case 0: //Shareable Order
			if (!TableFlag)// 0 For sharable table
			{
				//int AvailableSeats = pTable->getAvailableSeats(); In this I tried to use variable to be better  in shape but I don't like it after that,Even It is still an option to me
				temp->set_assigned_table(pTable);
			}
			break;
		case 1://Not Shareable Order
			temp->set_assigned_table(pTable);

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
	pUI->Print(ActionListR, ActionListC, Pend_ODG, Pend_ODN, Pend_OT, Pend_OVN, Pend_OVC, Pend_OVG, Ready_OT, Ready_OD, Ready_OV, Cook_orders, Cancelled_Orders, Finished_Orders, InServ, Compo, Free_CS, Free_CN, Free_Scooters,Maint_Scooters , Busy_Scooters,Free_Tables, Busy_Sharable, Busy_No_Share);
}
void Restaurant::RandomSimulation()
{
	CurrTimeStep = 1;
	//This loop for creataing random chefs and tables, and create scooters
	for (int i = 0; i < 10; i++)
	{
		Chef* pChef = CreateRandomChefs(i + 1);
		if (pChef->gettype() == CN)
			Free_CN.enqueue(pChef);
		else
			Free_CS.enqueue(pChef);

		Table* pTable = CreateRandomTables(i + 1);
		if (pTable->get_Is_sharable() == Sharable)
		{
			Free_Tables.enqueue(pTable);
			pTable->set_IS_sharable(true);
		}
		else
		{
			pTable->set_IS_sharable(false);
			Free_Tables.enqueue(pTable);
		}
		int id = i;
		Scooter* pScooter = new Scooter(ScooterSpeed,id,12,12);
		pScooter->update_info(1 + i, 1 + 2 * i);//I just want to make the scooters different in the distance and the busy time to make the simulation more real but I can make them all the same if you want
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
			{	pOrder->set_assigned_chef(pickRandomChefs());
			Cook_orders.enqueue(pOrder);
				//Here I will make the needed implementations for each order type like for OV make the time of cooking and then move it to the ready list and for OD make the time of cooking and then move it to the ready list and for OT make the time of cooking and then move it to the ready list 
				//I will make a function for each order type to do all these implementations and I will call this function here
			}
		}
		if ((rand() % 100) < 75)
		{
			Order* pOrder=nullptr;
			for (int i = 0; i < 15; i++)
			{
				if (Cook_orders.dequeue(pOrder))
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
				switch (pOrder->gettype())
				{
					case OT_O:

						Ready_OT.dequeue(pOrder);
						Finished_Orders.push(pOrder);
						break;
					case OVN:
					case OVG:
					case OVC:
						
						Ready_OV.dequeue(pOrder);
						InServ.enqueue(pOrder);
						break;
					case ODN:
					case ODG:
						Ready_OD.dequeue(pOrder);
						Table* pTable=nullptr;
						((OD*)pOrder)->set_assigned_table(pTable);
						InServ.enqueue(pOrder);
						break;
				}

			}

		}
		int totalGenerated = Pend_ODG.getcount() + Pend_ODN.getcount() + Pend_OT.getcount() + Pend_OVN.getcount() + Pend_OVC.getcount() + Pend_OVG.getcount();
		if (totalGenerated > 0) {
			int randomID = (rand() % totalGenerated) + 1;
			CancelOrder(randomID);
		}
		if ((rand() % 100) < 25) {
			Order* pFinished;
			if (InServ.dequeue(pFinished)) 
			{
				ReleaseResources(pFinished);
				Finished_Orders.push(pFinished);
			}
		}
		UpdateInterface();

		pUI->WaitForClick();
		CurrTimeStep++;
	}

}
void Restaurant::AddToPending(Order* pOrder)
{
	OrderType OrderType = pOrder->gettype();  

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
		Cook_orders.isempty() &&//error because it is from derived class
		InServ.isempty())
		return true;
	else
		return false;
}
Order* Restaurant::CreateRandomOrder(int ArrivalTime)
{
	Order* pOrder=nullptr;
	static int ID = 1;
	OrderType type;
	int RandomType = rand() % 5;
	switch (RandomType)
	{
	case 0:
		type = ODG;
		 pOrder = new OD(ID + 2, ID++, ID * 2, ID * 3, ID * 5,ID+3,ID+17,ID%2,ODG);

		break;
	case 1:
		type = ODN;
		 pOrder = new OD(ID + 2, ID++, ID * 1, ID * 3, ID * 4, ID + 3, ID + 11, ID % 2, ODN);

		break;
	case 2:	
		type = OT_O;
		 pOrder = new OT(ID + 2, ID++, ID * 1, ID * 3, ID * 4);

		break;
	case 3:
		type = OVN;
		 pOrder = new OV(ID+2,ID++,ID*3,ID*3,ID*5,100*ID,OVN);
		break;
	case 4:
		type = OVG;
		pOrder = new OV(ID + 2, ID++, ID * 2, ID * 3, ID * 5, 120 * ID, OVG);

		break;
	}



	return pOrder;
}
Table* Restaurant::CreateRandomTables(int TableId)
{

	Table* pTable = new Table(TableId, TableId+5);
	int type = rand() % 2;
	if (type)
		pTable->set_IS_sharable(Sharable);
	else
		pTable->set_IS_sharable(Non_Sharable);

	return pTable;
}
Chef* Restaurant::CreateRandomChefs(int ChefID)
{
	Chef* pChef = new Chef(ChefID*9,ChefID);
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
	Chef* pChef=nullptr;
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
	int RandomList = rand() % 3;
	switch (RandomList)
	{
	case 0:
		if (!Ready_OT.isempty())
			Ready_OT.peek(pOrder);
		break;
	case 1:
		if (!Ready_OD.isempty()) {
			
			Ready_OD.peek(pOrder);
		}
		break;
	case 2:
		if (!Ready_OV.isempty()) {
			OV* temp1 = (OV*)pOrder;
			Ready_OV.peek(pOrder);
		}
		break;
	
	}
	return pOrder;
}
Order* Restaurant::FromCookingToReadyByType(Order* pOrder)
{
	if (!pOrder)
		return NULL;
	OrderType type = pOrder->gettype();
	switch(type)
	{
	case ODG: //Dine in Orders
	case ODN: {
		OD* temp = (OD*)pOrder;
		Ready_OD.enqueue(temp);
		break;
	}
	case OT_O :{ //Take away Orders
				Ready_OT.enqueue(pOrder);
				break; }
	case OVN:
	case OVG: {
		OV* temp1 = (OV*)pOrder;
		Ready_OV.enqueue(temp1);
		break;
	}
	default: {
		// To avoid Crashing
		break;
	}
	}
	return pOrder;
	//Remember : After calling this func in any place ,You must dequeue the pOrder from the CookingList
}

bool Restaurant::CancelOrder(int id) {
	
	Order* cancelledOVC = Pend_OVC.Cancel_Order(id); 
	Order* cancelledCook = Cook_orders.Cancel_Order(id); 
	Order* cancelledReady = Ready_OV.Cancel_Order(id);

	if (cancelledOVC || cancelledReady) 
	{
		return true;
	}
	else if (cancelledCook) 
	{
		Chef* assigned = cancelledCook->get_assigned_chef(); 
		ChefType type = assigned->gettype();  
		switch(type)
		{
		case CN:
			Free_CN.enqueue(assigned);
			break;
		case CS:
			Free_CS.enqueue(assigned);
			break;
		}
		return true;
	}
	return false;
}
void Restaurant::setRestaurantMode(Mode m)
{
	RestaurantMode = m;
}
Restaurant::~Restaurant()
{
	delete pUI;
}
