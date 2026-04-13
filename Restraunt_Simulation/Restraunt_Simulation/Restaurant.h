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
#include "Cook_Order.h" //Derived from Priority Queue class
#include "Pending_OVC.h"//Derived from Queue class
#include "RDY_OV.h"//Derived from Queue class




template < typename  T>
class Restaurant
{
private:
	//Action List
	Queue <Action*> ActionListR;//Action List Request
	Queue <Action*> ActionListC;//Action List Cancellation

	// Orders 
	 //1- Pending Orders 
	Queue <Order*> Pend_ODG; //Dine in Grilled [need special chef CS and need of table]
	Queue <Order*> Pend_ODN;//Dine in Normal [need of table]
	Queue <Order*> Pend_OT;// Takeaway Orders [On site picked by the user ,do not need of scooters or tables]
	Queue <Order*> Pend_OVN;//Delivery Normal [Only need scooter] 
	Pending_OVC Pend_OVC;// Delivery cold [Only need scooter and to be deliverd cold]  {derived class from the queue} 
	PriQueue <Order*> Pend_OVG;// Delivery Grilled [ it needs a special chef CS and a scooter ]
	//2-Ready Orders 
	Queue<Order*> Ready_OT;
	Queue<Order*> Ready_OD;
	RDY_OV Ready_OV; //derived class from the queue 
	//3- Cooking, Cancelled, Finished dn InServ Orders 
	Cook_Order Cooking_orders; //Each cookin order points to the assigned chef
	Queue <Order*> Cancelled_Orders;
	Stack <Order*> Finished_Orders;
	PriQueue <Order*> InServ;//Each inserv order points to asssigned scooter [delivery] or table [dine in] 
	//4-Compo Orders
	PriQueue<Order*> Compo; //It needs 4 chefs at least 1 is CS and 2 scooters or more ,They have the highest priority over all the orders type 

	//Chefs
	  // 1-Free Chefs
	Queue <Chef*> Free_CS; //Free Special Chefs
	Queue <Chef*> Free_CN; //Free Normal Chefs

	//Scooters 
	PriQueue<Scooter*> Free_Scooters; //assigned based for the shortest distance
	PriQueue<Scooter*> Back_Scooters; //Leaves the list based on the distance they cut back to the restaurant
	Queue<Scooter*> Maint_Scooters; //scooters in the maintainance time ,they all have the same maintainance time

	//Tables 
	Fit_Tables Free_Tables;
	Fit_Tables Busy_Sharable;
	Fit_Tables Busy_No_Share;
public:
	Restaurant();

	void LoadFromFile();//Load From input file 
	void SaveToFile();//Save to Output file

	int TableStatus();
	//Check the status of the table fully available[for sharing and non_sharing tables] or partially available for [sharing tables]
	//[return num : 1--> partially available and I want to know the number of the free seats ,2--> fully available and I want to know the number of seats ,0--> not Available]
	void MoveOrderLists();
	//Move finished orders to “Finish” list and release the assigned scooter/table 
	// Assign pending orders to chefs 
	// Assign ready orders to scooter/table or give to customer (OT orders)
	void TakeOrder();
	//it takes the order data from the user [i/p file] and then add this order to the pending list 



	void UpdateInterface();
	//it is implemented only to pass the lists to the UI class1

	int GetCurrentTimestep() const;
	//Return the current time step need when execute actions .
	~Restaurant();
};

