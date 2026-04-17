#pragma once
#include"PriQueue.h"
#include"OD.h"
#include"Table.h"
class Fit_Tables:public PriQueue<Table*>
{
public:
	Table* getBest(OD*o);
};

