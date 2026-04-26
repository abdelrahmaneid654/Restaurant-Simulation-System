#include "Restaurant.h"
#include "Action.h"
#include"RequestAction.h"
#include"CancelAction.h"

#include"fstream"
Restaurant::Restaurant()
{
	//Here I will initialze all variables we use ,after the random function called it will overwrte this,and in phase 2 the input will overwirte 
	CurrTimeStep = 0;
	numCN = numCS = 0;
	numScooter = 0;
	MainDur = 0;
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

//Now I comment this function ,for a later time .



int Restaurant::GetCurrentTimestep() const
{
	return CurrTimeStep;
}

 void Restaurant::UpdateInterface()
{
	//Don't forget that you didn't add any variable for point 6 
	//Joke :Cnrl C Cntrl V function
	pUI->Print(ActionList, Pend_ODG, Pend_ODN, Pend_OT, Pend_OVN, Pend_OVC, Pend_OVG,
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

void Restaurant::createOutputFile()
{
	ofstream file("Output.txt");
	if (file.is_open())
	{
		Order* pOrder = nullptr;
		Stack<Order*> temp; 

		while (!Finished_Orders.isempty())
		{
			Finished_Orders.pop(pOrder);
			pOrder->printInFile(file); 
			file << endl;

			temp.push(pOrder);
		}

		while (!temp.isempty()) // return elements back in Finished_Orders
		{
			Order* p;
			temp.pop(p);
			Finished_Orders.push(p); 
		}

		file << "Total number of orders: " << TotalOrders << endl;
		file << "Dine-In Orders: " << OrdersOD << endl;
		file << "Delivery Orders: " << OrdersOV << endl; 
		file << "Takeaway Orders: " << OrdersOT << endl; 

		file << "Total number of chefs: " << TotalChefs << endl;
		file << "Special Chefs: " << numCS << endl;
		file << "Normal Chefs: " << numCN << endl;

		file << "Total number of Scooters: " << numScooter << endl;
		/*file << "Special Chefs: " << numCS << endl;
		file << "Normal Chefs: " << numCN << endl;*/
		
		file << "Percentage of Finished orders: " << 1.0*FinishedOrders/TotalOrders * 100.0 << endl;
		file << "Percentage of Cancelled orders: " << 1.0 * CancelledOrders / TotalOrders * 100.0 << endl;

		
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


Order* Restaurant::FromCookingToReadyByType(Order* pOrder)
{
	if (!pOrder)
		return NULL;
	Chef* assignedChef = pOrder->get_assigned_chef();
//	assignedChef->gettype() == CN ? Free_CN.enqueue(assignedChef) : Free_CS.enqueue(assignedChef);
	if (assignedChef)//I make this instead of the above line to avoid the crash if the assignedchef is nullptr
	{
		
		ChefType type = assignedChef->gettype();
		switch (type)
		{
		case CN:
			Free_CN.enqueue(assignedChef);
			break;
		case CS:
			Free_CS.enqueue(assignedChef);
			break;
		}
		assignedChef->update_info(CurrTimeStep - pOrder->get_TA());
	pOrder->set_assigned_chef(nullptr);
	
	}
	pOrder->set_TR(CurrTimeStep);
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
//		FinalizeOT();
		Ready_OT.enqueue(pOrder);
		break; 
	}
	case OVC:
	{
		Ready_OV.enqueue(pOrder);
		//Scooter* pScooter = pickRandomScooter();
		//((OV*)pOrder)->set_assigned_scooter(pScooter);
		break;
	}
	case OVG: 
	{
		Ready_OV.enqueue(pOrder);
		//Scooter* pScooter = pickRandomScooter();
		//((OV*)pOrder)->set_assigned_scooter(pScooter);
		break;
	}
	case OVN:
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
Order* Restaurant::AssingPendingToChef(Order* pOrder)
{
	if (!pOrder)
		return NULL;
	/*
	 Pending Lists Name :
			Pend_ODG
			Pend_ODN
			Pend_OT
			Pend_OVN
			Pend_OVC
			Pend_OVG
	 */

	pOrder->set_TA(CurrTimeStep);
	OrderType type = pOrder->gettype();
	switch (type)
	{
		case ODG:
		case OVG:
		{
			if (Free_CS.isempty())
				return nullptr;
			else
			{
				Chef* pChef;
				Free_CS.dequeue(pChef);
				pOrder->set_assigned_chef(pChef);
				if (type == ODG)
				{
					Pend_ODG.dequeue(pOrder);
				}
				else
				{
					Pend_OVG.dequeue(pOrder);
				}
				Cook_orders.enqueue(pOrder);
			}
		}
		break;
		case ODN:
		case OVC:
		{

			if (Free_CN.isempty())
			{
				if (Free_CS.isempty())
					return nullptr;
				else
				{
					Chef* pChef;
					Free_CS.dequeue(pChef);
					pOrder->set_assigned_chef(pChef);
					if (type == ODN)
					{
						Pend_ODN.dequeue(pOrder);
					}
					else
					{
						Pend_OVC.dequeue(pOrder);
					}
					Cook_orders.enqueue(pOrder);
				}
			}
			else
			{
					Chef* pChef;
					Free_CN.dequeue(pChef);
					pOrder->set_assigned_chef(pChef);
				if (type == ODN)
				{
					Pend_ODN.dequeue(pOrder);
				}
				else
				{
					Pend_OVC.dequeue(pOrder);
				}
					Cook_orders.enqueue(pOrder);
			}
		}
		break;
		case OT_O:
		case OVN:
		{

			if (Free_CN.isempty())
				return NULL;

			else
			{
					Chef* pChef;
					Free_CN.dequeue(pChef);
					pOrder->set_assigned_chef(pChef);
				if (type == OVN)
				{
					Pend_OVN.dequeue(pOrder);
				}
				else
				{
					Pend_OT.dequeue(pOrder);
				}
					Cook_orders.enqueue(pOrder);
			}
		}
		break;
		default:
			return nullptr; 
		break;

	}
	return pOrder;
}
Order* Restaurant::AssignScooter()
{
	//This function is still not finished because It has errors in dequeue process and looping in the ready OV list 
	Order* pOrder =nullptr;
	
	Order* pnext=NULL;
	if (Ready_OV.isempty() || Free_Scooters.isempty())
		return NULL;
	Ready_OV.peek(pOrder);
	while (pOrder)
	{
		if (pOrder->gettype() == OVC)
		{
			break;
		}
		else
		{
			pnext = pOrder->next;
			pOrder = pnext;

		}
	}
	if (!pOrder)
	{
		Ready_OV.peek(pOrder);
	}	
		Scooter* pScooter;
		Free_Scooters.dequeue(pScooter);
		((OV*)pOrder)->set_assigned_scooter(pScooter);
		pOrder->set_TS(CurrTimeStep);
		InServ.enqueue(pOrder);
		Ready_OV.dequeue(pOrder);
		return pOrder;
}






void Restaurant::getAverage()
{
	Stack<Order*> temp;
	Order* pOrder;

	// Avergae TI
	double sumTI = 0;
	for (int i = 0;i < FinishedOrders;i++)
	{
		Finished_Orders.pop(pOrder);
		sumTI += pOrder->get_TI();

		temp.push(pOrder);
	}


}

void Restaurant::checkScootersList(int time)
{
	Scooter* pScooter;

	Maint_Scooters.peek(pScooter);
	if (MainDur == time - pScooter->getTimeStepOfMaint())
	{
		Maint_Scooters.dequeue(pScooter);
		pScooter->update_info(0, 0, Free);
		Free_Scooters.enqueue(pScooter); 
	}

	Back_Scooters.peek(pScooter);
	if (pScooter->getReturnDistance() == 0)
	{
		Back_Scooters.dequeue(pScooter);

		if (BeforeMainOrders == pScooter->get_counter())
		{
			pScooter->setTimeStepOfMaint(time);
			pScooter->update_info(0, MainDur,Maint);  
			Maint_Scooters.enqueue(pScooter); 
			pScooter->reset_counter();
		}
		else
		{
			pScooter->update_info(0, 0, Free);
			Free_Scooters.enqueue(pScooter); 
		}
	}
}

bool Restaurant::assignTable(Order* o)
{
	OD* pOD = ((OD*)o);
	if (pOD->IS_Sharable())
	{
		Table* pTable = Busy_Sharable.getBest(pOD);

		if (pTable)
		{
			pTable->put_order(pOD);
			return true;
		}
		else
		{
			pTable = Free_Tables.getBest(pOD);

			if (pTable)
			{
				pTable->set_IS_sharable(Sharable);
				pTable->put_order(pOD);
				Busy_Sharable.enqueue(pTable);
				return true;
			}
			else
				return false;
		}
	}
	else
	{
		Table* pTable = Free_Tables.getBest(pOD);

		if (pTable)
		{
			pTable->put_order(pOD);
			pTable->set_IS_sharable(Non_Sharable);
			Busy_No_Share.enqueue(pTable);
			return true;
		}
		else
			return false;

	}
}

bool Restaurant::CancelOrder(int id) {
	
	Order* cancelledOVC = Pend_OVC.Cancel_Order(id); 
	Order* cancelledCook = Cook_orders.Cancel_Order(id); 
	Order* cancelledReady = Ready_OV.Cancel_Order(id);

	if (cancelledOVC) 
	{
		Cancelled_Orders.enqueue(cancelledOVC);
		CancelledOrders++;
		return true;
	}
	else if (cancelledReady)
	{ 
		Cancelled_Orders.enqueue(cancelledReady);  
		CancelledOrders++;
		return true;
	}
	else if (cancelledCook) 
	{
		Chef* assigned = cancelledCook->get_assigned_chef(); 
		ChefType type = assigned->gettype();  
		CancelledOrders++;  
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
void Restaurant::Load_from_Input_File(string filename)
{	
	char action_type,canshare;
	string type;
	int tq, id, size, price, no_of_seats, order_dur, distance;

	int nom_of_table_same_capacity,  capacity;


	ifstream infile;
	infile.open(filename);
	if (!infile.is_open())
		cout << "Error File name";
	//OverWaitTime
	else {
		infile >> numCN >> numCS >> SpeedCN >> SpeedCS
			>> numScooter >> ScooterSpeed >> BeforeMainOrders >> MainDur
			>> TotalTables;

		TotalChefs = numCN + numCS;
		int chef_id = 0;
		for (int i = 0; i < numCN; i++) {
			Chef* cHef = new Chef(SpeedCN, chef_id++);
			cHef->setType(CN);
			Free_CN.enqueue(cHef);
		}
		for (int i = 0; i < numCS; i++) {
			Chef* cHef = new Chef(SpeedCS, chef_id++);
			cHef->setType(CS);
			Free_CS.enqueue(cHef);
		}
		int Scooter_id = 0;
		for (int i = 0; i < numScooter; i++) {
			Scooter* sCooter = new Scooter(SpeedCN, Scooter_id++);
			Free_Scooters.enqueue(sCooter);
		}
		int count=0;
		int temp = 0;
		while (count < TotalTables) {
			infile >> nom_of_table_same_capacity >> capacity;
			count += nom_of_table_same_capacity;

				for (int i = 0; i < nom_of_table_same_capacity; i++) {
					Table* t = new Table(temp++, capacity);
					Free_Tables.enqueue(t);
				
				}
		}

		//infile >> OverWaitTime; // bonous
		count = 0;
		infile >> TotalOrders;
		while (count++ < TotalOrders) {
			infile >> action_type;
			if (action_type == 'Q') {

				infile >> type >> tq >> id >> size >> price;
				if (type == "ODG" || type=="ODN") {
					infile>>no_of_seats >> order_dur >> canshare;
					bool share;

					if (canshare == 'Y')
						share = true;
					else
						share = false;

					OrderType type1;
					if (type == "ODG")
						type1 = ODG;
					else
						type1 = ODN;

					Order* oRder = new OD(tq, id, size, price, no_of_seats, order_dur, share, type1); 
					Action* aCtion = new RequestAction(this,oRder); 
					aCtion->setTimeStep(tq);

					ActionList.enqueue(aCtion);

				}
				else if (type == "OVN" || type=="OVC" || type=="OVG") {

					infile >>distance;
					OrderType type1;
					if (type == "OVG")
						type1 = OVG;
					else if (type == "OVN")
						type1 = OVN;
					else
						type1 = OVC;

					Order* oRder = new OV(tq, id, size, price, distance, type1); 
					Action* aCtion = new RequestAction(this,oRder); 
					aCtion->setTimeStep(tq);

					ActionList.enqueue(aCtion);

				}
				else {

					Order* oRder = new OT(tq, id, size, price);
					Action* aCtion = new RequestAction(this,oRder); 
					aCtion->setTimeStep(tq);

					ActionList.enqueue(aCtion);
				}

	
			}
			else if(action_type=='X'){
			
				int tcancel; // cancellation timestep
				infile >> tcancel >> id;
				Action* aCtion = new CancelAction(this,id);
				aCtion->setTimeStep(tcancel);
				ActionList.enqueue(aCtion);


					

			
			}
		}
		



	}
}
Restaurant::~Restaurant()
{
	delete pUI;
}
