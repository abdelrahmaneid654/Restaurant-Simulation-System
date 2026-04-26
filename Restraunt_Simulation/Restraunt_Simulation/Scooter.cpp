#include"Scooter.h"

Scooter::Scooter(int s,int id)
{
	Speed = s;
	ID = id;
	counter = 0;
	total_dis = 0;
	total_busy_time = 0;
	state = Free;
}
int Scooter::calc_priority() {
	if(state == Free)
		return total_dis;
	else if(state == Back)
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

void Scooter::update_info(int d, int b_time, ScooterState s)
{
	counter++;
	total_dis += d;
	total_busy_time += b_time;
	returningDistance = d / 2;
	state = s;
}

void Scooter::reset_counter()
{
	counter = 0;
}



ostream& operator<<(ostream& out, const Scooter* s)
{
	if (s)
		out << s->get_ID();
	return out;
}
