#pragma once
#include<iostream>
using namespace std;
class Order
{
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
public:
	Order(int tq, int id,int size,double price,int t_serve); //TQ ,T_Serve from input file // and T_serve differ if it's OD or OV


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

	virtual string gettype()  const = 0;

	virtual ~Order() {};

};
ostream& operator<<(ostream& out, const Order* o);


