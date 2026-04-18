#pragma once
#include<iostream>
using namespace std;
class Scooter
{
	int Speed;
	int ID;
	int return_time;
	int Main_Ords;
	int	Main_Dur;
	int counter;
	int total_dis;
	int total_busy_time; // to calc Scooters utilization
public:
	Scooter(int s, int id, int m_o, int m_d);

	int get_ID() const;
	int get_counter() const;
	int get_total_dis() const;
	int get_total_btime() const;

	int get_Speed() const;
	int get_Main_Ords() const;
	int get_Main_Dur() const;
	void update_info(int dis,int b_time);
	void reset_counter();
	void set_return_time(int t);
	int get_return_time();
	int calc_priority();
};
ostream& operator<<(ostream& out, const Scooter* s);

