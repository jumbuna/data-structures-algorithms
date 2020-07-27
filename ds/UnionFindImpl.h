#include "UnionFind.h"

using namespace jumbuna;

int UnionFind::root(int index) {
	while(index != array[index]) {
		//path compression
		array[index] = array[array[index]];
		index = array[index];
	}
	return index;
}

UnionFind::UnionFind(int numberOfElements)
:numberOfElements(numberOfElements)
{
	array = new int[numberOfElements];
	connectedElements = new int[numberOfElements];
	for(int i = 0; i < numberOfElements; i++) {
		array[i] = i;
		connectedElements[i] = 1;
	}
}

UnionFind::~UnionFind() {
	delete[] array;
	delete[] connectedElements;
}

void UnionFind::unionize(int i, int j) {
	if(i >= numberOfElements || j >= numberOfElements){
		return;
	}
	int iRoot= root(i), jRoot = root(j);
	if(iRoot != jRoot) {
		if(connectedElements[iRoot] >= connectedElements[jRoot]) {
			array[jRoot] = iRoot;
			connectedElements[iRoot] += connectedElements[jRoot];
		}else {
			array[iRoot] = jRoot;
			connectedElements[jRoot] += connectedElements[iRoot];
		}
	}
}

bool UnionFind::unionized(int i, int j) {
	if(i >= numberOfElements || j >= numberOfElements){
			return false;
	}
	return root(i) == root(j);
}