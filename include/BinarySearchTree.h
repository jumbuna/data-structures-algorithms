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
	virtual void insert(T) = 0;
	virtual void remove(T) = 0;
	virtual bool contains(T)=0;
	virtual Vector<T> treeTraversal(TraversalOrder = IN_ORDER)=0;
	virtual std::size_t size() = 0;
};

template<class T, class C>
BinarySearchTree<T, C>::BinarySearchTree()
:root(nullptr), nodeCount(0)
{}
