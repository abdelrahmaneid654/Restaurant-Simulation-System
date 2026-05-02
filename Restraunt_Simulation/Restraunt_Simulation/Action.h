#pragma once
#include<iostream>
using namespace std;

#include"Order.h"
#include "Restaurant.h" 

class Restaurant;
class Action
{
protected:
	int timeStep;
	Restaurant* pRes;  
	ActionType type;
public:
	Action(Restaurant* r,ActionType t); 
	virtual void Act() = 0;
	void setTimeStep(int t);
	int getTimeStep();
	ActionType gettype();
};
ostream& operator << (ostream & o, Action*p);
