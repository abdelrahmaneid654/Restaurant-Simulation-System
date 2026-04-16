#pragma once
#include<iostream>
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
	void put_order(bool sharable, int s);
	void  leave_order(int s);
};
ostream& operator<<(ostream& out, const Table *t);
