#pragma once

#include "PoolAllocator.h"
#include "BinarySearchTree.h"
#include "BinarySearchTreeUtilities.h"
#include <algorithm>

namespace jumbuna {
template<class T>
struct AvlNode: BstNode<T> {
	AvlNode(T, AvlNode *);
	//balance the tree
	int height, balanceFactor;
	//helper functions to get pointers cast to AvlNode type
	AvlNode *getLeftChild();
	AvlNode *getRightChild();
	AvlNode *getParent();
};

template<class T, class C = std::greater<T>>
class AvlTree: public BinarySearchTree<T, C> {
	using AvlNode = AvlNode<T>;
	using Node = BstNode<T>;
	//allocator
	Allocator<AvlNode, 128> nodeAllocator;
	void insert(Node *, Node *, T);
	void remove(Node *, T);
	void updateBalanceFactor(AvlNode *);
	void balance(AvlNode *);
public:
	AvlTree(std::size_t = 128);
	virtual void insert(T) override;
	virtual void remove(T) override;
	virtual bool contains(T) override;
	virtual std::size_t size() override;
	virtual Vector<T> treeTraversal(TraversalOrder = IN_ORDER) override;
	virtual void clear() override;
};

}
#include "AvlTreeImpl.h"