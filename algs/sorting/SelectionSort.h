#pragma once

//quadratic time complexity
//constant space complexity

template<class T>
void selectionSort(T *array, size_t arraySize) {
	for(size_t i = 0; i < arraySize; i++) {
		size_t min = i;
		for(size_t j = i; j < arraySize; j++) {
			if(array[min] > array[j]) {
				min = j;
			}
		}
		if(min != i) {
			T temp = array[i];
			array[i] = array[min];
			array[min] = temp;
		}
	}
}