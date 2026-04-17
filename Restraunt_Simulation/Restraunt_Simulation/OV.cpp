#include "OV.h"

OV::OV(int tq, int id, int size, double price, int t_serve, int dis, OV_Type type):Order(tq, id, size, price, t_serve)
{
	distance = dis;
	assigned_scooter = nullptr;
	Type = type;
}

int OV::get_distance()
{
	return distance;
}

string OV::gettype()
{
	if (Type == GRILLED)
		return "OVG";
	else if (Type == NORMAL)
		return "OVN";
	else if (Type == COLD)
		return "OVC";

		return "unknown";
}

Scooter* OV::get_assigned_scooter()
{
	return assigned_scooter;
}
