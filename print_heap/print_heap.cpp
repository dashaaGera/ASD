#include "../lib_heap/heap.h"
#include <iostream>
#include <stdexcept>
#include <vector>

int main() {
	std::vector<int> arr = { 42, 15, 73, 8, 91, 23, 56, 7, 34,15 };

	std::cout << "Array:  "<<std::endl;
	for (int x : arr) std::cout << x << " " << std::endl;

	Heap<int> heap;
	for (int x : arr) {
		heap.insert(x);
	}

	std::vector<int> sorted;
	while (!heap.is_empty()) {
		sorted.push_back(heap.erase());
	}

	std::cout << "Sorted array: "<<std::endl;
	for (int x : sorted) 
		std::cout << x << " "<<std::endl;


	return 0;
}