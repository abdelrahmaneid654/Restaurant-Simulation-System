#pragma once
#include "Order.h"
#include"Scooter.h"
enum OV_Type { // benfit of this in cooking orders all orders in same queue 
	OVC,
	OVG,
	OVN,
	UNKNOWN
};
class OV :public Order
{
	Scooter* assigned_scooter;
	int distance;
	OV_Type Type;
public:
	OV(int tq, int id, int size, double price, int t_serve,int distance, OV_Type type);
	int get_distance();
	int gettype();
	Scooter* get_assigned_scooter();
};

