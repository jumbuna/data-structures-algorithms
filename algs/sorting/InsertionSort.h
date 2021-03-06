#pragma once
#include <memory>

//quadratic time complexity except for nearly sorted array where the time complexity can be reduced to linear
//constant space complexity
namespace jumbuna {
template<class T>
void insertionSort(T *array, size_t arraySize, bool (*function) (T, T) = [](T i, T j) {
	return i > j;
}) {
	for(int i = 1; i < arraySize; i++) {
		if(function(array[0], array[i])) {
			T temp = array[i];
			std::memmove(array+1, array, sizeof(T)*i);
			array[0] = temp;
		}else {
			int newPosition = i;
			for(int j = i-1; j > 0; j--) {
				if(function(array[j], array[i])) {
					newPosition = j;
				}else {
					break;
				}
			}
			if(newPosition != i) {
				T temp = array[i];
				std::memmove(array+newPosition+1, array+newPosition, sizeof(T)*(i-newPosition));
				array[newPosition] = temp;
			}
		}
	}
}
}