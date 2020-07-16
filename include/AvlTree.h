#pragma once

#include "PoolAllocator.h"
#include "BinarySearchTree.h"
#include "BinarySearchTreeUtilities.h"
#include <algorithm>

template<class T>
struct AvlNode: BstNode<T> {
	AvlNode(T, AvlNode *);
	int height, balanceFactor;
	AvlNode *getLeftChild();
	AvlNode *getRightChild();
	AvlNode *getParent();
};

template<class T, class C = std::greater<T>>
class AvlTree: public BinarySearchTree<T, C> {
	using AvlNode = AvlNode<T>;
	using Node = BstNode<T>;
	Allocator<AvlNode, 128> nodeAllocator;
	void insert(Node *, Node *, T);
	void remove(Node *, T);
	void updateBalanceFactor(AvlNode *);
	void balance(AvlNode *);
public:
	AvlTree();
	AvlTree(std::size_t);
	virtual void insert(T) override;
	virtual void remove(T) override;
	virtual bool contains(T) override;
	virtual std::size_t size() override;
	virtual Vector<T> treeTraversal(TraversalOrder = IN_ORDER) override;
};

#include "AvlTreeImpl.h"