#include"OV.h"
OV::OV(int tq, int id, int size, double price, int dis, OrderType type) :Order(tq, id, size, price)
{
	distance = dis;
	assigned_scooter = nullptr;
	Type = type;
	delivery_time = 0;
}

int OV::get_distance()
{
	return distance;
}


int OV::calc_priority()
{
	if (Type == ODG)
	return (getsize() * getprice()) / get_distance();
	else
		return 0;
}

int OV::get_delivery_time()
{
	return delivery_time;
}

void OV::set_dilvery_time(int t)
{
	delivery_time = t;
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
