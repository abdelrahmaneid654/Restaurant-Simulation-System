#pragma once
#include<iostream>
#include"EnumTypes.h"
using namespace std;

class Scooter
{
	int Speed;
	int ID;
	int counter;
	int total_dis;
	int return_time;
	int timeStepOfMaint;
	int total_busy_time; // to calc Scooters utilization
	ScooterState state;
public:
	Scooter(int s, int id);

	int get_ID() const;
	int get_counter() const;
	int get_total_dis() const;
	int get_total_btime() const;

	void setTimeStepOfMaint(int t); // setted when counter == Main_Ord 
	int getTimeStepOfMaint();

	void setState(ScooterState s);
	int getReturnTime();

	int get_Speed() const;
	void update_info(int dis,int currtimestep); // used when a scooter is assigned, returning distance is setted here
	void reset_counter();
	int calc_priority(int z=0);

};
ostream& operator<<(ostream& out, const Scooter* s);

