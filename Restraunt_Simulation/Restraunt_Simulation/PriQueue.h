#pragma once
#include"Queue.h"
template<class T>
class PriQueue :public Queue<T>
{
public:
	void enqueue(T x);
};

