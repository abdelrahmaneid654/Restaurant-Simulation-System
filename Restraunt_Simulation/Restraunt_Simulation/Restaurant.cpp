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
	////////////////////////////
	sumTI = 0;
	sumTC = 0;
	sumTserv=0;
	sumTW = 0;

	BackScooters = 0;
	MaintScooters = 0;
	//DON'T forget the point6 variables
	Restaurant* temp = this;
	pUI = new UI(temp);

}
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
Action* Restaurant::checkActions()
{
	Action* pAction;

	do
	{
		ActionList.peek(pAction);
		if (!pAction)
			return nullptr;

		if (pAction->getTimeStep() == CurrTimeStep)
		{
			ActionList.dequeue(pAction);
			pAction->Act();
			return pAction;
		}
	} while (pAction->getTimeStep() == CurrTimeStep);

	return nullptr;
}
void Restaurant::FromPendingToCooking()
{
	Order* pOrder; 

	Pend_ODG.peek(pOrder);
	if (pOrder)
	{
		assignChefToOrderByType(pOrder); 
		return;
	}

	Pend_ODN.peek(pOrder); 
	if (pOrder)
	{
		assignChefToOrderByType(pOrder);
		return;
	}

	Pend_OT.peek(pOrder);
	if (pOrder)
	{
		assignChefToOrderByType(pOrder);
		return;
	}

	Pend_OVG.peek(pOrder);
	if (pOrder)
	{
		assignChefToOrderByType(pOrder);
		return;
	}

	Pend_OVC.peek(pOrder);
	if (pOrder)
	{
		assignChefToOrderByType(pOrder);
		return;
	}

	Pend_OVN.peek(pOrder);
	if (pOrder)
	{
		assignChefToOrderByType(pOrder);
		return;
	}
}
void Restaurant::assignChefToOrderByType(Order* pOrder)
{ 
	if (!pOrder)
		return;
	/*
	 Pending Lists Name :
			Pend_ODG
			Pend_ODN
			Pend_OT
			Pend_OVN
			Pend_OVC
			Pend_OVG
	 */


	Chef* pChef;
	OrderType type = pOrder->gettype();
	switch (type)
	{
	case ODG:
	case OVG:
	{
		if (Free_CS.isempty())
			return;
		else
		{
			Free_CS.dequeue(pChef);
			if (type == ODG)
				Pend_ODG.dequeue(pOrder);
			else if (type == OVG)
				Pend_OVG.dequeue(pOrder); 
		}
	break;
	}
	case ODN:
	case OVC:
	{
		if (Free_CN.isempty())
		{
			if (Free_CS.isempty())
				return;
			else
			{
				Free_CS.dequeue(pChef);
			}
		}
		else
		{
			Free_CN.dequeue(pChef);
		}

		if (type == ODN)
			Pend_ODN.dequeue(pOrder);
		else if (type == OVC)
			Pend_OVC.dequeue(pOrder);
	break;
	}
	case OT_O:
	case OVN:
	{
		if (Free_CN.isempty())
			return; 
		else
		{
			Free_CN.dequeue(pChef);
			if (type == OT_O)
				Pend_OT.dequeue(pOrder);
			else if (type == OVN)
				Pend_OVN.dequeue(pOrder);
		}
	break;
	}
	default:
		return;
	}
	pOrder->set_assigned_chef(pChef); 
	pOrder->set_TA(CurrTimeStep);
	pOrder->set_TR(CurrTimeStep + pOrder->getsize() / pChef->getSpeed());

	//pChef->update_info(pOrder->get_TC());
	TotalChefsBusyTime += pOrder->get_TC(); 

	Cook_orders.enqueue(pOrder);

}
void Restaurant::FinalizeTakeAwayOrders()
{
	Order* pOrder;
	do
	{
		Ready_OT.peek(pOrder);
		if (!pOrder)
			return;
		if (CurrTimeStep >=(1+ pOrder->get_TR()))
		{
			Ready_OT.dequeue(pOrder);
			pOrder->set_TS(1 + pOrder->get_TR());
			pOrder->set_TF(CurrTimeStep); 
			Finished_Orders.push(pOrder);
		}
	} while (CurrTimeStep >= (1 + pOrder->get_TR()));

}
void Restaurant::createOutputFile(string fileName) 
{
	ofstream file(fileName); 

	if (file.is_open()) 
	{
		Order* pOrder = nullptr;
		Stack<Order*> temp; 

		Finished_Orders.printInFile(file); 

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

		file << "Average for Ti TC Tw Tserv for all finished orders " << sumTI / FinishedOrders << " " << sumTC / FinishedOrders << " " << sumTW / FinishedOrders << " " << sumTserv / FinishedOrders << endl;

		file << "Scooters utilization % " << TotalScootersBusyTime / (CurrTimeStep * numScooter) << endl;
		file << "Chefs utilization % " << TotalChefsBusyTime / (CurrTimeStep * TotalChefs) << endl;
	}

}
void Restaurant::mainSimulation()
{
	string fileName = pUI->getFileName(); 
	if (!Load_from_Input_File(fileName))
		return;

	Mode m = pUI->chooseMode();

	while(!AreAllOrdersFinishedOrCancelled())
	{

		checkActions(); // has Act inside it
		checkScootersList();
		Check_Finished_Orders();

		FromPendingToCooking();
		FromCookingToReady();
		FromReadyToInServ();

		if (m == Interactive)
		{
			UpdateInterface();
			pUI->WaitForClick(); 
		}

		
		CurrTimeStep++;
	}
	createOutputFile("Output.txt");
}
bool Restaurant::AreAllOrdersFinishedOrCancelled()
{
	if (ActionList.isempty()&&
		Pend_ODG.isempty() &&
		Pend_ODN.isempty() &&
		Pend_OT.isempty() &&
		Pend_OVN.isempty() &&
		Pend_OVC.isempty() &&//error because it is from derived class
		Pend_OVG.isempty() &&
		//Ready_OT.isempty() &&
		Ready_OD.isempty() &&
		Ready_OV.isempty() &&//error because it is from derived class
		Cook_orders.isempty() &&//error because it is from derived class
		InServ.isempty())
		return true;
	else
		return false;
}
void Restaurant::addOrderToReadyByType(Order* pOrder) 
{
	if (!pOrder)
		return;

	OrderType type = pOrder->gettype();
	switch (type) 
	{
	case ODG:
	case ODN: 
	{
		Ready_OD.enqueue(pOrder);
		break;
	}
	case OVG: 
	case OVN:
	case OVC:
	{
		Ready_OV.enqueue(pOrder); 
		break;
	}
	case OT_O:
	{
		Ready_OT.enqueue(pOrder); 
		break;
	}
	}
}
void Restaurant::FromCookingToReady()
{
	Order* pOrder;

	do
	{
		Cook_orders.peek(pOrder);
		if (!pOrder)
			break;

		if (CurrTimeStep == pOrder->get_TR())
		{
			Cook_orders.dequeue(pOrder);
			releaseChef(pOrder);
			addOrderToReadyByType(pOrder);
		}
	} while (CurrTimeStep == pOrder->get_TR());
}
void Restaurant::releaseChef(Order* pOrder)
{
	if (!pOrder)
		return;

	Chef* assignedChef = pOrder->get_assigned_chef();

	if (assignedChef)
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
		pOrder->set_assigned_chef(nullptr); 

	}
}
void Restaurant::FromReadyToInServ()
{
	Order* pOrder;

	do
	{
		Ready_OD.peek(pOrder);
		if (pOrder)
		{
			if (assignTable(pOrder))
			{
				Ready_OD.dequeue(pOrder);
				pOrder->set_TS(CurrTimeStep);
				pOrder->set_TF(CurrTimeStep + ((OD*)pOrder)->get_duration());
				InServ.enqueue(pOrder);
			}
			else
				break;
		}
	} while (pOrder); 

	do
	{
		Ready_OV.peekOVC(pOrder);
		if (pOrder)
		{
			if (AssignScooter(pOrder))
			{
				Ready_OV.dequeueOVC(pOrder);
				pOrder->set_TS(CurrTimeStep);
				pOrder->set_TF(CurrTimeStep + ((OV*)pOrder)->get_delivery_time());
				InServ.enqueue(pOrder);
			}
			else
				break;
		}
	} while (pOrder);

	do
	{
		Ready_OV.peek(pOrder);
		if (pOrder)
		{
			if (AssignScooter(pOrder))
			{
				Ready_OV.dequeue(pOrder);
				pOrder->set_TS(CurrTimeStep);
				pOrder->set_TF(CurrTimeStep + ((OV*)pOrder)->get_delivery_time());
				InServ.enqueue(pOrder);
			}
			else
				break;

		}
	} while (pOrder); 


	Ready_OT.peek(pOrder);
	while(pOrder){
		 
		Ready_OT.dequeue(pOrder);
		pOrder->set_TF(CurrTimeStep + 1);
		Ready_OT.enqueue(pOrder);
		Ready_OT.peek(pOrder);
	} 

}
bool Restaurant::AssignScooter(Order* p)
{
	if (!p)
		return false;

	Scooter* pScooter;
	Free_Scooters.peek(pScooter); 
	if(pScooter) 
	{
		Free_Scooters.dequeue(pScooter); 
		((OV*)p)->set_assigned_scooter(pScooter);
		pScooter->update_info(((OV*)p)->get_distance(), CurrTimeStep);
	}
}
void Restaurant::checkScootersList()
{
	Scooter* pScooter; 

	do
	{
		Maint_Scooters.peek(pScooter);

		if (!pScooter)
			break;

		if (MainDur == CurrTimeStep - pScooter->getTimeStepOfMaint())
		{
			Maint_Scooters.dequeue(pScooter);
			pScooter->setState(Free);
			Free_Scooters.enqueue(pScooter);
		}
	} while (MainDur == CurrTimeStep - pScooter->getTimeStepOfMaint());

	do
	{
		Back_Scooters.peek(pScooter);

		if (!pScooter)
			break;

		if (pScooter->getReturnTime() == CurrTimeStep)
		{
			Back_Scooters.dequeue(pScooter);

			if (BeforeMainOrders == pScooter->get_counter())
			{
				pScooter->setTimeStepOfMaint(CurrTimeStep);
				pScooter->setState(Maint);
				TotalScootersBusyTime += MainDur;
				Maint_Scooters.enqueue(pScooter);
				pScooter->reset_counter();
			}
			else
			{
				pScooter->setState(Free);
				Free_Scooters.enqueue(pScooter);
			}
		}
	} while (pScooter->getReturnTime() == CurrTimeStep);
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

	if (cancelledOVC) 
	{
		Cancelled_Orders.enqueue(cancelledOVC);
		CancelledOrders++;
		return true;
	}


	Order* cancelledReady = Ready_OV.Cancel_Order(id);
	 if (cancelledReady)
	{ 
		Cancelled_Orders.enqueue(cancelledReady);  
		CancelledOrders++;
		return true;
	}



	Order* cancelledCook = Cook_orders.Cancel_Order(id); 
	 if (cancelledCook) 
	{
		 Cancelled_Orders.enqueue(cancelledCook);

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
		TotalChefsBusyTime -= (cancelledCook->get_TR() - CurrTimeStep); // IMPORTANT
		return true;
	}
	return false;
}
void Restaurant::setRestaurantMode(Mode m)
{
	RestaurantMode = m;
}
void Restaurant::Check_Finished_Dine_in() {
	Order* finished;
	InServ.dequeue(finished);
	sumTI += finished->get_TI();
	sumTC += finished->get_TC();
	sumTserv += ((OD*)finished)->get_duration();
	sumTW += finished->get_TW();
	FinishedOrders++;


	Table* pTable = ((OD*)finished)->get_assigned_table();
	int seats = ((OD*)finished)->get_num_of_seats();

	
		if (((OD*)finished)->IS_Sharable()) {					// remove then modify then enqueue
			Busy_Sharable.remove_table(pTable);
			pTable->leave_order(seats);
			if (pTable->get_free_seats() == pTable->get_capacity()) {
				Free_Tables.enqueue(pTable);
				pTable->set_IS_sharable(Non_Sharable);
			}
			else
				Busy_Sharable.enqueue(pTable);

		}
		else {

			Busy_No_Share.remove_table(pTable);
			pTable->leave_order(seats);
			Free_Tables.enqueue(pTable);
			

		}

	
	((OD*)finished)->set_assigned_table(NULL);

	Finished_Orders.push(finished);

}
void Restaurant::Check_Finished_Delivery() {

	Order* finished;
	InServ.dequeue(finished);
	sumTI += finished->get_TI();
	sumTC += finished->get_TC();
	sumTserv += ((OV*)finished)->get_delivery_time();
	sumTW += finished->get_TW();
	FinishedOrders++;
	Scooter* sCooter = ((OV*)finished)->get_assigned_scooter();
	Back_Scooters.enqueue(sCooter);
	sCooter->setState(Back);
	((OV*)finished)->set_assigned_scooter(NULL);
	Finished_Orders.push(finished);



}
void Restaurant::Check_Finished_Orders() {
	Order* temp;


	do
	{
		InServ.peek(temp);
		if (!temp)
			break;

		if (temp->get_TF() == CurrTimeStep) {
			if (temp->gettype() == ODN || temp->gettype() == ODG)
					Check_Finished_Dine_in();
			else
					Check_Finished_Delivery();
		}
		
		} while (temp->get_TF() == CurrTimeStep);
	

}
bool Restaurant::Load_from_Input_File(string filename)
{	
	char action_type,canshare;
	string type;
	int tq, id, size, price, no_of_seats, order_dur, distance;

	int nom_of_table_same_capacity,  capacity;


	ifstream infile;
	infile.open(filename);
	if (!infile.is_open())
	{
		cout << "Error in File name\n";
		return false;
	}

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
			Scooter* sCooter = new Scooter(ScooterSpeed, Scooter_id++);
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
		infile >> TotalActions;
		while (count++ < TotalActions) {
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

					int delivery_time = distance / ScooterSpeed;

					Order* oRder = new OV(tq, id, size, price, distance, delivery_time, type1);
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
	return true;
}
Restaurant::~Restaurant()
{
	delete pUI;
}
