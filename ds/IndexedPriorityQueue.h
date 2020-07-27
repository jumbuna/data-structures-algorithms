#pragma once

#include "HashMap.h"
#include "Vector.h"

template<class K, class P, class C = std::less<P>>
class PriorityQueue {
	Map<K, size_t> keyToIndex{true};
	Map<size_t, K> indexToKey;
	Vector<size_t> positionalMap;
	Vector<size_t> heap;
	Vector<P> priorityArray;
	void swim(size_t);
	void sink(size_t);
	void swap(size_t, size_t);
	size_t currentIndex;
public:
	void push(K, P);
	K pop();
	K peek();
	void update(K, P);
	bool incrementPriority(K, P);
	bool decrementPriority(K, P);
	void remove(K);
	size_t size();
};

#include "IndexedPriorityQueueImpl.h"