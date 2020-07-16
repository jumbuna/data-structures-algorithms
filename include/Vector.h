#pragma once

#include "PoolAllocator.h"

//the passed allocator is actually not used
template<class T, class A = MemoryPool<T>>
class Vector {
	//access address of array block
	Pool<T> *memoryPool;
	//tracks the number of items in the array
	std::size_t currentIndex;
	//the maximum number of items the array can actually hold
	std::size_t capacity;
	//threshold above which a new block is allocated to house the array
	const double loadFactor;
	std::size_t threshold;
	//generate a new larger pool
	void newPool();
public:
	//constructor default capacity = 16
	Vector();
	//constructor user defined capacity
	Vector(std::size_t);
	//copy constructor
	Vector(Vector<T>&);
	//destructor
	~Vector();
	//add element to the array
	void push_back(T);
	//get index of element in the array or -1 if absent
	int indexOf(T);
	//access aray elements
	T& operator[](std::size_t);
	//return vector to initial state
	void clear();
	//free memory by returning unused memory back to the system
	void shrinkToFit(bool force = false);
	//search for and remove first instance of an element in the under-lying array
	void remove(T);
	//remove element at particular index
	void removeAt(std::size_t);
	//get size of the vector
	std::size_t size();
	//get the current capacity of the vector
	std::size_t currentCapacity();
	//TODO implement iterators for traversal using specialized for loop
};

#include "VectorImpl.h"
