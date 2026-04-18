#pragma once
#include"Node.h"
template<class T>
class Queue
{
protected:
	Node<T>* front;
	Node<T>* rear;
public:

	Queue();
	bool peek(T& x);
	bool isempty();
	void enqueue(T x);
	void print() const;
	bool dequeue(T& x);
	int getcount() const;
};

template<class T>
Queue<T>::Queue()
{
	front = nullptr;
	rear = nullptr;
}
template<class T>
bool Queue<T>::peek(T& x)
{
	if (!isempty()) {
		x = front->getdata();
		return true;
	}
	return false;
}


template<class T>
bool Queue<T>::isempty()
{
	if (front == nullptr)
		return true;
	return false;
}

template<class T>
void Queue<T>::enqueue(T x)
{
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

template<class T>
bool Queue<T>::dequeue(T& x)
{
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

template<class T>
void Queue<T>::print() const
{
	Node<T>* temp = front;
	while (temp) {
		std::cout << temp->getdata() << " "; 
		temp = temp->getnext();
	}
	std::cout << "\n";
}

template<class T>
int Queue<T>::getcount() const {
	int count = 0;
	Node<T>* temp = front;
	while (temp) {
		count++;
		temp = temp->getnext();
	}
	return count;
}
