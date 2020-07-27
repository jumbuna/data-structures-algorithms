#include "../ds/Queue.h"
#include <iostream>

using namespace jumbuna;

int main() {
	Queue<char> queue;
	queue.push('a');
	queue.push('b');
	queue.push('c');
	queue.push('d');
	queue.push('e');
	
//	queue.clear();
	
	while(!queue.empty()) {
		std::cout << queue.peek();
		queue.pop();
	}
}