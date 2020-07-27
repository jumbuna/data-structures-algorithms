#pragma once

#include "PoolAllocator.h"
#include "Vector.h"
#include "BinarySearchTree.h"
#include "BinarySearchTreeUtilities.h"
#include "RedBlackTree.h"
#include <cmath>
#include <algorithm>

namespace jumbuna {
template<class T, class C, class B>
struct BtreeNode {
	using Node = BtreeNode<T, C, B>;
	BtreeNode(Node *, std::size_t);
	Allocator<B> nodeAllocator;
	struct NodePointerComparator {
		bool operator()(Node *, Node *);
	};
	Allocator<RedBlackTree<Node *, NodePointerComparator>> rbAllocator;
	BinarySearchTree<T, C> &keys;
	BinarySearchTree<Node *, NodePointerComparator> &children;
	Node *parent;
};

template<class T, class C, class B>
struct Utility {
	using Node = BtreeNode<T, C, B>;
	static bool isOverflow(Node *, std::size_t);
	static bool isUnderflow(Node *, std::size_t);
	static bool isLeaf(Node *);
	static Node *successorChild(Node *, T);
	static T preOrderSuccessor(Node *);
};


template<class T, class C = std::greater<T>, class B = RedBlackTree<T, C>>
class Btree {
	using Node = BtreeNode<T, C, B>;
	using Util = Utility<T, C, B>;
	Allocator<Node> nodeAllocator;
	void borrowKeyFromLeftSibling(Node *, Node *, T);
	void borrowKeyFromRightSibling(Node *, Node *, T);
	void mergeSiblings(Node *, Node *, T);
	void postInsertBalance(Node *);
	void postRemoveBalance(Node *);
	void insert(Node *, Node *, T);
	void remove(Node *, T);
	void removeCaseOne(Node *, Vector<T> &, Vector<Node*> &);
	void removeCaseTwo(Node *, Vector<T> &, Vector<Node*> &);
	void removeCaseThree(Node *, Vector<T> &, Vector<Node*> &);
	Node *root;
	std::size_t elementCount, treeOrder;
public:
	Btree(std::size_t = 5);
	void insert(T);
	void remove(T);
	bool contains(T);
	std::size_t size();
	Vector<T> treeTraversal(TraversalOrder = LEVEL_ORDER);
};

}

#include "BtreeImpl.h"