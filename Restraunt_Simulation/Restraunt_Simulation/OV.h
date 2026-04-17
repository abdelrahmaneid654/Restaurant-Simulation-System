#pragma once
#include "Order.h"
#include"Scooter.h"

class OV :public Order
{
	Scooter* assigned_scooter;
	int distance;
	OrderType Type;
public:
	OV(int tq, int id, int size, double price, int t_serve,int distance, OrderType type);
	int get_distance();
	int gettype();
	Scooter* get_assigned_scooter();
	void set_assigned_scooter(Scooter *s);
};

