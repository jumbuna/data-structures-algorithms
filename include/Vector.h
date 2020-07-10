#pragma once

#include "PoolAllocator.h"

template<class T, class A = MemoryPool<T>>
class Vector {
	Pool<T> *memoryPool;
	std::size_t currentIndex;
	std::size_t capacity;
	const double loadFactor;
	std::size_t threshold;
	void newPool();
public:
	Vector();
	Vector(std::size_t);
	~Vector();
	void push_back(T);
	std::size_t indexOf(T);
	T& operator[](std::size_t);
	void clear();
	void shrinkToFit();
	void remove(T);
	void removeAt(std::size_t);
	std::size_t size();
	std::size_t currentCapacity();
};

#include "VectorImpl.h"
