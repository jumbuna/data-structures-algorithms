#include "../ds/poolallocator.h"
#include <iostream>

int main() {
	Allocator<long> allocator;
	
	auto r = allocator.create(500);
	auto v = allocator.create(5005);
	auto x = allocator.create(5050);
	allocator.destroy(v);
	auto w = allocator.create(505550);
	
	
	std::cout << *v ;
}