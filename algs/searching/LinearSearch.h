#pragma once

//linear time complexity
//constant time complexity

namespace jumbuna {
template<class T>
int linearSearch(T *array, T value, size_t arraySize, size_t begin = 0) {
	for(int i = begin; i < begin+arraySize; i++) {
		if(array[i] == value) {
			return i;
		}
	}
	return -1;
}
}