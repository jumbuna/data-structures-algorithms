#include <iostream>
#include "../algs/sorting/BubbleSort.h"
#include "../algs/sorting/SelectionSort.h"
#include "../algs/sorting/InsertionSort.h"
#include "../algs/sorting/mergeSort.h"
#include <string>

using namespace std;
int main(int argc, char *argv[]) {
	int array[11] ;//= {1, 4, 65, 65, 34, 62, 98, 90, 2, 3, 7};
	for(int i = 1; i < argc; i++) {
		array[i-1] = std::stoi(std::string(argv[i]));
	}
//	selectionSort(array, 11);
//	bubbleSort(array, 11);
	//insertionSort(array, 11);
	mergeSort(array, 0, 10);
	for(int i = 0; i < 11; i++) {
		std::cout << array[i] << ", ";
	}
}