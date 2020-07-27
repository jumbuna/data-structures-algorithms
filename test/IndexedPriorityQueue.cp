#include "../ds/IndexedPriorityQueue.h"
#include <iostream>

int main() {
	PriorityQueue<char, int> pq;
	pq.push('a', 10);
	pq.push('b', 1);
	pq.push('y', 5);
	pq.push('h', 9);
	pq.push('a', 11);
	
	pq.update('y', 0);
	pq.remove('a');
	pq.remove('a');
	pq.decrementPriority('h', 0);
	while(pq.size() > 0) {
		std::cout << pq.pop() << std::endl;
	}
}