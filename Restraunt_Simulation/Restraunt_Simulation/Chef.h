#pragma once
#include<iostream>
#include"EnumTypes.h"
using namespace std;

class Chef
{	
	int ID;
	//int speed;
	int total_busy_time; // to calc Chefs utilization
	ChefType type; 
public:
	Chef(int s, int id);
	int getID() const;
	int getspeed() const;
	void update_info(int b_time);
	void setType(ChefType s);
	ChefType gettype() const;
	virtual~Chef() {};

};

ostream& operator<<(ostream& out, const Chef *c);


