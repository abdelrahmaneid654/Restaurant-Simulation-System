#include "OD.h"

OD::OD(int tq, int id, int size, double price, int t_serve,int seats, int dur, bool share, OD_TYPE type) :Order(tq,id,size,price,t_serve)
{
    num_of_seats = seats;
    duration = dur;
    sharable = share;
    Type = type;
    assigned_table = nullptr;
}

string OD::gettype() const
{
    if (Type == ODG)
        return "ODG";
    else if (Type == ODN)
        return "ODN";
    return "UNKNOWN";
}

int OD::get_num_of_seats()
{
    return num_of_seats;
}

bool OD::IS_Sharable()
{
    return sharable;
}

int OD::get_duration()
{
    return duration;
}

void OD::set_assigned_table(Table* t)
{
    assigned_table = t;
}

Table* OD::get_assigned_table()
{
    return assigned_table;
}
