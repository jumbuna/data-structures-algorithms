#pragma once

#include "BinarySearchTree.h"
#include "BinarySearchTreeNode.h"
#include "BinarySearchTreeUtilities.h"

template<class T>
class UnbalancedBinarySearchTree: public BinarySearchTree<T> {
	using Node = BstNode<T>;
	Allocator<Node> nodeAllocator;
	void insert(Node *, Node *, T);
	void removeNode(Node *, T);
public:
	UnbalancedBinarySearchTree(std::size_t);
	UnbalancedBinarySearchTree();
	virtual void insert(T) override;
	virtual void remove(T) override;
	virtual bool contains(T) override;
	virtual std::size_t size() override;
	virtual Vector<T> treeTraversal(TraversalOrder = IN_ORDER) override;
};

#include "UnbalancedBinarySearchTreeImpl.h"