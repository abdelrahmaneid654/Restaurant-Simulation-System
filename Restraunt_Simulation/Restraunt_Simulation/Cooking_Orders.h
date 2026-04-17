#pragma once
#include"Order.h"
#include"PriQueue.h"
template<class T>
class Cooking_Orders : public PriQueue<Order*>
{
public:
	T Cancel_Order(int id);
};

