#pragma once
#include <algorithm>

namespace jumbuna {
template<class T>
void swap(T *array, int i, int j) {
	T temp = array[i];
	array[i] = array[j];
	array[j] = temp;
}

template<class T>
void heapify(T *array, int arraySize, int root, bool (*function) (T, T)) {
	//move small root value away from index 0
	int largest = root;
	int leftChild = 2*root+1;
	int rightChild = 2*root+2;
	if(leftChild < arraySize && function(array[leftChild], array[largest])) {
		largest = leftChild;
	}
	if(rightChild < arraySize && function(array[rightChild], array[largest])) {
		largest = rightChild;
	}
	if(largest != root) {
		swap(array, largest, root);
		heapify(array, arraySize, largest, function);
	}
}

template<class T>
void heapSort(T *array, int size, bool (*function) (T, T) = [](T i, T j) {
	return i > j;
}) {
	//build initial max heap
	//size/2-1 = index of last non-leaf node
	for(int i =size/2-1; i >= 0; i--) {
		heapify(array, size, i, function);
	}
	//reduce size of heap by 1 before every loop
	for(int i = size-1; i >= 0; i--) {
		//root which is now the largest element is 'removed' from the heap
		swap(array, 0, i);
		heapify(array, i, 0, function);
	}
}

}