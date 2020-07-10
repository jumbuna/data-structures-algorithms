#pragma once

#include "SinglyLinkedList.h"

template<class T, class A = Allocator<ListNode<T>, 256>>
class Queue {
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

#include "QueueImpl.h"