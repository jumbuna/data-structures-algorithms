#include "../ds/Vector.h"
#include <iostream>

int main() {
	Vector<int> vector{4};
	vector.push_back(10);
	vector.push_back(20);
	vector.push_back(30);
	vector.push_back(40);
	vector.push_back(50);
	vector.push_back(60);
	vector.push_back(70);
	vector.push_back(80);
	vector.push_back(90);
	vector.push_back(100);
	vector.push_back(900);
	vector.push_back(6600);
	vector.push_back(18700);
	vector.push_back(10970);
	
	for(int i = 0; i < vector.size(); i++) {
		std::cout << vector[i] << std::endl;
	}
	
	std::cout << vector.currentCapacity();
}