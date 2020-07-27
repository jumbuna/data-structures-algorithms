#include "SinglyLinkedList.h"

template<class T>
ListNode<T>::ListNode(T element)
:data(element), nextNode(nullptr)
{}

template<class T, class allocator>
void List<T, allocator>::push_front(T element) {
	Node *node = alloc.create(element);
	if(head == nullptr) {
		head = tail = node;
	}else {
		node->nextNode = head;
		head = node;
	}
	++nodecount;
}

template<class T, class allocator>
void List<T, allocator>::push_back(T element) {
	Node *node = alloc.create(element);
	if(head == nullptr) {
		head = tail = node;
	}else {
		tail->nextNode = node;
		tail = node;
	}
	++nodecount;
}

template<class T, class allocator>
bool List<T, allocator>::contains(T element) {
	Node *node = head;
	while(node) {
		if(node->data == element) {
			return true;
		}
		node = node->nextNode;
	}
	return false;
}

template<class T, class allocator>
std::size_t List<T, allocator>::size() {
	return nodecount;
}

template<class T, class allocator>
bool List<T, allocator>::empty() {
	return size() == 0;
}

template<class T, class allocator>
void List<T, allocator>::clear() {
	alloc.reset();
	head = tail = nullptr;
	nodecount = 0;
}

template<class T, class allocator>
T List<T, allocator>::pop_front() {
	T data = head->data;
	Node *temp = head;
	head = head->nextNode;
	--nodecount;
	alloc.destroy(temp);
	return data;
}

template<class T, class allocator>
T List<T, allocator>::peek_front() {
	return head->data;
}