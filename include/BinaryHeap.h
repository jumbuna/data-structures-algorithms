#pragma once

#include "Vector.h"
#include <algorithm>

template<class T, class compare = std::less<T>>
class BinaryHeap {
	Vector<T> vector {128};
	void swim(std::size_t);
	void sink(std::size_t);
	void swap(std::size_t, std::size_t);
	compare comparator;
public:
	void insert(T);
	T remove();
	bool contains(T);
	std::size_t size();
//	bool empty();
};

#include "BinaryHeapImpl.h"