#pragma once

#include "BinarySearch.h"

//works on sorted data
//out performs binary search when value may appear toward the beginning
//logarithmic time complexity
//constant space complexity

namespace jumbuna {
template<class T>
int exponentialSearch(T *array, T value, size_t arraySize) {
	if(array[0] != value) {
		int i = 1;
		while(i < arraySize && array[i] <= value) {
			i *= 2;
		}
		return binarySearch(array, value, i/2, i > arraySize ? arraySize : i);
	}
	return 0;
}
}