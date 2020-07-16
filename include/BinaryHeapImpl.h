#include "BinaryHeap.h"

template<class T, class compare>
void BinaryHeap<T, compare>::swim(std::size_t index) {
	int parent = (index-1)/2;
	if(parent >= 0) {
		if(comparator(vector[index], vector[parent])) {
			swap(index, parent);
			swim(parent);
		}
	}
}

template<class T, class compare>
void BinaryHeap<T, compare>::sink(std::size_t index) {
	int leftChild = 2*index+1, rightChild = 2*index+2, swapChild;
	if(rightChild < vector.size() || leftChild < vector.size()) {
		if(rightChild >= vector.size()) {
			swapChild = leftChild;
		}else {
			swapChild = comparator(vector[leftChild], vector[rightChild]) ? leftChild : rightChild;
		}
		if(comparator(vector[swapChild], vector[index])) {
			swap(index, swapChild);
			sink(swapChild);
		}
	}
}

template<class T, class compare>
void BinaryHeap<T, compare>::swap(std::size_t i, std::size_t j) {
	T iValue = vector[i];
	vector[i] = vector[j];
	vector[j] = iValue;
}

template<class T, class compare>
void BinaryHeap<T, compare>::insert(T element) {
	if(vector.indexOf(element) == -1) {
		vector.push_back(element);
		swim(vector.size()-1);
	}
}

template<class T, class compare>
T BinaryHeap<T, compare>::remove() {
	//get top most element
	if(vector.size() == 0) {
		throw std::out_of_range("ofr");
	}
	T element = vector[0];
	vector[0] = vector[vector.size()-1];
	vector.removeAt(vector.size()-1);
	sink(0);
	return element;
}

template<class T, class compare>
bool BinaryHeap<T, compare>::contains(T element) {
	return vector.indexOf(element) != -1;
}

template<class T, class compare>
std::size_t BinaryHeap<T, compare>::size() {
	return vector.size();
}