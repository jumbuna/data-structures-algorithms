#pragma once

#include "BinarySearchTreeNode.h"
#include "Vector.h"
#include "Queue.h"
#include "BinarySearchTreeTraversals.h"
#include <algorithm>

template<class T, class C = std::greater<T>>
class BinarySearchTree {
public:
	using Node = BstNode<T>;
	BinarySearchTree();
	Node *root;
	std::size_t nodeCount;
	C comparator;
	Node *leafSentinel;
	virtual void insert(T) = 0;
	virtual void remove(T) = 0;
	virtual bool contains(T)=0;
	virtual Vector<T> treeTraversal(TraversalOrder = IN_ORDER)=0;
	virtual std::size_t size() = 0;
	virtual void clear() = 0;
	virtual T getSmallestElement();
	virtual T getLargestElement();
};

template<class T, class C>
BinarySearchTree<T, C>::BinarySearchTree()
:root(nullptr), nodeCount(0), leafSentinel(nullptr)
{}

template<class T, class C>
T BinarySearchTree<T, C>::getSmallestElement() {
	Node *temp = root;
	while(temp->leftChild != leafSentinel) {
		temp = temp->leftChild;
	}
	return temp->element;
}

template<class T, class C>
T BinarySearchTree<T, C>::getLargestElement() {
	Node *temp = root;
	while(temp->rightChild != leafSentinel) {
		temp = temp->rightChild;
	}
	return temp->element;
}
