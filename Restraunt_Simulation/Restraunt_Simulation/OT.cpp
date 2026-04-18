#include"OT.h"
OT::OT(int tq, int id, int size, double price, int t_serve) :Order(tq, id, size, price, t_serve)
{
}
OrderType OT::gettype() const {
	return Type;
}
