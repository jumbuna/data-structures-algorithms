#include <iostream>
#include "../algs/sorting/BubbleSort.h"
#include "../algs/sorting/SelectionSort.h"
#include "../algs/sorting/InsertionSort.h"
#include "../algs/sorting/MergeSort.h"
#include "../algs/sorting/QuickSort.h"
#include "../algs/sorting/HeapSort.h"
#include "../algs/sorting/StoogeSort.h"
#include <string>

template<class T>
bool compare(T i, T j) {
	//descending order
	return i < j;
}

int main(int argc, char *argv[]) {
	char array[26] = {'r', 'c', 'u', 'v', 'b', 'm', 'o', 'z', 'p', 'w', 'e', 'f', 't', 'i', 'a', 'y', 's', 'd', 'g', 'h', 'j', 'l', 'n', 'q', 'k', 'x'};
//	for(int i = 1; i < argc; i++) {
//		array[i-1] = std::stoi(std::string(argv[i]));
//	}
//	jumbuna::selectionSort(array, 5, ::compare);
//	jumbuna::bubbleSort(array, 5, ::compare);
//	jumbuna::insertionSort(array, 5, ::compare);
//	jumbuna::mergeSort(array, 0, 25, ::compare);
//	jumbuna::quickSort(array, 0, 25, ::compare);
//	jumbuna::heapSort(array, 26, ::compare);
	jumbuna::stoogeSort(array, 0, 4, ::compare);
	for(int i = 0; i < 5; i++) {
		std::cout << array[i] << ", ";
	}
}