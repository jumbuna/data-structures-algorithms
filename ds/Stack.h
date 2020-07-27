#pragma once

#include "SinglyLinkedList.h"

namespace jumbuna {
template<class T, class A = Allocator<ListNode<T>, 256>>
class Stack {
	List<T> list;
	A allocator;
public:
	void push(T);
	T pop();
	T peek();
	std::size_t size();
	bool contains(T);
	bool empty();
	void clear();	
};
}
#include "StackImpl.h"