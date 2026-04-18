#pragma once
#include<iostream>
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
	Node();
		
	Node(T x);

		
};

template<class T>
Node<T>* Node<T>::getnext()
{

	return next;
}
template<class T>
void Node<T>::setnext(Node<T>* n)
{
	next = n;

}

template<class T>
Node<T>::Node()
{
	next = nullptr;
}
template<class T>
Node<T>::Node(T x) {
	data = x;
	next = nullptr;
}

template<class T>
T Node<T>::getdata() {
	return data;
}

template<class T>
void Node<T>::setdata(T x)
{
	data = x;
}

