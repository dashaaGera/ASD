#ifndef LIB_LIST_H_
#define LIB_LIST_H_

template <class T>
struct Node
{
	T value;
	Node<T>* next;
	Node(T value_=0, Node<T>* next_ = nullptr);

};

template <class T>
Node<T>::Node(T value_, Node<T>* next_) : value(value_), next(next_) {}

#endif 