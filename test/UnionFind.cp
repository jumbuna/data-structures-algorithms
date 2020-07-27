#include "../ds/UnionFind.h"
#include <iostream>

int main() {
	UnionFind find{20};
	find.unionize(2, 7);
	find.unionize(3, 7);
	find.unionize(10, 6);
	find.unionize(1, 8);
	find.unionize(2, 6);
	
	std::cout << find.unionized(4, 3);
	
}