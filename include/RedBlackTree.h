#pragma once

#include "PoolAllocator.h"
#include "BinarySearchTree.h"
#include "BinarySearchTreeUtilities.h"

enum Paint {
	RED, BLACK
};

template<class T>
struct RBNode: BstNode<T> {
	Paint color;
	RBNode();
	RBNode(T, BstNode<T> *, BstNode<T> *);
	RBNode *getLeftChild();
	RBNode *getRightChild();
	RBNode *getParent();
};

template<class T>
class RedBlackTree : public BinarySearchTree<T> {
	using Node = BstNode<T>;
	using RbNode = RBNode<T>;
	Allocator<RbNode> nodeAllocator;
	RbNode leafSentinel;
	void insert(Node *, Node *, T);
	void balance(RbNode *);
	void insertCaseOne(RbNode *);
	void insertCaseTwo(RbNode *);
	void insertCaseThree(RbNode *, RbNode *);
	void insertCaseFour(RbNode *, RbNode *);
	void remove(RbNode *, T);
	void deleteCaseOne(RbNode *);
	void deleteCaseTwo(RbNode *);
	void deleteCaseThree(RbNode *);
	void deleteCaseFour(RbNode *);
	void deleteCaseFive(RbNode *);
	void deleteCaseSix(RbNode *);
public:
	RedBlackTree(std::size_t = 128);
	virtual void insert(T) override;
	virtual void remove(T) override;
	virtual bool contains(T) override;
	virtual std::size_t size() override;
	virtual Vector<T> treeTraversal(TraversalOrder = IN_ORDER) override;
};

#include "RedBlackTreeImpl.h"