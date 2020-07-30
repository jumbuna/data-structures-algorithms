#pragma once

#include "LinearSearch.h"
#include <cmath>

namespace jumbuna {
template<class T>
int jumpSearch(T *array, T value, size_t arraySize, int begin = 0) {
	int blockSize = sqrt(arraySize);
	int i = blockSize+begin;
	for(; i < arraySize+begin; i += blockSize) {
		if(array[i] > value) {
			return linearSearch(array, value, blockSize, i-blockSize);
		}
	}
	if(i-blockSize <= arraySize+begin-1) {
		i -= blockSize;
		return linearSearch(array, value, arraySize+begin-i, i);
	}
	return -1;
}
}