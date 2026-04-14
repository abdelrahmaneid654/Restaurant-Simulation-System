#pragma once
#include"Node.h"
template<class T>

class Stack
{
	Node<T>* top;
public:
	Stack();
	bool peek(T& x);
	bool isempty();
	void push(T x);
	bool pop(T& x);
	void print();
	int getcount();
	~Stack();
};

