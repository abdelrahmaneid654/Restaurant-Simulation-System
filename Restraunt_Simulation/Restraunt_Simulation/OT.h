#pragma once
#include "Order.h"
class OT :public Order

{
	OrderType Type;
public:
	OT(int tq, int id, int size, double price, int t_serve);

	OrderType gettype() const;
};

