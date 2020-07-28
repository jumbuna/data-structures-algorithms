#pragma once

//linear logarithmic time complexity
//logarithmic space complexity
//quadratic time complexity in worst case

namespace jumbuna {
template<class T>
void quickSort(T *array, int start, int end,  bool (*function) (T, T) = [](T i, T j) {
	return i > j;
}) {
	if(start < end) {
		int pivot = end;
		for(int i=end-1; i >= start; i--) {
			if(function(array[i], array[pivot])) {
				T temp = array[i];
				array[i] = array[pivot-1];
				array[pivot-1] = array[pivot];
				array[pivot] = temp;
				pivot = pivot-1;
			}
		}
		quickSort(array, start, pivot-1, function);
		quickSort(array, pivot+1, end, function);
	}
}
}