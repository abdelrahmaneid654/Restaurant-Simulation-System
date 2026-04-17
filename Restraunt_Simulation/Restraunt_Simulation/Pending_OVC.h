#pragma once
#include"Queue.h"
#include"OV.h"

template<class T>
class Pending_OVC : public Queue <OV*>
{
public:
	T Cancel_Order(int id);

};

