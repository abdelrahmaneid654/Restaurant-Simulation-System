
#include <iostream>
#include <time.h>
#include "Restaurant.h"

	using namespace std;

	int main()
	{
		srand((int)time(NULL));

		cout << "Welcome to the Restaurant Simulation!" << endl;
		cout << "Starting Phase 1 Testing..." << endl;
		cout << "-----------------------------------" << endl;

		Restaurant* pRest = new Restaurant();

		pRest->RandomSimulation();

		delete pRest;

		cout << "-----------------------------------" << endl;
		cout << "Simulation Ended Successfully!" << endl;
		return 0;
	}

