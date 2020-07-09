#define __DEBUG
#include "../include/poolallocator.h"

int main() {
	allocator<long> allocator;
	
	auto r = allocator.create(500);
	
	std::cout << *r ;
}