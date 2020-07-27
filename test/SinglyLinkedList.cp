#include "../ds/SinglyLinkedList.h"
#include <iostream>

int main() {
	List<int> list;
	list.push_back(100);
	list.push_back(200);
	list.push_back(300);
	list.push_back(400);
	list.push_front(0);
	
	while(!list.empty()) {
		std::cout << list.pop_front() << std::endl;
	}
}