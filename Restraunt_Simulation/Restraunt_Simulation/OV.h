#pragma once
#include "Order.h"
#include"Scooter.h"

class OV :public Order
{
	Scooter* assigned_scooter;
	int distance;
	OrderType Type;
	int delivery_time;
public:
	OV(int tq, int id, int size, double price,int distance, OrderType type);
	int get_distance();
	OrderType gettype() const;
	Scooter* get_assigned_scooter();
	void set_assigned_scooter(Scooter *s);
	int calc_priority();
	int get_delivery_time();
	void set_dilvery_time(int t);

};


