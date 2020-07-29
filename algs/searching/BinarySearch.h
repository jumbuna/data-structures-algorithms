#pragma once

//assumption - array is already sorted

namespace jumbuna {
template<class T>
//iterative
int binarySearch(T *array, T value, size_t arraySize) {
	size_t begin = 0;
	size_t end = arraySize-1;
	size_t middle;
	while(begin < end) {
		middle = (begin + end)/2;
		if(array[middle] == value) {
			return middle;
		}
		if(array[middle] > value) {
			end = middle-1;
		}else {
			begin = middle+1;
		}
	}
	return array[begin] == value ? begin : -1;	
}

//recursive
template<class T>
int binarySearch(T *array, T &value, size_t begin, size_t end) {
	if(begin < end) {
		int midian = (begin + end)/2;
		if(array[midian] == value) {
			return midian;
		}
		if(array[midian] > value) {
			return binarySearch(array, value, begin, midian-1);
		}else {
			return binarySearch(array, value, midian+1, end);
		}
	}
	return array[begin] == value? begin : -1;
}

//recursive overload
template<class T>
int binarySearch(T *array, T &&value, size_t begin, size_t end) {
	return binarySearch(array, value, begin, end);
}

}