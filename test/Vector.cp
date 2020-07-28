#include "../ds/Vector.h"
#include <iostream>

using namespace jumbuna;

int main() {
	Vector<int> vector{4};
	vector.push_back(10);
	vector.push_back(0);
	vector.push_back(30);
	vector.push_back(99);
	vector.push_back(55);
	vector.push_back(86);
	vector.push_back(77);
	vector.push_back(80);
	vector.push_back(90);
	vector.push_back(1);
	vector.push_back(9);
	vector.push_back(600);
	vector.push_back(800);
	vector.push_back(7);
	
	vector.sort();
	
	for(int i = 0; i < vector.size(); i++) {
		std::cout << vector[i] << std::endl;
	}
}