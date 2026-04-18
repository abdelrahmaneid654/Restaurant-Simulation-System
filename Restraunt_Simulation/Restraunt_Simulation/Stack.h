#pragma once
#include"Node.h"
template<class T>

class Stack
{
	Node<T>* top;
public:
	Stack() {
		top = nullptr;

	}
	bool peek(T& x) {
		if (!isempty()) {
			x = top->getdata();
			return true;
		}
		return false;
	}
	bool isempty() {
		if (top == nullptr)
			return true;
		return false;
	}
	void push(T x) {
		Node<T>* temp = new Node<T>;
		temp->setdata(x);
		temp->setnext(top);
		top = temp;
	}
	bool pop(T& x) {
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
	void print() {
		Node<T>* temp = top;
		while (temp) {
			std::cout << temp->getdata() << " ";
			temp = temp->getnext();
		}
	}
	int getcount() {
		int count = 0;
		Node<T>* temp = top;
		while (temp) {
			count++;
			temp = temp->getnext();
		}
		return count;
	}
	~Stack();
};

