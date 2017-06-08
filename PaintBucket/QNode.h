#pragma once

// Queue node class template. Singly linked nodes.

template <typename T>
class QNode
{
public:
	QNode();
	QNode(T);

	T data;
	QNode *next;
};

template <typename T>
QNode<T>::QNode()
{
	next = NULL;
}

template <typename T>
QNode<T>::QNode(T x)
{
	data = x;
	next = NULL;
}