#pragma once
#include"Queue.h"
template<class T>
class RDY_OV :public Queue<T>
{
public:


	template<class T>
	T RDY_OV<T>::Cancel_Order(int id)
	{
		Node<T>* temp = this->front;
		if (!this->front) return nullptr;// if queue is empty

		if (this->front->getdata()->getID() == id) { // if order front of queue
			if (this->front == this->rear)
				this->rear = nullptr;  // if there is one order in queue 
			this->front = this->front->getnext();
			T deleted_order = temp->getdata();
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
				T deleted_order = todelete->getdata(); // to return pointer of order canceled
				delete todelete; // to delete node of canceled order
				return deleted_order;
			}
			temp = temp->getnext();
		}
		return nullptr;
	}
};