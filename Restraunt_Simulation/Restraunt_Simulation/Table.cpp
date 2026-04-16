#include "Table.h"

Table::Table(int id, int cap)
{
	ID = id;
	Capacity = cap;
	free_seats = 0;
	Is_sharable = false;
}
int Table::get_ID() const
{
	return ID;
}
int Table::get_free_seats() const
{
	return free_seats;
}
int Table::get_capacity() const
{
	return Capacity;
}


bool Table::get_Is_sharable() const
{
	return Is_sharable;
}
void Table::put_order(bool sharable, int s)
{
	if (sharable)
		Is_sharable = true;
	free_seats -= s;
}

void Table::leave_order(int s)
{
	free_seats += s;
}

ostream& operator<<(ostream& out, const Table *t)
{
	if (t)
		out << t->get_ID();
	return out;
}
