#pragma once
#include<iostream>
#include"Chef.h"
#include"EnumTypes.h"
using namespace std;


class Order
{
	Chef* assigned_Chef;
	int Size;
	int ID;
	double Price;
	int TQ;				//Order Request Time
	int TA;				//Assignment Time
	int TR;				//Ready Time
	int TS;				//Service Start Time
						//TI				//Order Idle Time
						//TC				//Order Cook Period
						//TW				//Customer Wait Time
	int TF;				//Order Finish Time
	int T_Serve;		// Service Duration
	OrderType Type;


public:
	Order(int tq, int id,int size,double price,int t_serve, OrderType t ); //TQ ,T_Serve from input file // and T_serve differ if it's OD or OV

	Chef* get_assigned_chef() const;
	void set_assigned_chef(Chef* c);

	

	int getsize() const;
	int getID() const;
	int getprice() const;


	int get_TQ() const;

	int get_TA()	const;
	void set_TA(int ta);

	int get_TR()	const;
	void set_TR(int tr);

	int get_TS()	const;
	void set_TS(int ts) ;

	int get_TI()	const;

	int get_TC()	const;

	int get_TW()	const;

	int get_TF()	const;
	void set_TF(int tf) ;

	int get_T_Serve() const;

	OrderType gettype()  const;

	virtual ~Order() = 0;

};
ostream& operator<<(ostream& out, const Order* o);


