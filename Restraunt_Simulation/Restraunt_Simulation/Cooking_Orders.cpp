#include "Cooking_Orders.h"
template<class T>
T Cooking_Orders<T>::Cancel_Order(int id) {
	Node<T>* temp = this->front;
	if (!this->front) return;// if queue is empty

	if (this->front->getdata()->getID() == id) { // if order front of queue
		if (this->front == this->rear)
			this->rear = nullptr;  // if there is one order in queue 
		this->front = this->front->getnext();
		temp->getdata()->get_assigned_chef()->setstatus(AVAILABLE);
			T deleted_order =temp->getdata();
			delete temp;
			return deleted_order;
	}


	while (temp->getnext()) {
		if (temp->getnext()->getdata()->getID() == id) {
			Node<T>* todelete = temp->getnext(); // to delete node from heap

			if (temp->getnext() == this->rear) {
				this->rear = temp;
			}
			temp->setnext(temp->getnext()->getnext());

			todelete->getdata()->get_assigned_chef()->setstatus(AVAILABLE);
				T deleted_order =todelete->getdata() ; // to return pointer of order canceled
				delete todelete; // to delete node of canceled order
				return deleted_order;
		}
		temp = temp->getnext();
	}
	return nullptr;
}