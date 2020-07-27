#include "IndexedPriorityQueue.h"

using namespace jumbuna;

template<class K, class P, class C>
void PriorityQueue<K, P, C>::swim(size_t i) {
	if(i > 0) {
		size_t parent = (i-1)/2;
		if(C{}(priorityArray[heap[i]], priorityArray[heap[parent]])) {
			swap(i, parent);
			swim(parent);
		}
	}
}

template<class K, class P, class C>
void PriorityQueue<K, P, C>::sink(size_t i) {
	if(i < heap.size()) {
		size_t leftIndex = i*2+1, rightIndex = i*2+2, swapIndex;
		if(leftIndex >= heap.size() && rightIndex >= heap.size()) {
			return;
		}else if(rightIndex >= heap.size()) {
			swapIndex = leftIndex;
		}else {
			swapIndex = C{}(priorityArray[heap[leftIndex]], priorityArray[heap[rightIndex]]) ? leftIndex : rightIndex;
		}
		if(!C{}(priorityArray[heap[i]], priorityArray[heap[swapIndex]])) {
			swap(i, swapIndex);
			sink(swapIndex);
		}
	}
}

template<class K, class P, class C>
void PriorityQueue<K, P, C>::swap(size_t i, size_t j) {
	positionalMap[heap[i]] = j;
	positionalMap[heap[j]] = i;
	size_t index = heap[i];
	heap[i] = heap[j];
	heap[j] = index;
}

template<class K, class P, class C>
void PriorityQueue<K, P, C>::push(K key, P priority) {
	priorityArray.push_back(priority);
	keyToIndex[key] = priorityArray.size()-1;
	indexToKey[priorityArray.size()-1] = key;
	positionalMap.push_back(priorityArray.size()-1);
	heap.push_back(priorityArray.size()-1);
	swim(heap.size()-1);
}

template<class K, class P, class C>
K PriorityQueue<K, P, C>::pop() {
	if(heap.size() == 0) {
		throw -1;
	}
	size_t ki = heap[0];
	heap[0] = heap[heap.size()-1];
	heap.removeAt(heap.size()-1);
	keyToIndex.remove(indexToKey[ki]);
	sink(0);
	return indexToKey[ki];
}

template<class K, class P, class C>
K PriorityQueue<K, P, C>::peek() {
	if(heap.size() == 0) {
		throw -1;
	}
	return indexToKey[heap[0]];
}

template<class K, class P, class C>
size_t PriorityQueue<K, P, C>::size() {
	return heap.size();
}

template<class K, class P, class C>
void PriorityQueue<K, P, C>::update(K key, P newPriority) {
	if(keyToIndex.contains(key)) {
		size_t keyIndex = keyToIndex[key];
		P oldPriority = priorityArray[keyIndex];
		priorityArray[keyIndex] = newPriority;
		if(C{}(newPriority, oldPriority)) {
			swim(positionalMap[keyIndex]);
		}else {
			sink(positionalMap[keyIndex]);
		}
	}
}

template<class K, class P, class C>
bool PriorityQueue<K, P, C>::incrementPriority(K key, P newPriority) {
	if(keyToIndex.contains(key)) {
		size_t keyIndex = keyToIndex[key];
		if(newPriority > priorityArray[keyIndex]) {
			P oldPriority = priorityArray[keyIndex];
			priorityArray[keyIndex] = newPriority;
			if(C{}(newPriority, oldPriority)) {
				swim(positionalMap[keyIndex]);
			}else {
				sink(positionalMap[keyIndex]);
			}
			return true;
		}
	}
	return false;
}

template<class K, class P, class C>
bool PriorityQueue<K, P, C>::decrementPriority(K key, P newPriority) {
	if(keyToIndex.contains(key)) {
		size_t keyIndex = keyToIndex[key];
		if(newPriority < priorityArray[keyIndex]) {
			P oldPriority = priorityArray[keyIndex];
			priorityArray[keyIndex] = newPriority;
			if(C{}(newPriority, oldPriority)) {
				swim(positionalMap[keyIndex]);
			}else {
				sink(positionalMap[keyIndex]);
			}
			return true;
		}
	}
	return false;
}


template<class K, class P, class C>
void PriorityQueue<K, P, C>::remove(K key) {
	if(keyToIndex.contains(key)) {
		size_t keyIndex = keyToIndex[key];
		heap[positionalMap[keyIndex]] = heap[heap.size()-1];
		heap.removeAt(heap.size()-1);
		sink(positionalMap[keyIndex]);
	}
}