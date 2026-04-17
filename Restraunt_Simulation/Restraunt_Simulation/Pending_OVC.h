#pragma once
#include"Queue.h"
#include"Order.h"

template<class T>
class Pending_OVC : public Queue <T>
{
public:
	T Cancel_Order(int id);

};

