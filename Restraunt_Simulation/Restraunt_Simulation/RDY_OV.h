#pragma once
#include"Queue.h"
template<class T>
class RDY_OV :public Queue<T>
{
public:
	T Cancel_Order(int id);

};

