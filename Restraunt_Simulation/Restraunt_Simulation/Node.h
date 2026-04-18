#pragma once
#include<iostream>
template<class T>
class Node
{
	T data;
	Node* next;
public:
	T getdata() {
		return data;
	}
	void setdata(T x) {
		data = x;
	}
	Node<T>* getnext() {

		return next;
	}
	void setnext(Node<T>*n) {
		next = n;

	}
	Node() {
		next = nullptr;
	}
		
	Node(T x) {
		data = x;
		next = nullptr;
	}
		
};

