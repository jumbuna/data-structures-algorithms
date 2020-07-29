#include <iostream>
#include "../algs/searching/BinarySearch.h"
#include "../algs/searching/LinearSearch.h"

using namespace std;
int main(int argc, char *argv[]) {
	int array[10] = {2, 5, 6, 9, 11, 45, 67, 88, 98, 101};
	
	int w = jumbuna::LinearSearch(array, 6, 10);
	//recursive
	int x = jumbuna::binarySearch(array, 6, 10);
	//iterative
	int y = jumbuna::binarySearch(array, 6, 0, 9);
	
	std::cout << (x == y & x == w);
}