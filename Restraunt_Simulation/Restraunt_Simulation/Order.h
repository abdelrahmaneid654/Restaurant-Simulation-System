#pragma once
#include<iostream>
#include"Chef.h"
using namespace std;


enum ORD_STATUS {
	PENDING,
	COOKING,
	READY,
	IN_SERVICE,
	FINISHED
};


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
	ORD_STATUS status;


public:
	Order(int tq, int id,int size,double price,int t_serve); //TQ ,T_Serve from input file // and T_serve differ if it's OD or OV
	void setStatus(ORD_STATUS s);
	ORD_STATUS getStatus() const;

	Chef* get_assigned_chef();
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

	virtual int gettype()  const = 0;

	virtual ~Order() {};

};
ostream& operator<<(ostream& out, const Order* o);


