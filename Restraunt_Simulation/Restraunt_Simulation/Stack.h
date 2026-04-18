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

template<class T>
Stack<T>::Stack() {
	top = nullptr;

}

template<class T>
bool Stack<T>::peek(T& x)
{
	if (!isempty()) {
		x = top->getdata();
		return true;
	}
	return false;
}
template<class T>
bool Stack<T>::isempty()
{
	if (top == nullptr)
		return true;
	return false;
}

template<class T>
void Stack<T>::push(T x)
{
	Node<T>* temp = new Node<T>;
	temp->setdata(x);
	temp->setnext(top);
	top = temp;
}

template<class T>
bool Stack<T>::pop(T& x)
{
	if (!isempty()) {
		Node<T>* temp;
		temp = top;
		x = top->getdata();
		top = top->getnext();
		temp->setnext(nullptr);
		delete temp;
		return true;
	}
	return false;
}

template<class T>
void Stack<T>::print()
{
	Node<T>* temp = top;
	while (temp) {
		std::cout << temp->getdata() << " ";
		temp = temp->getnext();
	}
}

template<class T>
int Stack<T>::getcount() {
	int count = 0;
	Node<T>* temp = top;
	while (temp) {
		count++;
		temp = temp->getnext();
	}
	return count;
}

template<class T>
Stack<T>::~Stack()
{
	T x;
	while (!isempty()) {
		pop(x);
	}
}


