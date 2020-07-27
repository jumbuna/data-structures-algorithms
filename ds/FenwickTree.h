#pragma once

#include "Vector.h"

//T must be of NumericType
//indexes start from 1

namespace jumbuna {
template<class T>
class FenwickTree {
	Vector<T> oldVector, newVector;
	T positionalSum(std::size_t);
	std::size_t leastSignificantBit(std::size_t);
public:
	FenwickTree(Vector<T>&);
	T rangeSum(std::size_t, std::size_t);
	void update(std::size_t, T);
};
}

#include "FenwickTreeImpl.h"