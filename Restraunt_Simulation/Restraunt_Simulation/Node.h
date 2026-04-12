#pragma once
template<class T>

class Node
{
	T data;
	Node* next;
public:
	T getdata();
	void setdata(T x);
	Node<T>* getnext();
	void setnext(Node<T>*n);
		

		
};

