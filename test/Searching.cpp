#include <iostream>
#include "../algs/searching/BinarySearch.h"
#include "../algs/searching/LinearSearch.h"
#include "../algs/searching/ExponentialSearch.h"
#include "../algs/searching/JumpSearch.h"

using namespace std;
int main(int argc, char *argv[]) {
	int array[10] = {2, 5, 6, 9, 11, 45, 67, 88, 98, 101};
	
//	int w = jumbuna::LinearSearch(array, 6, 10);
//	//iterative
	//int x = jumbuna::itBinarySearch(array, 6, 2, 1);
//	//recursive
//	int y = jumbuna::binarySearch(array, 6, 0, 9);
	
//	std::cout << jumbuna::jumpSearch(array, 101, 1, 9);
	std::cout << jumbuna::exponentialSearch(array, 6, 1, 2);
	//std::cout << x;
}