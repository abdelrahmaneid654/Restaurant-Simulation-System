#pragma once
#include<iostream>
#include"EnumTypes.h"
using namespace std;

class Scooter
{
	int Speed;
	int ID;
	int Main_Ords;
	int	Main_Dur;
	int counter;
	int total_dis;
	int timeStepOfMaint;
	int returningDistance;
	int total_busy_time; // to calc Scooters utilization
	ScooterState state;
public:
	Scooter(int s, int id, int m_o, int m_d);

	int get_ID() const;
	int get_counter() const;
	int get_total_dis() const;
	int get_total_btime() const;

	void setTimeStepOfMaint(int t); // setted when counter == Main_Ord 
	int getTimeStepOfMaint();
	int getReturnDistance();

	void updateReturningDistance(); // just decrement the returning distance

	int get_Speed() const;
	int get_Main_Ords() const;
	int get_Main_Dur() const;
	void update_info(int dis,int b_time,ScooterState s); // used when a scooter is assigned, returning distance is setted here
	void reset_counter();
	int calc_priority();

};
ostream& operator<<(ostream& out, const Scooter* s);

