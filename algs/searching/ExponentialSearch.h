#pragma once

#include "BinarySearch.h"

//works on sorted data
//out performs binary search when value may appear toward the beginning
//logarithmic time complexity
//constant space complexity

namespace jumbuna {
template<class T>
int exponentialSearch(T *array, T value, size_t arraySize, int begin = 0) {
	if(array[begin] != value) {
		int i = 1+begin;
		while(i < arraySize+begin && array[i] <= value) {
			i *= 2;
		}
		return reBinarySearch(array, value, i/2, i > arraySize+begin ? arraySize+begin : i);
	}
	return begin;
}
}