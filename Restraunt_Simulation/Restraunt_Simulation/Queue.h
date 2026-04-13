#pragma once
#include"Node.h"
template<class T>
class Queue
{
	Node<T>* front;
	Node<T>* rear;
public:
	Queue();
	bool peek(T& x);
	bool isempty();
	void enqueue(T x);
	bool dequeue(T &x);
	void print();
	int getcount();
};

