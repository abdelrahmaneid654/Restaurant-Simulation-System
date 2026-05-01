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
int Scooter::calc_priority(int z) {
	if(state == Free)
		return total_dis;
	else if(state == Back)
		return return_time;
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

void Scooter::setState(ScooterState s)
{
	state = s;
}

int Scooter::getReturnTime()
{
	return return_time;
}

int Scooter::get_Speed() const
{
	return Speed;
}


void Scooter::update_info(int d,int cuurent_timestep )
{
	counter++;
	total_dis += d*2;
	return_time= cuurent_timestep+(2*d/Speed);
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
