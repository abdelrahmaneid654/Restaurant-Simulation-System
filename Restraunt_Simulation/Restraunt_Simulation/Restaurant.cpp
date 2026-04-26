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

//void Restaurant::MoveOrderLists()
//{/*
// I Write this only to make the reader to understand the logic : we move from back to front [in the sequence of the order]
// so we start from Ready lists and put the orders in the IN_Serv lists then put in  finished lists and for each type : OV make all need implementations for
// Scooters and for OT [it is the most easiest logic] move to finish list,and for OD  make all need implementations for
// Tables Sharing and non_Sharing
//
// */
//
//	while (!Ready_OV.isempty() && !Free_Scooters.isempty())
//	{
//		Order* pOrder;
//		Scooter* pScooter;
//		Free_Scooters.dequeue(pScooter);
//		Ready_OV.dequeue(pOrder);
//		OV* temp = (OV*)pOrder;
//		InServ.enqueue(pOrder);
//		temp->set_assigned_scooter(pScooter);
//		//Time to return back:Time Travel is 2* distance/ScooterSpeed
//		int TravelTime = 2 * temp->get_distance()/ ScooterSpeed;
//		pScooter->set_return_time(CurrTimeStep + TravelTime);
//		pScooter->update_info(temp->get_distance(), TravelTime);
//
//		pOrder->set_TF(CurrTimeStep + TravelTime/2);
//		Finished_Orders.push(pOrder);
//		Back_Scooters.dequeue(pScooter);
//		Free_Scooters.enqueue(pScooter);
//
//
//	}
//	while (!Ready_OT.isempty())
//	{
//		Order* pOrder;
//		Ready_OT.dequeue(pOrder);
//
//		pOrder->set_TF(CurrTimeStep);
//		Finished_Orders.push(pOrder);
//
//	}
//
//	//It is for Dine in Orders but Still not Finished
//	while (!Ready_OD.isempty())
//	{
//		Order* pOrder; 
//		Table* pTable;
//		Ready_OD.dequeue(pOrder);
//		bool ShareableFlag = ((OD*)pOrder)->IS_Sharable();// Function getFlag is specialized only about the Sharable flag .
//		OD* temp = (OD*)pOrder;
//		pTable=Free_Tables.getBest(temp);
//		T TableFlag = pTable->get_Is_sharable();
//		int NeededSeats= temp->get_num_of_seats();
//		switch (ShareableFlag)
//		{
//		case 0: //Shareable Order
//			if (!TableFlag)// 0 For sharable table
//			{
//				//int AvailableSeats = pTable->getAvailableSeats(); In this I tried to use variable to be better  in shape but I don't like it after that,Even It is still an option to me
//				temp->set_assigned_table(pTable);
//			}
//			break;
//		case 1://Not Shareable Order
//			temp->set_assigned_table(pTable);
//
//			break;
//		}
//	}
//}

int Restaurant::GetCurrentTimestep() const
{
	return CurrTimeStep;
}

void Restaurant::UpdateInterface()
{
	//Don't forget that you didn't add any variable for point 6 
	//Joke :Cnrl C Cntrl V function
	pUI->Print(ActionListR, ActionListC, Pend_ODG, Pend_ODN, Pend_OT, Pend_OVN, Pend_OVC, Pend_OVG, 
		Ready_OT, Ready_OD, Ready_OV, Cook_orders, Cancelled_Orders, Finished_Orders, InServ, 
		Compo, Free_CS, Free_CN, Free_Scooters,Maint_Scooters , Back_Scooters,Free_Tables, 
		Busy_Sharable, Busy_No_Share);
}
//void Restaurant::RandomSimulation()
//{
//	CurrTimeStep = 1;
//	//This loop for creataing random chefs and tables, and create scooters
//	for (int i = 0; i < 30; i++)
//	{
//		CreateRandomChefs(i + 1);
//
//		CreateRandomTables(i + 1);
//		
//		CreatRandomScooter(i + 1); 
//	}
//	//This loop for creating random orders and add them to the pending lists
//	for (int i = 0; i < 500; i++)
//	{
//		CreateRandomOrder(i + 1);  
//	}
//
//	UpdateInterface(); // shows the initial state
//
//	while (!AreAllOrdersFinishedOrCancelled())
//	{
//		for (int i = 0; i < 30; i++)
//		{
//			Chef* pSelectedChef = pickRandomChefs(); // it dequeues inside it the assigned chef
//
//			if (pSelectedChef)
//			{
//				Order* pOrder = pickRandomOrderFromPendingLists();// it dequeues inside it the order
//
//				if (pOrder)
//				{
//					pOrder->set_assigned_chef(pSelectedChef);
//					Cook_orders.enqueue(pOrder);
//				}
//				else
//				{
//					if (pSelectedChef->gettype() == CN) 
//						Free_CN.enqueue(pSelectedChef);
//					else 
//						Free_CS.enqueue(pSelectedChef);
//					break; // in both cases break
//				}
//			}
//			else
//			{
//				break;
//			}
//		}
//		// moving random order from cooking to ready by 75% percent
//		{
//			Order* pOrder=nullptr;
//			for (int i = 0; i < 15; i++)
//			{
//				if ((rand() % 100) < 75)
//				{
//					if (Cook_orders.dequeue(pOrder)) // dequeue the cooking order
//					{
//						Chef* assignedChef = pOrder->get_assigned_chef();
//						pOrder->set_assigned_chef(nullptr);
//						ChefType type = assignedChef->gettype();
//
//						switch (type) //return the chef to free list
//						{
//						case CN:
//							Free_CN.enqueue(assignedChef);
//							break;
//						case CS:
//							Free_CS.enqueue(assignedChef);
//							break;
//						}
//
//						FromCookingToReadyByType(pOrder); // add the order here according to its type  
//
//					}
//					else
//						break;
//				}
//			}
//		}
//
//		for (int i = 0; i < 10; i++)
//		{
//			Order* pOrder = pickRandomOrderFromReadyLists();
//
//			if (pOrder)
//			{
//				OrderType type = pOrder->gettype();
//
//				switch (type)
//				{
//				case ODG:
//				case ODN:
//				{
//					Table* pTable = pickRandomTable();
//					if(pTable) 
//					{
//					((OD*)pOrder)->set_assigned_table(pTable);
//						InServ.enqueue(pOrder);
//					}
//					else
//					{
//						Ready_OD.enqueue(pOrder);
//					}
//					break;
//				}
//				case OVG:
//				case OVN:
//				case OVC:
//				{
//					Scooter* pScooter = pickRandomScooter();
//					((OV*)pOrder)->set_assigned_scooter(pScooter);
//					if(pScooter) 
//					{
//						InServ.enqueue(pOrder);
//					}
//					else
//					{
//						Ready_OV.enqueue(pOrder);
//					}
//					break;
//				}
//
//				case OT_O:
//					Finished_Orders.push(pOrder); 
//					break;
//				}
//			}
//
//		}
//		int totalGenerated = Pend_ODG.getcount() + Pend_ODN.getcount() + Pend_OT.getcount() + Pend_OVN.getcount() + Pend_OVC.getcount() + Pend_OVG.getcount();
//		if (totalGenerated > 0) {
//			int randomID = (rand() % totalGenerated) + 1;
//			CancelOrder(randomID); // handled the 3 cases inside it
//		}
//
//		if ((rand() % 100) < 25) {
//			Order* pFinished;
//			if (InServ.dequeue(pFinished)) 
//			{
//				OrderType type = pFinished->gettype();
//
//				switch (type)
//				{
//				case ODG:
//				case ODN:
//				{
//					Table* pTable = ((OD*)pFinished)->get_assigned_table();
//					((OD*)pFinished)->set_assigned_table(nullptr);
//					Free_Tables.enqueue(pTable); 
//					break;
//				}
//				case OVC:
//				case OVG:
//				case OVN:
//				{
//					Scooter* pScooter = ((OV*)pFinished)->get_assigned_scooter();
//					((OV*)pFinished)->set_assigned_scooter(nullptr);
//					Back_Scooters.enqueue(pScooter);  
//					break;
//				}
//				}
//				Finished_Orders.push(pFinished);
//			}
//		}
//		UpdateInterface();
//
//		pUI->WaitForClick();
//		CurrTimeStep++;
//	}
//}
void Restaurant::AddToPending(Order* pOrder)
{
	OrderType OrderType = pOrder->gettype();  

	switch (OrderType)
	{
	case ODG:
		Pend_ODG.enqueue(pOrder);
		break;
	case ODN:
		Pend_ODN.enqueue(pOrder);
		break;
	case OT_O:
		Pend_OT.enqueue(pOrder);
		break;
	case OVN:
		Pend_OVN.enqueue(pOrder);
		break;
	case OVG:
		Pend_OVG.enqueue(pOrder);//function in enqueue should be replaced by insert because it is a priority queue
		break;
	case OVC:
		Pend_OVC.enqueue(pOrder);//erorr in enqueue because it is from derived class from the queue and there is no implementation for the class yet.
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

//void Restaurant::CreateRandomOrder(int ArrivalTime)
//{
//	Order* pOrder=nullptr;
//	int ID = ArrivalTime; 
//	OrderType type;
//	int RandomType = rand() % 6;
//	switch (RandomType)
//	{
//	case 0:
//	{
//		type = ODG;
//		pOrder = new OD(ID + 2, ID++, ID * 2, ID * 3, ID * 5, ID + 3, ID + 17, ID % 2, ODG);
//		Pend_ODG.enqueue(pOrder);
//		break;
//	}
//	case 1:
//	{
//		type = ODN;
//		pOrder = new OD(ID + 2, ID++, ID * 1, ID * 3, ID * 4, ID + 3, ID + 11, ID % 2, ODN);
//		Pend_ODN.enqueue(pOrder);
//		break;
//	}
//	case 2:	
//	{
//		type = OT_O;
//		pOrder = new OT(ID + 2, ID++, ID * 1, ID * 3, ID * 4);
//		Pend_OT.enqueue(pOrder);
//		break;
//	}
//	case 3:
//	{
//		type = OVN;
//		pOrder = new OV(ID + 2, ID++, ID * 3, ID * 3, ID * 5, 100 * ID, OVN);
//		Pend_OVN.enqueue(pOrder);
//		break;
//	}
//	case 4:
//	{
//		type = OVG;
//		pOrder = new OV(ID + 2, ID++, ID * 2, ID * 3, ID * 5, 120 * ID, OVG);
//		Pend_OVG.enqueue(pOrder);
//		break;
//	}
//	case 5:
//	{
//		type = OVC;
//		pOrder = new OV(ID + 2, ID++, ID * 2, ID * 3, ID * 5, 120 * ID, OVC);
//		Pend_OVC.enqueue(pOrder);
//		break;
//	}
//	}
//}
//void Restaurant::CreateRandomTables(int TableId)
//{
//	Table* pTable = new Table(TableId, TableId+5);
//	int type = rand() % 2;
//	if (type)
//	{
//		pTable->set_IS_sharable(Sharable);
//	}
//	else
//	{
//		pTable->set_IS_sharable(Non_Sharable);
//	}
//	Free_Tables.enqueue(pTable); 
//}
//void Restaurant::CreatRandomScooter(int ScooterID)
//{
//	Scooter* pScooter = new Scooter(ScooterID * 10, ScooterID, ScooterID + 6, ScooterID + 10);
//	Free_Scooters.enqueue(pScooter);
//}
//void Restaurant::CreateRandomChefs(int ChefID)
//{
//	Chef* pChef = new Chef(ChefID*9,ChefID);
//	int type = rand() % 2;
//	if (type)
//	{
//		pChef->setType(CN);
//		Free_CN.enqueue(pChef);
//	}
//	else {
//		pChef->setType(CS);
//		Free_CS.enqueue(pChef); 
//	}
//}
//Order * Restaurant::pickRandomOrderFromPendingLists()
//{
//	Order* pOrder=nullptr;
//	int RandomList = rand() % 6;
//	switch (RandomList)
//	{
//	case ODG: 
//		if (!Pend_ODG.isempty())
//			Pend_ODG.dequeue(pOrder);
//		break;
//	case ODN: 
//		if (!Pend_ODN.isempty())
//			Pend_ODN.dequeue(pOrder);
//		break;
//	case OT_O: 
//		if (!Pend_OT.isempty())
//			Pend_OT.dequeue(pOrder);
//		break;
//	case OVN: 
//		if (!Pend_OVN.isempty())
//			Pend_OVN.dequeue(pOrder);
//		break;
//	case OVG:
//		if (!Pend_OVG.isempty())
//			Pend_OVG.dequeue(pOrder);
//		break;
//	case OVC: 
//		if (!Pend_OVC.isempty())
//			Pend_OVC.dequeue(pOrder);
//		break;
//		
//	}
//	return pOrder;
//}
//Chef* Restaurant::pickRandomChefs()
//{
//	Chef* pChef=nullptr;
//	int randomPick = rand() % 2;
//	if (randomPick)
//	{
//		if (!Free_CN.isempty())
//			Free_CN.dequeue(pChef);
//
//	}
//	else
//	{
//		if (!Free_CS.isempty())
//			Free_CS.dequeue(pChef); 
//	}
//	return pChef;
//}
//Scooter* Restaurant::pickRandomScooter()
//{
//	Scooter* pScoot;
//	if (!Free_Scooters.dequeue(pScoot))
//	{
//		Back_Scooters.dequeue(pScoot);
//	}
//
//	return pScoot;
//}
//Table* Restaurant::pickRandomTable()
//{
//	Table* pTable=nullptr;
//	Free_Tables.dequeue(pTable);
//
//	if (pTable) {
//		TableType type = pTable->get_Is_sharable();
//		switch (type) {
//		case Non_Sharable:
//			Busy_No_Share.enqueue(pTable);
//			break;
//		case Sharable:
//			Busy_Sharable.enqueue(pTable);
//			break;
//		}
//	}
//	return pTable;  
//}
//
//Order* Restaurant::pickRandomOrderFromReadyLists()
//{
//	Order* pOrder=nullptr;
//	int RandomList = rand() % 3;
//	switch (RandomList)
//	{
//	case 0:
//		if (!Ready_OT.isempty())
//			Ready_OT.dequeue(pOrder);
//		break;
//	case 1:
//		if (!Ready_OD.isempty() && !Free_Tables.isempty()) {
//			Ready_OD.dequeue(pOrder);
//		}
//		break;
//	case 2:
//		if (!Ready_OV.isempty() && !Free_Scooters.isempty()) {
//			Ready_OV.dequeue(pOrder);
//		}
//		break;
//	
//	}
//	return pOrder;
//}
Order* Restaurant::FromCookingToReadyByType(Order* pOrder)
{
	if (!pOrder)
		return NULL;
	OrderType type = pOrder->gettype();
	switch(type)
	{
	case ODG: //Dine in Orders
	case ODN: 
	{
		Ready_OD.enqueue(pOrder);
		//Table* pTable = pickRandomTable();
		//((OD*)pOrder)->set_assigned_table(pTable); 
		break;
	}
	case OT_O :
	{ //Take away Orders
		Ready_OT.enqueue(pOrder);
		break; 
	}
	case OVN:
	case OVG: 
	case OVC:
	{
		Ready_OV.enqueue(pOrder);
		//Scooter* pScooter = pickRandomScooter();
		//((OV*)pOrder)->set_assigned_scooter(pScooter);
		break;
	}
	default: {
		// To avoid Crashing
		break;
	}
	}
	return pOrder;
}

void Restaurant::FromActionToPending(int time)
{
	Action* pAction; 
	ActionListR.peek(pAction);
	if (time == pAction->getTimeStep())
	{
		pAction->Act();
		ActionListR.dequeue(pAction); 
	}
}

void Restaurant::checkScootersList(int time)
{
	Scooter* pScooter;
	Maint_Scooters.peek(pScooter);
	if (pScooter->get_Main_Dur() == time - pScooter->getTimeStepOfMaint())
	{
		Maint_Scooters.dequeue(pScooter);
		Free_Scooters.enqueue(pScooter); 
	}
	Back_Scooters.peek(pScooter);
	if (pScooter->getReturnDistance() == 0)
	{
		Back_Scooters.dequeue(pScooter);
		if (pScooter->get_Main_Ords() == pScooter->get_counter())
		{
			pScooter->setTimeStepOfMaint(time);
			Maint_Scooters.enqueue(pScooter);
			pScooter->reset_counter();
		}
		else
		{
			Free_Scooters.enqueue(pScooter); 
		}
	}
}

bool Restaurant::CancelOrder(int id) {
	
	Order* cancelledOVC = Pend_OVC.Cancel_Order(id); 
	Order* cancelledCook = Cook_orders.Cancel_Order(id); 
	Order* cancelledReady = Ready_OV.Cancel_Order(id);

	if (cancelledOVC) 
	{
		Scooter* pScooter = ((OV*)cancelledOVC)->get_assigned_scooter();
		((OV*)cancelledOVC)->set_assigned_scooter(nullptr);
		Cancelled_Orders.enqueue(cancelledOVC);
		return true;
	}
	else if (cancelledReady)
	{ 
		Scooter* pScooter = ((OV*)cancelledReady)->get_assigned_scooter();
		((OV*)cancelledReady)->set_assigned_scooter(nullptr);
		Cancelled_Orders.enqueue(cancelledReady);  
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
