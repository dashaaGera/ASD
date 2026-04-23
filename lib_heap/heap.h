#pragma once
#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>


template <class T>
class Heap {
	std::vector<T> _heap;
public:
	Heap() {};
	bool is_empty();
	void insert(const T& value);
	int size();
	T erase();

private:
	int parent(size_t i);
	int left(size_t i);
	int right(size_t i);
	T top();
	void sift_up(size_t i);
	void sift_down(size_t i);
	void swap(size_t i1, size_t i2);
};


template <class T>
bool Heap<T>::is_empty() {
	return _heap.empty();
}

template <class T>
int Heap<T>::size() {
	return _heap.size();
}

template <class T>
int Heap<T>::parent(size_t i) {
	return (i - 1) / 2;
}

template <class T>
int Heap<T>::left(size_t i) {
	return 2*i+1;
}


template <class T>
int Heap<T>::right(size_t i) {
	return 2*i + 2;
}

template <class T>
T Heap<T>::top() {
	if(is_empty())
		throw std::logic_error("Heap is empty");
	return _heap[0];
}

template <class T>
void Heap<T>::swap(size_t i1, size_t i2) {
	T tmp = _heap[i1];
	_heap[i1] = _heap[i2];
	_heap[i2] = tmp;
}

template <class T>
void Heap<T>::sift_up(size_t i) {
	while (i > 0 && _heap[i] < _heap[parent(i)]) {
		swap(i, parent(i));
		i = parent(i);
	}
}

template <class T>
void Heap<T>::sift_down(size_t i) {
	while (1) {
		int l = left(i);
		int r = right(i);
		int mini = std::min(l, r);
		if (l < _heap.size() && _heap[mini] < _heap[i]) {
			swap(i, mini);
			i = mini;
		}

		else {
			break;
		}

	}

}


template <class T>
void Heap<T>::insert(const T& value) {
	_heap.push_back(value);
	sift_up(_heap.size() - 1);
}

template <class T>
T Heap<T>::erase(){
	if (is_empty())
		throw std::logic_error("Heap is empty");
	T root = top();
	_heap[0] = _heap.back();
	_heap.pop_back();
	if (!is_empty()) {
		sift_down(0);
	}
	return root;
}