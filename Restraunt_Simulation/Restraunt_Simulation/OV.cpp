#include"OV.h"
OV::OV(int tq, int id, int size, double price, int dis, int del_time,OrderType type) :Order(tq, id, size, price)
{
	distance = dis;
	assigned_scooter = nullptr;
	Type = type;
	delivery_time = del_time;
}

int OV::get_distance()
{
	return distance;
}


int OV::calc_priority(int z)
{

	if (z == 0)  // priority for Insev queue
		return get_TF();
	else if(z==2)
		return -1 * ((getsize() * getprice()) / get_distance()); // priority for pending ovg
	else if (z == 1) {
		return get_TR();  // priority for cooking orders
	}
	
}

int OV::get_delivery_time()
{
	return delivery_time;
}

void OV::set_dilvery_time(int t)
{
	delivery_time = t;
}

void OV::printInFile(ofstream& file)
{
	Order::printInFile(file);
	file << delivery_time << " ";
}



OrderType OV::gettype() const
{
	if (Type == OVG)
		return OVG;
	else if (Type == OVN)
		return OVN;
	else if (Type == OVC)
		return OVC;

	return UNKNOWN;
}

Scooter* OV::get_assigned_scooter()
{
	return assigned_scooter;
}

void OV::set_assigned_scooter(Scooter* s)
{
	assigned_scooter = s;
}
