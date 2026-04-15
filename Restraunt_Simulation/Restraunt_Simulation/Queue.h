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
	virtual void enqueue(T x);
	bool dequeue(T &x);
	void print();
	int getcount();
};

