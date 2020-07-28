#pragma once

namespace jumbuna {
template<class T>
void stoogeSort(T *array, int start, int stop, bool (*function)(T, T) = [](T i, T j) {
	return i > j;
}) {
	if(function(array[start], array[stop])) {
		T temp = array[start];
		array[start] = array[stop];
		array[stop] = temp;
	}
	if(stop-start+1 > 2) {
		int tp = (stop-start+1)/3;
		stoogeSort(array, start, stop-tp, function);
		stoogeSort(array, start+tp, stop, function);
		stoogeSort(array, start, stop-tp, function);
	}
}
}