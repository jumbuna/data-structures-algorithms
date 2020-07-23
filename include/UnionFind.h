#pragma once


class UnionFind {
	int *array, *connectedElements;
	int root(int);
	int numberOfElements;
public:
	UnionFind(int);
	~UnionFind();
	void unionize(int, int);
	bool unionized(int, int);
};

#include "UnionFindImpl.h"