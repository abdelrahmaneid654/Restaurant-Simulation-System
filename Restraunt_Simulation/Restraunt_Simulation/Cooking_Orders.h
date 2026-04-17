#pragma once
#include"OV.h"
#include"PriQueue.h"
template<class T>
class Cooking_Orders : public PriQueue<T>
{
public:
	OV* Cancel_Order(int id);
};

