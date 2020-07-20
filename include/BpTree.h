#pragma once

#include "PoolAllocator.h"
#include "BinarySearchTree.h"
#include "RedBlackTree.h"
#include "HashMap.h"
#include "Vector.h"
#include "Queue.h"
#include <algorithm>
#include <cmath>

template<class K, class V, class C, class B>
struct BpTreeNode {
	using Node = BpTreeNode<K, V, C, B>;
	BpTreeNode(Node *, size_t);
	struct nodePtrComparator {
		bool operator()(Node *, Node *);
	};
	Allocator<B> keyAllocator;
	Allocator<RedBlackTree<Node*, nodePtrComparator>> childrenAllocator;
	BinarySearchTree<K, C> &keys;
	BinarySearchTree<Node*, nodePtrComparator> &children;
	Map<K, V> data;
	Node *previousNode, *nextNode, *parent;
	void insertData(K, V);
	void removeKey(K);
};

template<class K, class V, class C, class B>
class Utility {
public:
	using Node = BpTreeNode<K, V, C, B>;
	static bool isLeaf(Node *);
	static bool isOverFlow(Node *, size_t);
	static bool isUnderFlow(Node *, size_t);
//	static K preOrderSuccessor(Node *);
	static Node *successorChild(Node *, K);
	static Node *findInternalKeyNode(Node *, K);
};

template<class K, class V, class C = std::greater<K>, class B = RedBlackTree<K, C>>
class BpTree {
	using Node = BpTreeNode<K, V, C, B>;
	using Util = Utility<K, V, C, B>;
	Allocator<Node> nodeAllocator;
	void borrowKeyFromLeftLeafNode(Node *, Node *);
	void borrowKeyFromRightLeafNode(Node *, Node *);
	void borrowKeyFromLeftInternalNode(Node *, Node *, K);
	void borrowKeyFromRightInternalNode(Node *, Node *, K);
	void mergeLeafNodes(Node *, Node *);
	void mergeInternalNodes(Node *, Node *, K);
	void postInsertLeafNode(Node *);
	void postInsertInternalNode(Node *);
	Node *postRemoveLeafNode(Node *);
	void postRemoveInternalNode(Node *);
	Node *leafNodeRemoveCaseOne(Node *, Vector<K> &, Vector<Node*> &);
	Node *leafNodeRemoveCaseTwo(Node *, Vector<K> &, Vector<Node*> &);
	Node *leafNodeRemoveCaseThree(Node *, Vector<K> &, Vector<Node*> &);
	void internalNodeRemoveCaseOne(Node *, Vector<K> &, Vector<Node*> &);
	void internalNodeRemoveCaseTwo(Node *, Vector<K> &, Vector<Node*> &);
	void internalNodeRemoveCaseThree(Node *, Vector<K> &, Vector<Node*> &);
	void insert(Node *, K, V);
	void remove(Node *, K);
	Node *root, *firstLeaf;
	size_t keyCount;
	size_t treeOrder;
public:
	BpTree(size_t = 5);
	void insert(K, V);
	void remove(K);
	bool contains(K);
	size_t size();
	Vector<K> treeTraversal(TraversalOrder = IN_ORDER);
	Vector<std::pair<K, V>> KeyValuePairs();
};

#include "BpTreeImpl.h"
