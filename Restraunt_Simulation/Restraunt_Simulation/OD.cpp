#include"OD.h"
#include "Table.h"
OD::OD(int tq, int id, int size, double price, int seats, int dur, bool share, OrderType type) :Order(tq, id, size, price)
{
    num_of_seats = seats;
    duration = dur;
    sharable = share;
    Type = type;
    assigned_table = nullptr;
}

OrderType OD::gettype() const
{
    if (Type == ODG)
        return ODG;
    else if (Type == ODN)
        return ODN;
    return UNKNOWN;
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

void OD::printInFile(ofstream& file)
{
    Order::printInFile(file);
    file << duration << " ";

}
