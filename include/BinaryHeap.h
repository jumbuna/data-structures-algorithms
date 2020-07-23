#pragma once

#include "Vector.h"
#include <algorithm>

template<class T, class compare = std::less<T>>
class BinaryHeap {
	Vector<T> vector {128};
	//root is vector[0]
	//move element towards root of heap
	void swim(std::size_t);
	//move element away from root of heap
	void sink(std::size_t);
	//swap element between given indexes
	void swap(std::size_t, std::size_t);
	compare comparator;
public:
	void insert(T);
	//remove root element from heap
	T remove();
	bool contains(T);
	std::size_t size();
//	bool empty();
};

#include "BinaryHeapImpl.h"