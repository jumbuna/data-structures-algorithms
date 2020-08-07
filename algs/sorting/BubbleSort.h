#pragma once

//quadratic time complexity
//constant space complexity

namespace jumbuna {
template<class T>
void bubbleSort(T *array, size_t arraySize, bool (*function) (T, T) = [](T i, T j) {
	return i > j;
}) {
	bool swapped = false;
	for(size_t i = 0; i < arraySize; i++) {
		for(size_t j = 0; j < arraySize-i; j++) {
			if(j+1 < arraySize) {
				if(function(array[j], array[j+1])) {
					T temp = array[j];
					array[j] = array[j+1];
					array[j+1] = temp;
					swapped = true;
				}
			}
		}
		if(!swapped) {
			break;
		}
	}
}
}
