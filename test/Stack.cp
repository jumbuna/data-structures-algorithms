#include "../ds/Stack.h"
#include <iostream>

using namespace jumbuna;

int main() {
	Stack<char> stack;
	stack.push('a');
	stack.push('b');
	stack.push('c');
	stack.push('d');
	stack.push('e');
	
//	stack.clear();
	
	while(!stack.empty()) {
		std::cout << stack.peek();
		stack.pop();
	}
}