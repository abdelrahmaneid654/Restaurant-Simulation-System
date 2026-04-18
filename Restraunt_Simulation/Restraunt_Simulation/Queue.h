#pragma once
#include"Node.h"
template<class T>
class Queue
{
protected:
	Node<T>* front;
	Node<T>* rear;
public:
	Queue() {
		front = nullptr;
		rear = nullptr;
	}
	bool peek(T& x) {
		if (!isempty()) {
			x = front->getdata();
			return true;
		}
		return false;
	}
	bool isempty() {
		if (front == nullptr)
			return true;
		return false;
	}
	virtual void enqueue(T x) {
		Node<T>* n_node = new Node<T>;
		n_node->setdata(x);
		n_node->setnext(nullptr);

		if (front == nullptr || rear == nullptr) {
			front = n_node;
			rear = n_node;
		}
		else {

			rear->setnext(n_node);
			rear = n_node;
		}
	}
	bool dequeue(T &x) {
		Node<T>* temp = front;

		if (!isempty()) {
			x = front->getdata();

			if (front == rear) {
				rear = nullptr;
			}
			front = front->getnext();
			delete temp;
			return true;
		}
		return false;
	}
	void print() {
		Node<T>* temp = front;
		while (temp) {
			std::cout << temp->getdata() << " ";
			temp = temp->getnext();
		}
	}
	int getcount() {
		int count = 0;
		Node<T>* temp = front;
		while (temp) {
			count++;
			temp = temp->getnext();
		}
		return count;
	}
};

