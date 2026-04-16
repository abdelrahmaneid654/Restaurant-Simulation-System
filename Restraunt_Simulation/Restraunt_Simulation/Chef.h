#pragma once
#include<iostream>
using namespace std;
class Chef
{	
	int ID;
	int speed;
	int total_busy_time; // to calc Chefs utilization
public:
	Chef(int s, int id);

	int getID() const;
	int getspeed() const;
	void update_info(int b_time);
	virtual string gettype() const = 0;
	virtual~Chef() {};

};

ostream& operator<<(ostream& out, const Chef *c);