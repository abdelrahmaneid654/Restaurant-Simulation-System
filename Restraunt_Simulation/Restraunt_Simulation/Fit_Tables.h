#pragma once
#include"PriQueue.h"
#include"OD.h"
#include"Table.h"
template<class T>
class Fit_Tables:public PriQueue<Table*>
{
public:
	T getBest(OD*o);
};

