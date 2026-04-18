#pragma once
#include<iostream>
#include"OD.h"
class OD;
using namespace std;
class Table
{
	int Capacity;
	int ID;
	int free_seats;
	bool Is_sharable;
public:
	Table(int id, int cap);
	int get_ID()const;
	int get_capacity()const;
	int get_free_seats() const;
	bool get_Is_sharable() const;
	void set_IS_sharable(bool s);
	void put_order(OD *o);
	void  leave_order(int s);
	int calc_priority();
};
ostream& operator<<(ostream& out, const Table *t);