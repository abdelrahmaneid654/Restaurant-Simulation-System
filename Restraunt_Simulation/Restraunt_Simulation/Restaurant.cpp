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
	pUI = new UI(this);

}
/*template <typename T>
void Restaurant<T>::LoadFromFile()
{

}

template <typename T>
void Restaurant<T>::SaveToFile()
{

}

template <typename T>
void Restaurant<T>::TakeOrderInputFile()
{

}
*/

void Restaurant::MoveOrderLists()
{/*
 I Write this only to make the reader to understand the logic : we move from back to front [in the sequence of the order]
 so we start from Ready lists and put the orders in the finished lists and for each type : OV make all need implementations for 
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
		Busy_Scooters.enqueue(pScooter);
		//Time to return back:Time Travel is 2* distance/ScooterSpeed
		TravelTime = 2 * pOrder->distance / ScooterSpeed; 
		pScooter->SetReturnTime(CurrTimeStep + TravelTime);

		pOrder->SetFinishTime(CurrTimeStep + TravelTime);
		Finished_Orders.push(pOrder);

	}
	while (!Ready_OT.isempty)
	{
		Order* pOrder;
		Ready_OT.dequeue(pOrder);

		pOrder->SetFinishTime(CurrTimeStep);
		Finished_Orders.push(pOrder);

	}
/*
It is for Dine in Orders but Still not Finished
while (!Ready_OD.isempty())
	{
		Order* pOrder;
		Table* pTable;
		Ready_OD.dequeue(pOrder);
		bool ShareableFlag = pOrder->getFlag();
		bool TableFlag = pTable->getType();
		switch ShareableFlag
		{
		case 0: //Shareable Order
			

			break;

		case 1://Not Shareable Order

			break;
		}

	}*/
}
int Restaurant::GetCurrentTimestep() const
{
	return CurrTimeStep;
}

void Restaurant::UpdateInterface()
{
	//Don't forget that you didn't add any variable for point 6 
	//Joke :Cnrl C Cntrl V function
	pUI->Print(ActionListR, ActionListC, Pend_ODG, Pend_ODN, Pend_OT, Pend_OVN, Pend_OVC, Pend_OVG, Ready_OT, Ready_OD, Ready_OV, Cooking_orders, Cancelled_Orders, Finished_Orders, InServ, Compo, Free_CS, Free_CN, Free_Scooters,Maint_Scooters , Busy_Scooters,Free_Tables, Busy_Sharable, Busy_No_Share);
}

void Restaurant::RandomSimulation()
{

}


void Restaurant::setRestaurantMode(Mode m)
{
	RestaurantMode = m;
}

Restaurant::~Restaurant()
{
	delete pUI;

}