#pragma once

#include "BinarySearchTreeNode.h"
#include "Vector.h"
#include "Queue.h"
#include "BinarySearchTreeTraversals.h"

template<class T>
class BinarySearchTree {
public:
	using Node = BstNode<T>;
	BinarySearchTree();
	Node *root;
	std::size_t nodeCount;
	virtual void insert(T) = 0;
	virtual void remove(T) = 0;
	virtual bool contains(T)=0;
	virtual Vector<T> treeTraversal(TraversalOrder)=0;
	virtual std::size_t size() = 0;
};

template<class T>
BinarySearchTree<T>::BinarySearchTree()
:root(nullptr), nodeCount(0)
{}

//template<class T>
//bool BinarySearchTree<T>::contains(T element) {
//	return BstUtility<T>::contains(root, element);
//}
//
//template<class T>
//std::size_t BinarySearchTree<T>::size() {
//	return nodeCount;
//}
//
//template<class T>
//Vector<T> BinarySearchTree<T>::treeTraversal(TraversalOrder order) {
//	return BstUtility<T>::treeTraversal(root, order);
//}
