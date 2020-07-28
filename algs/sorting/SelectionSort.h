#pragma once

//quadratic time complexity
//constant space complexity

namespace jumbuna {
template<class T>
void selectionSort(T *array, size_t arraySize, bool (*function) (T, T) = [](T i, T j) {
	return i > j;
}) {
	for(size_t i = 0; i < arraySize; i++) {
		size_t min = i;
		for(size_t j = i+1; j < arraySize; j++) {
			if(function(array[min], array[j])) {
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
}