#include <iostream>
#include "../algs/sorting/BubbleSort.h"
#include "../algs/sorting/SelectionSort.h"
#include "../algs/sorting/InsertionSort.h"
#include "../algs/sorting/MergeSort.h"
#include "../algs/sorting/QuickSort.h"
#include <string>

int main(int argc, char *argv[]) {
	char array[26] = {'r', 'c', 'u', 'v', 'b', 'm', 'o', 'z', 'p', 'w', 'e', 'f', 't', 'i', 'a', 'y', 's', 'd', 'g', 'h', 'j', 'l', 'n', 'q', 'k', 'x'};
//	for(int i = 1; i < argc; i++) {
//		array[i-1] = std::stoi(std::string(argv[i]));
//	}
//	jumbuna::selectionSort(array, 11);
//	jumbuna::bubbleSort(array, 11);
//	jumbuna::insertionSort(array, 11);
//	jumbuna::mergeSort(array, 0, 25);
	jumbuna::quickSort(array, 0, 25);
	for(int i = 0; i < 26; i++) {
		std::cout << array[i] << ", ";
	}
}