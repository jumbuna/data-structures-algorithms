#include "../include/BinaryHeap.h"
#include <iostream>

int main() {
	BinaryHeap<int, /*std::greater<int>*/> heap;
	for(int i = 20; i > 0; i--) {
		heap.insert(i);
	}
	
	while(heap.size() > 0) {
		std::cout << heap.remove() << ",";
	}
}