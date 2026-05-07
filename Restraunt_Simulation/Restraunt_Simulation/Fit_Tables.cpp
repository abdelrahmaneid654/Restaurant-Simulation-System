#include"Fit_Tables.h"
#include"Node.h"
Table* Fit_Tables::getBest(OD* o)
{
	if (this->isempty()) return nullptr;

	Node<Table*>* temp = this->front;
	int order_seats = o->get_num_of_seats();

	if (order_seats <= this->front->getdata()->get_free_seats()) { // if front is best fit
		if (this->front == this->rear) // if there is only one table
			this->rear = nullptr;
		Table* target = temp->getdata();

		this->front = this->front->getnext();
		delete temp;
		return target;
	}


	while (temp->getnext()) {
		if (order_seats <= temp->getnext()->getdata()->get_free_seats()) {
			Node<Table*>* todelete = temp->getnext();
			if (todelete == this->rear)						// if best fit is rear node
				this->rear = temp;

			Table* target = todelete->getdata();
			temp->setnext(todelete->getnext());
			delete todelete;
			return target;

		}											// if you want to modify number of free tables don't chane it in priqueue as order destroyed you must dequeue and modify and enqueue
		temp = temp->getnext();
	}
	return nullptr;
}

void Fit_Tables::remove_table(Table* pTable)
{
	Node<Table*>*temp = this->front;

	if (!temp)
		return;

	if (pTable == front->getdata()) {			// check if fdeleted node is front
		if (pTable == rear->getdata())  // check if there is one node
			rear = NULL;

		front = front->getnext();
		return;
	}

	while (temp->getnext()) {
		if (temp->getnext()->getdata() == pTable) {
			if (pTable == rear->getdata()) {
				rear = temp;

			}
			Node<Table*>* deleted = temp->getnext();
			temp->setnext( deleted->getnext());
			delete deleted;
			break;
		}
		temp = temp->getnext();
	}


}
