#include "Scooter.h"

Scooter::Scooter(int s, int id, int m_o, int m_d)
{
	Speed = s;
	ID = id;
	Main_Ords = m_o;
	Main_Dur = m_d;
	counter = 0;
	total_dis = 0;
	total_busy_time = 0;
}

int Scooter::get_ID() const
{
	return ID;
}

int Scooter::get_counter() const
{
	return counter;
}

int Scooter::get_total_dis() const
{
	return total_dis;
}

int Scooter::get_total_btime() const
{
	return total_busy_time;
}

int Scooter::get_Speed() const
{
	return Speed;
}

int Scooter::get_Main_Ords() const
{
	return Main_Ords;
}

int Scooter::get_Main_Dur() const
{
	return Main_Dur;
}

void Scooter::update_info(int d,int b_time)
{
	counter++;
	total_dis += d;
	total_busy_time += b_time;
}

void Scooter::reset_counter()
{
	counter = 0;
}

void Scooter::set_return_time(int t)
{
	return_time = t;
}

int Scooter::get_return_time()
{
	return return_time;
}

int Scooter::calc_priority()
{
	return total_dis;
}

ostream& operator<<(ostream& out,const Scooter* s)
{
	if (s)
		out << s->get_ID();
	return out;
}
