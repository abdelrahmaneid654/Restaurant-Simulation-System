#pragma once
#include"OV.h"
#include"PriQueue.h"
template<class T>
class Cooking_Orders : public PriQueue<OV*>
{
public:
	T Cancel_Order(int id);
};

