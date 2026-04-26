#include"Scooter.h"

Scooter::Scooter(int s, int id, int m_o, int m_d)
{
	Speed = s;
	ID = id;
	Main_Ords = m_o;
	Main_Dur = m_d;
	counter = 0;
	total_dis = 0;
	total_busy_time = 0;
	return_time = 0;
}
int Scooter::calc_priorityForFree() { 
	return total_dis;
}
int Scooter::calc_priorityForBack()
{
	return returningDistance; 
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

void Scooter::setTimeStepOfMaint(int t)
{
	timeStepOfMaint = t;
}

int Scooter::getTimeStepOfMaint()
{
	return timeStepOfMaint;
}

void Scooter::setReturnDistance(int d)
{
	returningDistance = d;
}

int Scooter::getReturnDistance()
{
	return returningDistance;
}

void Scooter::updateReturningDistance()
{
	if(returningDistance > 0)
		returningDistance -= Speed; 

	if (returningDistance < 0)
		returningDistance = 0;
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

void Scooter::update_info(int d, int b_time)
{
	counter++;
	total_dis += d;
	total_busy_time += b_time;
	returningDistance = d / 2;
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

ostream& operator<<(ostream& out, const Scooter* s)
{
	if (s)
		out << s->get_ID();
	return out;
}
