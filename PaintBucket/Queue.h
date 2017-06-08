#pragma once

// Queue class template

#include "QNode.h"

template <typename T>
class Queue
{
public:
	Queue();
	Queue(T);
	Queue(const Queue<T> & otherQ);
	~Queue();
	Queue<T> & operator=(const Queue<T> & otherQ);

	void enQ(T);
	void deQ(T &);
	bool isEmpty();

	void dumpQueue(std::string);
	int getQueueCount();

private:
	QNode<T> *front, *back;
	static int queuect;
	QNode<T> *copyList(const QNode<T> * p) const;

};

template <typename T>
Queue <T>::Queue()
{
	front = NULL;
	back = NULL;
}

template <typename T>
Queue <T>::Queue(T x)
{
	QNode<T> *temp;
	temp = new QNode<T>(x);
	front = temp;
	back = temp;
	queuect = 1;
}

template <typename T>
Queue<T>::~Queue()
{
	QNode<T> *temp;
	while (front != NULL)
	{
		temp = front;
		front = front->next;
		delete temp;
	}
}

template <typename T>
QNode<T> *Queue<T>::copyList(const QNode<T> *p) const
{
	if (p == NULL)
	{
		return NULL;
	}
	else
	{
		QNode<T> *temp = new QNode<T>;
		temp->data = p->data;
		temp->next = copyList(p->next);
		return temp;
	}

}
template <typename T>
Queue<T>::Queue(const Queue<T> & otherQ)
{
	if (otherQ.front == NULL)
	{
		front = NULL;
		back = NULL;
		queuect = 0;
	}
	else
	{
		front = copyList(otherQ.front);
		back = front;
		queuect++;
		while (back->next != NULL)
		{
			back = back->next;
		}
	}
}

template <typename T>
Queue<T> & Queue<T>::operator=(const Queue<T> & otherQ)
{
	if (otherQ.front == NULL)
	{
		front = NULL;
		back = NULL;
		queuect = 0;
	}
	else
	{
		front = copyList(otherQ.front);
		back = front;
		queuect++;
		while (back->next != NULL)
		{
			back = back->next;
			queuect++;
		}
	}
	return (*this);
}


template <typename T>
void Queue <T>::enQ(T x)
{
	QNode<T> *temp;
	temp = new QNode<T>(x);
	if (!isEmpty())
	{
		back->next = temp;
		back = back->next;
	}
	else
	{
		front = temp;
		back = temp;
	}

}

template <typename T>
void Queue<T>::deQ(T &x)
{
	if (!isEmpty())
	{
		QNode<T> *temp;
		temp = front;
		x = temp->data;
		if (front == back)
		{
			delete front;

			front = NULL;
			back = NULL;
		}
		else
		{
			front = front->next;
			delete temp;
		}
	}

}

template <typename T>
bool Queue<T>::isEmpty()
{
	if (back == NULL && front == NULL)
		return true;
	else
		return false;
}

template <typename T>
int Queue<T>::getQueueCount()
{
	return queuect;
}

template <typename T>
void Queue<T>::dumpQueue(std::string msg)
{
	if (msg.length()>0)
		std::cout << msg << std::endl;

	QNode<T> *t = front;
	if (t == NULL)
		std::cout << "Queue is EMPTY" << std::endl;
	else
	{
		while (t != NULL)
		{
			std::cout << *(t->data->getFirst()) << "," << *(t->data->getSecond()) << std::endl;
			t = t->next;
		}
	}
}