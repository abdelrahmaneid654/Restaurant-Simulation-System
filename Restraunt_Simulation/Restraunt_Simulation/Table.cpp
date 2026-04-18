#include "Table.h"

Table::Table(int id, int cap)
{
	ID = id;
	Capacity = cap;
	free_seats = cap;
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
void Table::set_IS_sharable(bool s)
{
	Is_sharable = s;
}
//void Table::put_order(OD*o)
//{
//	Table* temp = this;
//	o->set_assigned_table(temp);
//	free_seats -= o->get_num_of_seats();
//}

void Table::leave_order(int s)
{
	free_seats += s;
}

int Table::calc_priority()
{
	return free_seats;
}

ostream& operator<<(ostream& out, const Table* t)
{
	if (t)
		out << "[" << t->get_ID() << "," << t->get_capacity() << "," << t->get_free_seats() << "]";
	return out;
}
