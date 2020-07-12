#include "../include/FenwickTree.h"
#include <iostream>

int main() {
	Vector<int> vector;
//	for(double i = 0; i < 10.0; i += .5) {
//		vector.push_back(i);
//	}
	vector.push_back(2);
	vector.push_back(8);
	vector.push_back(9);
	vector.push_back(6);
	vector.push_back(10);
	vector.push_back(45);
	vector.push_back(23);
	vector.push_back(16);
	FenwickTree<int> fenwick {vector};
	fenwick.update(5, 20);
	std::cout << fenwick.rangeSum(3, 8);
}