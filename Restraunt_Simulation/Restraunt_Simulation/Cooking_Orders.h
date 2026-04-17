#pragma once
#include"OV.h"
#include"PriQueue.h"

class Cooking_Orders : public PriQueue<OV*>
{
public:
	OV* Cancel_Order(int id);
};

