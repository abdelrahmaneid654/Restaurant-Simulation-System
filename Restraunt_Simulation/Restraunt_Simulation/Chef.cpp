#include "Chef.h"

Chef::Chef(int s,int id)
{	
	ID = id;
	speed = s;
	total_busy_time = 0;
}

int Chef::getID() const
{
	return ID;
}
int Chef::getspeed() const
{
	return speed;
}
void Chef::update_info(int b_time)
{
	total_busy_time += b_time;
}
void Chef::setType(OrderType s) 
{
	type = s;
}
OrderType Chef::gettype() const
{
	return type;
}
ostream& operator<<(ostream& out, const Chef* c) {
	if (c) {
		out << c->getID();
	}
	return out;
}



