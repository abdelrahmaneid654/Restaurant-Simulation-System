#include"OT.h"
OT::OT(int tq, int id, int size, double price) :Order(tq, id, size, price)
{
	Type = OT_O;
}
OrderType OT::gettype() const {
	return Type;
}

void OT::printInFile(ofstream& file)
{
	Order::printInFile(file);
	file << "No Tserv" << " ";
}
