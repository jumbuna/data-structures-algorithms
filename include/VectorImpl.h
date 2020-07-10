#include "Vector.h"
#include <memory>


template<class T, class A>
void Vector<T, A>::newPool() {
	capacity *= 2;
	threshold = capacity * loadFactor;
	Pool<T> *newpool = new MemoryPool<T>;
	newpool->numberOfChunks = capacity;
	newpool->allocate();
	void *newpoolAddress = newpool->poolAddress;
	std::memmove(newpoolAddress, memoryPool->poolAddress, capacity/2*sizeof(T));
	memoryPool->~Pool();
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
Vector<T, A>::~Vector() {
	memoryPool->~Pool();
}

template<class T, class A>
void Vector<T, A>::push_back(T element) {
	if(memoryPool->poolAddress == nullptr) {
		memoryPool->allocate();
	}
	memoryPool->poolAddress[currentIndex++] = element;
	if(currentIndex >= threshold) {
		newPool();
	}
}

template<class T, class A>
T& Vector<T, A>::operator[](std::size_t elementIndex) {
	return memoryPool->poolAddress[elementIndex];
}

template<class T, class A>
void Vector<T, A>::clear() {
	memoryPool->reset();
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
	return currentIndex;
}

template<class T, class A>
std::size_t Vector<T, A>::currentCapacity() {
	return capacity;
}