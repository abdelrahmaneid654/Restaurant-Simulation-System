#pragma once
#include <iostream>
#include<fstream>
#include "UI.h"

#include "Action.h"
#include "Order.h"
#include "Chef.h"
#include "Scooter.h"
#include "Table.h"
#include"OT.h"
#include "Stack.h"
#include "Queue.h"
#include "PriQueue.h"
#include "Fit_Tables.h"//Derived from Priority Queue class
#include "Cooking_Orders.h" //Derived from Priority Queue class
#include "Pending_OVC.h"//Derived from Queue class
#include "RDY_OV.h"//Derived from Queue class

#include "EnumTypes.h"

class Action;
class UI;

class Restaurant
{ 
private:
	//Mode
	Mode RestaurantMode;

//POINTERS
	UI * pUI; // to reach and control the functions in UI class
//LISTS
	//Action List
	Queue <Action*> ActionList;//Action List

 
	Queue <Order*> Pend_ODG; 
	Queue <Order*> Pend_ODN;
	Queue <Order*> Pend_OT;
	Queue <Order*> Pend_OVN;
	Pending_OVC<Order*> Pend_OVC;
	PriQueue <Order*> Pend_OVG;
	//2-Ready Orders 
	Queue<Order*> Ready_OT;
	Queue<Order*> Ready_OD;
	RDY_OV<Order*> Ready_OV; 
	//3- Cooking, Cancelled, Finished dn InServ Orders 
	Cooking_Orders<Order*> Cook_orders;
	Queue <Order*> Cancelled_Orders;
	Stack <Order*> Finished_Orders;
	PriQueue <Order*> InServ;
	//4-Compo Orders
	PriQueue<Order*> Compo; 
	//Chefs
	  // 1-Free Chefs
	Queue <Chef*> Free_CS; //Free Special Chefs
	Queue <Chef*> Free_CN; //Free Normal Chefs
	
	//Scooters 
	PriQueue<Scooter*> Free_Scooters; 
	PriQueue<Scooter*> Back_Scooters; 
	Queue<Scooter*> Maint_Scooters;

	//Tables 
	Fit_Tables Free_Tables;
	Fit_Tables Busy_Sharable;
	Fit_Tables Busy_No_Share;

//Variables 
	int CurrTimeStep; 
	int numCN; 
	int numCS; 
	int numScooter;
	int MainDur; 
	int BeforeMainOrders;
	int ScooterSpeed;
	int SpeedCN;
	int SpeedCS;
	int OverWaitTime; 
		
	int TotalOrders;
	int OrdersOD;//Dine in orders
	int OrdersOT;//take away orders
	int OrdersOV;//delivery orders
	int FinishedOrders;
	int CancelledOrders;
	int OverWaitOrders;

	int TotalActions;
	int Action_Counter;

	int sumTI;
	int sumTC;
	int sumTserv;
	int sumTW;

	int BackScooters;
	int MaintScooters;

		//Chefs
	int TotalChefs;//TotalChefs = numCS + numCN
	int TotalTables;
	//numScooter
		//Busy Time
	int TotalChefsBusyTime;
	int TotalScootersBusyTime;

	//STILL I do not write the point 6 in the document num 1 page 6 



	//PRIVATE FUNCTIONS
private: 
	//Sequence Functions:
	Action* checkActions();

	void FromPendingToCooking();// khaled
	bool assignChefToOrderByType(Order* pOrder); // helper inside FromPendingToCooking

	void FromCookingToReady(); //khaled
	void addOrderToReadyByType(Order* pOrder); // helper fn inside FromCookingToReady
	void releaseChef(Order* pOrder); // helper fn inside FromCookingToReady

	void FromReadyToInServ();// khaled 

	void checkScootersList();
	bool assignTable(Order* o);
	
	bool AreAllOrdersFinishedOrCancelled();

public:
	// Declaration only: implementation must remain in Restaurant.cpp
	Restaurant();
	void AddToPending(Order* pOrder); //khaled , public to let RequestAction class access it

	void createOutputFile(string fileName);  

	void mainSimulation(); 

	
	bool CancelOrder(int id);
	
	bool AssignScooter(Order* p);
	
	
	void Check_Finished_Orders();
	void Check_Finished_Dine_in();
	void Check_Finished_Delivery();


	void UpdateInterface();
	//it is implemented only to pass the lists to the UI class1

	int GetCurrentTimestep() const;
	int getActionCounter() const;
	int getTotalActions() const;
	//Return the current time step need when execute actions .
	void FinalizeTakeAwayOrders();
	void setRestaurantMode(Mode m);
	bool Load_from_Input_File(string filename);
	int get_least_tq(int old_tq);

	~Restaurant();
};
