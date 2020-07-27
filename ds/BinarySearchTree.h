#pragma once

//base class for all binary tree

#include "BinarySearchTreeNode.h"
#include "Vector.h"
#include "Queue.h"
#include "BinarySearchTreeTraversals.h"
#include <algorithm>

namespace jumbuna {
template<class T, class C = std::greater<T>>
class BinarySearchTree {
public:
	using Node = BstNode<T>;
	BinarySearchTree();
	//pointer to node at top of tree
	Node *root;
	//number of nodes in the tree
	std::size_t nodeCount;
	C comparator;
	//value signifying end of the tree
	Node *leafSentinel;
	virtual void insert(T) = 0;
	virtual void remove(T) = 0;
	virtual bool contains(T)=0;
	virtual Vector<T> treeTraversal(TraversalOrder = IN_ORDER)=0;
	virtual std::size_t size() = 0;
	virtual void clear() = 0;
	//get element of left's left most node
	virtual T getSmallestElement();
	//get element of right's right most node
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

}
