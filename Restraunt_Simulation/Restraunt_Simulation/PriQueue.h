#pragma once
#include"Queue.h"
template<class T>
class PriQueue :public Queue<T>
{
public:

	void enqueue(T x);

	
};

template<class T>
void PriQueue<T>::enqueue(T x) {
	Node<T>* trace = this->front;
	Node<T>* temp = new Node<T>;
	temp->setdata(x);
	temp->setnext(nullptr);
	if (x ) {
		if (!this->isempty()) {

			if (x->calc_priority() >= ((this->rear)->getdata())->calc_priority()) {
				this->rear->setnext(temp);
				this->rear = temp;
				return;
			}
			if (x->calc_priority() < ((this->front)->getdata())->calc_priority()) {
				temp->setnext(this->front);
				this->front = temp;
				return;
			}

			while (trace->getnext()) {

				if (x->calc_priority() < trace->getnext()->getdata()->calc_priority()) { // small number has highest priority
					temp->setnext(trace->getnext());
					trace->setnext(temp);
					return;
				}
				trace = trace->getnext();
			}
		}
		else {
			this->rear = temp;
			this->front = temp;
		}
	}
}