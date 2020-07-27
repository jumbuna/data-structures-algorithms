#include "../ds/BinaryHeap.h"
#include <iostream>

using namespace jumbuna;

int main() {
	BinaryHeap<int, std::greater<int>> heap;
	for(int i = 20; i > 0; i--) {
		heap.insert(i);
		heap.insert(i);
	}
	
	while(heap.size() > 0) {
		std::cout << heap.remove() << ",";
	}
}