#include "FenwickTree.h"

using namespace jumbuna;

template<class T>
T FenwickTree<T>::positionalSum(std::size_t elementPosition) {
	T sum = 0;
	while(elementPosition > 0) {
		sum += newVector[elementPosition];
		elementPosition -= leastSignificantBit(elementPosition);
	}
	return sum;
}

template<class T>
std::size_t FenwickTree<T>::leastSignificantBit(std::size_t position) {
	return position & -position;
}

template<class T>
FenwickTree<T>::FenwickTree(Vector<T> &vector) {
	oldVector.push_back(0);
	newVector.push_back(0);
	for(std::size_t i = 0; i < vector.size(); i++) {
		oldVector.push_back(vector[i]);
		newVector.push_back(vector[i]);
	}
	
	oldVector.shrinkToFit(true);
	newVector.shrinkToFit(true);
	
	for(std::size_t i=1; i < newVector.size(); i++) {
		std::size_t parent = i + leastSignificantBit(i);
		if(parent < newVector.size()) {
			newVector[parent] += newVector[i];
		}
	}
}

template<class T>
T FenwickTree<T>::rangeSum(std::size_t begin, std::size_t end) {
	return positionalSum(end) - positionalSum(begin-1);
}

template<class T>
void FenwickTree<T>::update(std::size_t position, T newValue) {
	T increment = newValue - oldVector[position];
	oldVector[position] = newValue;
	while(position < newVector.size()) {
		newVector[position] += increment;
		position += leastSignificantBit(position);
	}
}