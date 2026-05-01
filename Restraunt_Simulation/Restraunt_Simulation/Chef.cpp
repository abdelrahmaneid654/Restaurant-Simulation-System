#include"Chef.h"
Chef::Chef(int s, int id)
{
	ID = id;
	total_busy_time = 0;
	speed = s;
}

int Chef::getID() const
{
	return ID;
}

void Chef::update_info(int b_time)
{
	total_busy_time += b_time;
}
int Chef::getSpeed()
{
	return speed; 
}
void Chef::setType(ChefType s)
{
	type = s;
}
ChefType Chef::gettype() const
{
	return type;
}
ostream& operator<<(ostream& out, const Chef* c) {
	if (c) {
		out << c->getID();
	}
	return out;
}