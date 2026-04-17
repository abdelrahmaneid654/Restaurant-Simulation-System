#include "UI.h"
#include<iostream>
using namespace std;

UI::UI(Restaurant* p)
{
	pRes = p;
}

void UI::Print(Queue<Action*> ActionListR, Queue<Action*> ActionListC, Queue<Order*> Pend_ODG,
	Queue<Order*> Pend_ODN, Queue<Order*> Pend_OT, Queue<Order*> Pend_OVN, Pending_OVC<Order*> Pend_OVC,
	Queue<Order*> Pend_OVG, Queue<Order*> Ready_OT, Queue<Order*> Ready_OD, RDY_OV<Order*> Ready_OV,
	Cooking_Orders<Order*> Cooking_orders, Queue<Order*> Cancelled_Orders, Stack<Order*> Finished_Orders, 
	PriQueue<Order*> InServ, PriQueue<Order*> Compo, Queue<Chef*> Free_CS, Queue<Chef*> Free_CN,
	PriQueue<Scooter*> Free_Scooters, Queue<Scooter*> Maint_Scooters, PriQueue<Scooter*> Busy_Scooters,
	Fit_Tables Free_Tables, Fit_Tables Busy_Sharable, Fit_Tables Busy_No_Share)
{
	
	cout << "Current Time Step: " << pRes->GetCurrentTimestep() << endl;
	/*cout << "===================ACTIONS==================/n"; //not needed in this phase 
	cout << "Request Actions Remaining: " << ActionListR.getcount() << " :";
	ActionListR.print();
	cout << "Cancel Actions Reamining: " << ActionListC.getcount() << " :";
	ActionListC.print();*/
	cout << "/n=================Pending Orders IDs================/n";
	cout << Pend_ODG.getcount() << " " << "ODG ";
	Pend_ODG.print();
	cout << Pend_ODN.getcount() << " " << "ODN ";
	Pend_ODN.print();
	cout << Pend_OT.getcount() << " " << "OT ";
	Pend_OT.print();
	cout << Pend_OVN.getcount() << " " << "OVN ";
	Pend_OVN.print();
	cout << Pend_OVC.getcount() << " " << "OVC ";
	Pend_OVC.print();
	cout << Pend_OVG.getcount() << " " << "OVG ";
	Pend_OVG.print();
	cout << "/n=================Available Chefs IDs================/n";
	cout << Free_CS.getcount() << " " << "CS ";
	Free_CS.print();
	cout << Free_CN.getcount() << " " << "CN ";
	Free_CN.print();
	cout << "/n=================Cooking Orders [Orders ID, Chef ID]================/n";
	cout << Cooking_orders.getcount() << " ";
	Cooking_orders.print();
	cout << "/n=================Ready Orders IDs================/n";
	cout << Ready_OT.getcount()<< " " << "OT ";
	Ready_OT.print();
	cout << Ready_OD.getcount() << " " << "OD ";
	Ready_OD.print();
	cout << Ready_OV.getcount() << " " << "OV ";
	Ready_OV.print();
	cout << "/n=================Available Scooters IDs================/n";
	cout << Free_Scooters.getcount() << " ";
	Free_Scooters.print();
	cout << "/n=================Available Tables [ID, capacity, free seats]================/n";
	cout << Free_Tables.getcount() << " ";
	Free_Tables.print();
	cout << "/n=================In - Service Orders [order ID, scooter / Table ID]================/n";
	cout << InServ.getcount() << " ";
	InServ.print();
	cout << "/n=================In - maintainance scooters IDs================/n";
	cout << Maint_Scooters.getcount() << " ";
	Maint_Scooters.print();
	cout << "/n=================Scooters Back to Restaurant  IDs================/n";
	cout << Busy_Scooters.getcount();
	Busy_Scooters.print();
	cout << "/n=================Cancelled Orders IDs================/n";
	cout << Cancelled_Orders.getcount() << " ";
	Cancelled_Orders.print();
	cout << "/n=================Finished orders IDs================/n";
	cout << Finished_Orders.getcount() << " ";
	Finished_Orders.print();

	cout << endl << "Press Enter To Move To Next Step!/n";

}

void UI::chooseMode()
{
	cout << "========================/n";
	cout << "        SIMULATION/n";
	cout << "========================/n";
	int choice;
	cout << "Choose Simulation Mode: Silent - Interactive/n";
	cout << "(1) for Silent, (2) for Interactive: ";
	cin >> choice;
	switch (choice)
	{
	case 0:
		Mode m = Silent;
		setProgramMode(m);
		cout << "Done, Program is in Silent Mode/n";
		break;
	case 1:
		Mode m = Interactive;
		setProgramMode(m);
		cout << "Done, Program is in Interactive Mode/n";
		break;
	}
	cout << "/n";
}

void UI::setProgramMode(Mode m)
{
	pRes->setRestaurantMode(m);
}
