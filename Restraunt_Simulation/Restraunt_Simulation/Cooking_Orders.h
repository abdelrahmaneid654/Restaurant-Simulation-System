#pragma once
#include"OV.h"
#include"PriQueue.h"
template<class T>
class Cooking_Orders : public PriQueue<T>
{
public:
	T Cancel_Order(int id);
	void print() const;
};


template<class T>
T Cooking_Orders<T>::Cancel_Order(int id) {
	Node<T>* temp = this->front;
	if (!this->front) return nullptr;						// if queue is empty

	if (this->front->getdata()->getID() == id) {			// if order front of queue
		if (this->front == this->rear)
			this->rear = nullptr;							// if there is one order in queue 
		this->front = this->front->getnext();
		T deleted_order = temp->getdata();
		delete temp;
		return deleted_order;
	}

	while (temp->getnext()) {
		if (temp->getnext()->getdata()->getID() == id) {
			Node<T>* todelete = temp->getnext();					// to delete node from heap

			if (temp->getnext() == this->rear) {
				this->rear = temp;
			}
			temp->setnext(temp->getnext()->getnext());


			T deleted_order = todelete->getdata();				 // to return pointer of order canceled
			delete todelete;								 // to delete node of canceled order
			return deleted_order;
		}
		temp = temp->getnext();
	}
	return nullptr;
}

template<class T>
inline void Cooking_Orders<T>::print() const
{
	Node<T>* temp = this->front;
	while (temp) {
		std::cout << temp->getdata() << " " <<temp->getdata()->get_assigned_chef();
		temp = temp->getnext();
	}
	std::cout << "\n";

}