#pragma once
#include <iostream>

#include "UI.h"

#include "Action.h"
#include "Order.h"
#include "Chef.h"
#include "Scooter.h"
#include "Table.h"

#include "Stack.h"
#include "Queue.h"
#include "PriQueue.h"
#include "Fit_Tables.h"//Derived from Priority Queue class
#include "Cooking_Orders.h" //Derived from Priority Queue class
#include "Pending_OVC.h"//Derived from Queue class
#include "RDY_OV.h"//Derived from Queue class
#include "EnumTypes.h"




class Restaurant
{ 
private:
	//Mode
	Mode RestaurantMode;

//POINTERS
	UI * pUI; // to reach and control the functions in UI class
//LISTS
	//Action List
	Queue <Action*> ActionListR;//Action List Request
	Queue <Action*> ActionListC;//Action List Cancellation

	// Orders 
	 //1- Pending Orders 
	Queue <Order*> Pend_ODG; //Dine in Grilled [need special chef CS and need of table]
	Queue <Order*> Pend_ODN;//Dine in Normal [need of table]
	Queue <Order*> Pend_OT;// Takeaway Orders [On site picked by the user ,do not need of scooters or tables]
	Queue <Order*> Pend_OVN;//Delivery Normal [Only need scooter] 
	Pending_OVC<Order*> Pend_OVC;// Delivery cold [Only need scooter and to be deliverd cold]  {derived class from the queue} 
	PriQueue <Order*> Pend_OVG;// Delivery Grilled [ it needs a special chef CS and a scooter ]
	//2-Ready Orders 
	Queue<Order*> Ready_OT;
	Queue<Order*> Ready_OD;
	RDY_OV Ready_OV; //derived class from the queue 
	//3- Cooking, Cancelled, Finished dn InServ Orders 
	Cooking_Orders<Order*> Cook_orders; //Each cookin order points to the assigned chef
	Queue <Order*> Cancelled_Orders;
	Stack <Order*> Finished_Orders;
	PriQueue <Order*> InServ;//Each inserv order points to asssigned scooter [delivery] or table [dine in] 
	//4-Compo Orders
	PriQueue<Order*> Compo; //It needs 4 chefs at least 1 is CS and 2 scooters or more ,They have the highest priority over all the orders type 

	//Chefs
	  // 1-Free Chefs
	Queue <Chef*> Free_CS; //Free Special Chefs
	Queue <Chef*> Free_CN; //Free Normal Chefs
	//I choose PriQueue for busy chefs because it has a relation to the time and we must know and implement to them the needed equations
	//I delete busy chefs because I will make the order points to the chef and before send order to finished List I will enqueue the chef to the list again.
	
	//Scooters 
	PriQueue<Scooter*> Free_Scooters; //assigned based for the shortest distance
	PriQueue<Scooter*> Busy_Scooters; //Leaves the list based on the distance they cut back to the restaurant
	Queue<Scooter*> Maint_Scooters; //scooters in the maintainance time ,they all have the same maintainance time

	//Tables 
	Fit_Tables Free_Tables;
	Fit_Tables Busy_Sharable;
	Fit_Tables Busy_No_Share;

//Variables 
	int CurrTimeStep; //Current time step to calculate all time needed to each order [action happened to this order]
	int numCN; //number of the normal chefs work in the restaurant [I need to ask teh TA about that]
	int numCS; //number of the special chefs work in the restaurant [I need to ask teh TA about that]
	int numScooter;//number of the scooters work in the restaurant [I need to ask teh TA about that]
	int mainDur; //Maintainance duration for each scooter
	int ScooterSpeed;
	int SpeedCN;
	int SpeedCS;
	int BeforeMainOrders; //Number of orders that the scooter take before it goes to the maintainace list
	int OverWaitTime; //over wait threshold [ It is made for even if the { current time - the TQ(Time request) > OverWaitTime } the order will be inc in priority it is speacial for the OVG orders
	//Statistics VAriables for the Output file 
		//Orders : Total number of orders and total number of each order type 
	int TotalOrders;
	int OrdersOD;//Dine in orders
	int OrdersOT;//take away orders
	int OrdersOV;//delivery orders
	int FinishedOrders;
	int CancelledOrders;
	int OverWaitOrders;
		//Chefs
	int TotalChefs;//TotalChefs = numCS + numCN
	//numScooter
	double FinishedOrderPercentage;//FinishedOrderPercentage = FinishedOrders / TotalOrders
	double CancelledOrderPercentage;// CancelledOrderPercentage = CancelledOrders / TotalOrders
	double OverWaitOrderPercentage; //OverWaitOrderPercentage = OverWaitOrders  / TotalOrders
		//Busy Time
	int TotalChefsBusyTime;//each time a one chef is busy this increment by one for a one chef 
	int TotalScootersBusyTime;//time of deliver the order and return back for a one scooter [ I need to ask TA about the maintainance time of scooters will inc this variable or not ]

	//STILL I do not write the point 6 in the document num 1 page 6 



	//PRIVATE FUNCTIONS
private: 
	//Sequence Functions:
	void AddToPending(Order* pOrder);//I made this to take the order type and put it in the specific list.
	Order* FromPendingToCookingByType(Order* pOrder);//////0
	Order* FromCookingToReadyByType(Order* pOrder);
	Order* FromReadyToInServByType(Order* pOrder);/////
	Order* FromInServToFinishedByType(Order* pOrder);///////
	void ReleaseResources(Order* pOrd);
	//Random Functions: 
	Order* CreateRandomOrder( int  ArrivalTime);
	Chef* CreateRandomChefs(int ChefID);
	Table* CreateRandomTables(int TableId);
	Chef* pickRandomChefs();
	Order* pickRandomOrderFromPendingLists();
	Order* pickRandomOrderFromReadyLists();
	Order* FromCookingToReadyByType(Order* pOrder);
	bool AreAllOrdersFinishedOrCancelled();

public:
	Restaurant();

	/* 
	Functions will be used in phase 2:
	void LoadFromFile();//Load From input file 
	void SaveToFile();//Save to Output file
	void TakeOrderInputFile();
	//it takes the order data from the user [i/p file] and then add this order to the pending list 
	*/
	bool CancelOrder(int id);
	
	void MoveOrderLists();
	//Move finished orders to “Finish” list and release the assigned scooter/table 
	// Assign pending orders to chefs 
	// Assign ready orders to scooter/table or give to customer (OT orders)
	void RandomSimulation();

	


	void UpdateInterface();
	//it is implemented only to pass the lists to the UI class1

	int GetCurrentTimestep() const;
	//Return the current time step need when execute actions .

	void setRestaurantMode(Mode m);

	~Restaurant();
};
