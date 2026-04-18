#include"Order.h"
ostream& operator<<(ostream& out, const Order* o) {

	if (o && o->get_assigned_chef()) {

		out << "[" << o->getID() << "," << o->get_assigned_chef()->getID() << "]";
	}
	return out;
}

Order::Order(int tq, int id, int size, double price, int t_serve)
{
	TQ = tq;
	ID = id;
	Size = size;
	Price = price;
	T_Serve = t_serve;
	assigned_Chef = nullptr;
	TA = 0;
	TR = 0;
	TS = 0;
	TF = 0;
}


Chef* Order::get_assigned_chef() const
{
	return assigned_Chef;
}



void Order::set_assigned_chef(Chef* c)
{
	assigned_Chef = c;
}

int Order::getsize() const
{
	return Size;
}

int Order::getID() const
{
	return ID;
}

int Order::getprice() const
{
	return Price;
}

int Order::get_TQ() const
{
	return TQ;
}

int Order::get_TA() const
{
	return TA;
}

void Order::set_TA(int ta)
{
	TA = ta;
}

int Order::get_TR() const
{
	return TR;
}

void Order::set_TR(int tr)
{
	TR = tr;
}

int Order::get_TS() const
{
	return TS;
}

void Order::set_TS(int ts)
{
	TS = ts;
}

int Order::get_TI() const
{
	return (TA - TQ) + (TS - TR);
}

int Order::get_TC() const
{
	return TR - TA;
}

int Order::get_TW() const
{
	return get_TI() + get_TC();
}


int Order::get_TF() const
{
	return TF;
}

void Order::set_TF(int tf)
{
	TF = tf;
}

int Order::get_T_Serve() const
{
	return T_Serve;
}

int Order::calc_priority() {
	return 0;
}
Order::~Order() {
	
}