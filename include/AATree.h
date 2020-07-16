#pragma once

#include "PoolAllocator.h"
#include "BinarySearchTree.h"
#include "BinarySearchTreeUtilities.h"

template<class T>
struct AANode : BstNode<T> {
	AANode(T, BstNode<T> *);
	std::size_t level;
	AANode *getLeftChild();
	AANode *getRightChild();
	AANode *getParent();
};

template<class T, class C = std::greater<T>>
class AATree : public BinarySearchTree<T, C> {
	using Node = BstNode<T>;
	using aaNode = AANode<T>;
	Allocator<aaNode> nodeAllocator;
	bool leftHorizontalLinkExists(aaNode *);
	bool rightHorizontalLinkExists(aaNode *);
	void split(aaNode *);
	void skew(aaNode *);
	void insert(Node *, Node *, T);
	void remove(Node *, T);
	void updateLevel(aaNode *);
public:
	AATree(std::size_t = 128);
	virtual void insert(T) override;
	virtual void remove(T) override;
	virtual bool contains(T) override;
	virtual std::size_t size() override;
	virtual Vector<T> treeTraversal(TraversalOrder = IN_ORDER) override;
};

#include "AATreeImpl.h"
