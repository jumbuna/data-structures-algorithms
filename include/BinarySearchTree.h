#pragma once

#include "PoolAllocator.h"
#include "Vector.h"
#include "Queue.h"

enum TraversalOrder {
	IN, POST, PRE, LEVEL
};

template<class T>
struct BstNode {
	BstNode(T);
	T element;
	BstNode *leftChild;
	BstNode *rightChild;
};

template<class T>
class BinarySearchTree {
	using Node = BstNode<T>;
	void insert(Node *&, Node *&, T&);
	void removeNode(Node *&, Node *&, T&);
	T& preOrderSuccessor(Node *&);
	Node *root;
	std::size_t nodeCount;
	Allocator<Node, 128> nodeAllocator;
	void inOrderTraversal(Node *, Vector<T> &);
	void postOrderTraversal(Node *, Vector<T> &);
	void preOrderTraversal(Node *, Vector<T> &);
	void levelOrderTraversal(Node *, Vector<T> &);
public:
	BinarySearchTree(std::size_t);
	BinarySearchTree();
	void insert(T);
	void remove(T);
	bool contains(T);
	std::size_t size();
	Vector<T> treeTraversal(TraversalOrder = IN);
};

#include "BinarySearchTreeImpl.h"