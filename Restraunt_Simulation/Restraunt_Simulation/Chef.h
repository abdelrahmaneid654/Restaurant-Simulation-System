#pragma once
#include<iostream>
using namespace std;
enum CHEF_STATUS {
	BUSY,
	AVAILABLE
};
class Chef
{	
	CHEF_STATUS status;
	int ID;
	int speed;
	int total_busy_time; // to calc Chefs utilization
public:
	Chef(int s, int id);

	CHEF_STATUS getstatus();
	void setstatus(CHEF_STATUS s);
	int getID() const;
	int getspeed() const;
	void update_info(int b_time);
	virtual string gettype() const = 0;
	virtual~Chef() {};

};

ostream& operator<<(ostream& out, const Chef *c);