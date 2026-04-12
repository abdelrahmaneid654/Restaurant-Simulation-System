#include "Node.h"
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
T Node<T>::getdata() {
	return data;
}

template<class T>
void Node<T>::setdata(T x)
{
	data = x;
}
