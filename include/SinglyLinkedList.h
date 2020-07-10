#pragma once

/*
	minimal api for use in implementing of Queue & Stack
*/

#include "PoolAllocator.h"

template<class T>
struct ListNode {
	ListNode *nextNode;
	T data;
	ListNode(T);
};

template<class T, class allocator = Allocator<ListNode<T>, 256>>
class List {
	using Node = ListNode<T>;
	Node *head = nullptr, *tail = nullptr;
	std::size_t nodecount = 0;
public:
	allocator alloc;
	List() = default;
	~List() = default;
	void push_front(T);
	void push_back(T);
	//linear search
	bool contains(T);
	std::size_t size();
	bool empty();
	void clear();
	T pop_front();
	T peek_front();
};

#include "SinglyLinkedListImpl.h"