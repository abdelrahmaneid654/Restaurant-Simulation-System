#pragma once
#include "Order.h"
#include"Scooter.h"
enum OV_Type {
	COLD,
	GRILLED,
	NORMAL
};
class OV :public Order
{
	Scooter* assigned_scooter;
	int distance;
	OV_Type Type;
public:
	OV(int tq, int id, int size, double price, int t_serve,int distance, OV_Type type);
	int get_distance();
	string gettype();
	Scooter* get_assigned_scooter();
};

