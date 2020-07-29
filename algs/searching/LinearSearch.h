#pragma once

namespace jumbuna {
template<class T>
int LinearSearch(T *array, T value, size_t arraySize, size_t begin = 0) {
	for(int i = begin; i < arraySize; i++) {
		if(array[i] == value) {
			return i;
		}
	}
	return -1;
}
}