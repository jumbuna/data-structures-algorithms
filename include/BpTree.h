#pragma once

//B+ tree

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
	//compare node pointers
	struct nodePtrComparator {
		bool operator()(Node *, Node *);
	};
	//allocator for Bst of keys
	Allocator<B> keyAllocator;
	//allocator for Bst of pointers
	Allocator<RedBlackTree<Node*, nodePtrComparator>> childrenAllocator;
	BinarySearchTree<K, C> &keys;
	BinarySearchTree<Node*, nodePtrComparator> &children;
	//hold values in leafnodes
	Map<K, V> data;
	Node *previousNode, *nextNode, *parent;
	//helper functions to manage keys&values in leaf nodes
	void insertData(K, V);
	void removeKey(K);
};

template<class K, class V, class C, class B>
class Utility {
	//helper functions
public:
	using Node = BpTreeNode<K, V, C, B>;
	static bool isLeaf(Node *);
	static bool isOverFlow(Node *, size_t);
	static bool isUnderFlow(Node *, size_t);
	//find next node where given key could be
	static Node *successorChild(Node *, K);
	//find internal node with key K
	static Node *findInternalKeyNode(Node *, K);
};

template<class K, class V, class C = std::greater<K>, class B = RedBlackTree<K, C>>
class BpTree {
	using Node = BpTreeNode<K, V, C, B>;
	using Util = Utility<K, V, C, B>;
	Allocator<Node> nodeAllocator;
	//leaf node operations
	void borrowKeyFromLeftLeafNode(Node *, Node *);
	void borrowKeyFromRightLeafNode(Node *, Node *);
	void mergeLeafNodes(Node *, Node *);
	void postInsertLeafNode(Node *);
	Node *postRemoveLeafNode(Node *);
	Node *leafNodeRemoveCaseOne(Node *, Vector<K> &, Vector<Node*> &);
	Node *leafNodeRemoveCaseTwo(Node *, Vector<K> &, Vector<Node*> &);
	Node *leafNodeRemoveCaseThree(Node *, Vector<K> &, Vector<Node*> &);
	//internal node operations
	void mergeInternalNodes(Node *, Node *, K);
	void borrowKeyFromRightInternalNode(Node *, Node *, K);
	void borrowKeyFromLeftInternalNode(Node *, Node *, K);
	void postInsertInternalNode(Node *);
	void postRemoveInternalNode(Node *);
	void internalNodeRemoveCaseOne(Node *, Vector<K> &, Vector<Node*> &);
	void internalNodeRemoveCaseTwo(Node *, Vector<K> &, Vector<Node*> &);
	void internalNodeRemoveCaseThree(Node *, Vector<K> &, Vector<Node*> &);
	//find leaf node to place key-value pair
	void insert(Node *, K, V);
	//remove key from leaf and internal node
	void remove(Node *, K);
	//pointer to top node and first leaf node
	Node *root, *firstLeaf;
	//number of keys inserted
	size_t keyCount;
	//order of the tree where order is the maximum branching factor of a node
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
