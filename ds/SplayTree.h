#pragma once

#include "PoolAllocator.h"
#include "BinarySearchTree.h"
#include "BinarySearchTreeUtilities.h"

namespace jumbuna {
template<class T, class C = std::greater<T>>
class SplayTree : public BinarySearchTree<T, C> {
	using Node = BstNode<T>;
	Allocator<Node> nodeAllocator;
	void zigCase(Node *);
	void zigZagCase(Node *);
	void zigZigCase(Node *);
	void splay(Node *);
	bool find(T);
	void insert(Node *, Node *, T);
	void remove(Node *, T);
public:
	SplayTree(std::size_t = 128);
	virtual void insert(T) override;
	virtual void remove(T) override;
	virtual bool contains(T) override;
	virtual std::size_t size() override;
	virtual Vector<T> treeTraversal(TraversalOrder = IN_ORDER) override;
	virtual void clear() override;
};
}

#include "SplayTreeImpl.h"