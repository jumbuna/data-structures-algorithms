#include "Vector.h"
#include <memory>


template<class T, class A>
void Vector<T, A>::newPool() {
	//doublue the capacity
	capacity *= 2;
	//set new threshold based on the new capacity
	threshold = capacity * loadFactor;
	//allocate   new pool to haouse the array
	Pool<T> *newpool = new MemoryPool<T>;
	//since the actual memory is allocated after the first call to allocation
	//we set the number of chunks to be used durin the allocation
	newpool->numberOfChunks = capacity;
	//actual block allocation and poolAddress setting is done here
	newpool->allocate();
	//get the newly assigned pooladdres
	void *newpoolAddress = newpool->poolAddress;
	//move all contents from the old array to the new array(new pool address)
	//i could actually use currentIndex insead of capacity here since the objects are stored continuously
	std::memmove(newpoolAddress, memoryPool->poolAddress, capacity/2*sizeof(T));
	//free memory held by the now old array
	memoryPool->~Pool();
	//use new pool
	memoryPool = newpool;
}

template<class T, class A>
Vector<T, A>::Vector()
:Vector(16)
{}

template<class T, class A>
Vector<T, A>::Vector(std::size_t capacity)
:capacity(capacity), currentIndex(0), loadFactor(.75) {
	threshold = capacity * loadFactor;
	memoryPool = new MemoryPool<T>;
}

template<class T, class A>
Vector<T, A>::Vector(Vector<T>& other)
:loadFactor(0.75)
{
	memoryPool = new MemoryPool<T>;
	threshold = other.threshold;
	capacity = other.capacity;
	currentIndex = other.currentIndex;
	memoryPool->numberOfChunks = capacity;
	memoryPool->allocate();
	std::memcpy(memoryPool->poolAddress, other.memoryPool->poolAddress, capacity * sizeof(T));
}

template<class T, class A>
Vector<T, A>::~Vector() {
	//free allocated array memory
	memoryPool->~Pool();
}

template<class T, class A>
void Vector<T, A>::push_back(T element) {
	if(memoryPool->poolAddress == nullptr) {
		//this is the first push_back since memory is yet to be allocated
		memoryPool->numberOfChunks = capacity;
		memoryPool->allocate();
	}
	//poolAddress acts as array name :)
	memoryPool->poolAddress[currentIndex++] = element;
	if(currentIndex >= threshold) {
		//create a new pool
		newPool();
	}
}

template<class T, class A>
T& Vector<T, A>::operator[](std::size_t elementIndex) {
	//TODO implement a check to make sure given index is below the currentIndex
	return memoryPool->poolAddress[elementIndex];
}

template<class T, class A>
void Vector<T, A>::clear() {
//	memoryPool->reset();
	//start from begining of block again
	currentIndex = 0;
}

template<class T, class A>
void Vector<T, A>::shrinkToFit() {
	//TODO resize pool to currentIndex+1
}

template<class T, class A>
void Vector<T, A>::remove(T element) {
	std::size_t index = indexOf(element);
	if(index != -1) {
		--currentIndex;
		for(int i = index; i < currentIndex; i++) {
			//shift position by 1
			memoryPool->poolAddress[i] = memoryPool->poolAddress[i+1];
		}
	}
}

template<class T, class A>
void Vector<T, A>::removeAt(std::size_t index) {
	if(index < currentIndex) {
		--currentIndex;
		for(int i = index; i < currentIndex; i++) {
			memoryPool->poolAddress[i] = memoryPool->poolAddress[i+1];
		}
	}
}

template<class T, class A>
std::size_t Vector<T, A>::size() {
	//get the current index
	return currentIndex;
}

template<class T, class A>
std::size_t Vector<T, A>::currentCapacity() {
	//get current capacity
	return capacity;
}