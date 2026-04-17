#include "Chef.h"

Chef::Chef(int s,int id)
{	
	ID = id;
	speed = s;
	total_busy_time = 0;
}
CHEF_STATUS Chef::getstatus()
{
	return status;
}
void Chef::setstatus(CHEF_STATUS s)
{
	status = s;
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
ostream& operator<<(ostream& out, const Chef* c) {
	if (c) {
		out << c->getID();
	}
	return out;
}



