#pragma once
#include "Order.h"
#include "Table.h"

class OD : public Order
{
	Table* assigned_table;
	int num_of_seats;
	bool sharable;
	int duration;
	OrderType Type; 
	 
public:
	OD(int tq, int id, int size, double price, int t_serve, int seats, int dur, bool share, OrderType type); 
	OrderType gettype()  const;
	int get_num_of_seats();
	bool IS_Sharable();
	int get_duration();
	void set_assigned_table(Table* t);
	Table* get_assigned_table();
};

