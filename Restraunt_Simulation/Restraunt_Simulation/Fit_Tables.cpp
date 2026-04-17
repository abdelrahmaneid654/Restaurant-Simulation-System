#include "Fit_Tables.h"
template<class T>
inline T Fit_Tables<T>::getBest(Order* o)
{
	Node<T>* temp = front;
	int order_seats = o->get_num_ofseats();
	while (temp) {
		if(order_seats  <=  temp->getdata()->get_free_seats())
	}
}