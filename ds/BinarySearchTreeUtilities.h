#pragma once

//helper function to perform operations common to all BST

#include "BinarySearchTree.h"
#include "Vector.h"
#include "Queue.h"
#include "BinarySearchTreeTraversals.h"

namespace jumbuna {
template<class T,class C>
class BstUtility {
	using Node = BstNode<T>;
	static void inOrderTraversal(Node *, Vector<T> &, Node *);
	static void postOrderTraversal(Node *, Vector<T> &, Node *);
	static void preOrderTraversal(Node *, Vector<T> &, Node *);
	static void levelOrderTraversal(Node *, Vector<T> &, Node *);
	static void leftRotation(Node *, BinarySearchTree<T, C> *, Node *);
	static void rightRotation(Node *, BinarySearchTree<T, C> *, Node *);
public:
	//gateway to private traversal functions
	static Vector<T> treeTraversal(Node *, TraversalOrder, Node * = nullptr);
	static Node *contains(Node *, T, Node * = nullptr);
	static T preOrderSuccessor(Node *, Node * = nullptr);
	static T postOrderSuccessor(Node *, Node * = nullptr);
	//geteway to private rotation functions
	static void leftLeftCase(Node *, BinarySearchTree<T, C> *, Node * = nullptr);
	static void leftRightCase(Node *, BinarySearchTree<T, C> *, Node * = nullptr);
	static void rightRightCase(Node *, BinarySearchTree<T, C> *, Node * = nullptr);
	static void rightLeftCase(Node *, BinarySearchTree<T, C> *, Node * = nullptr);
	static C comparator;
};
}

using namespace jumbuna;

//same to that of the tree
template<class T, class C>
C BstUtility<T, C>::comparator = C{};

template<class T, class C>
Vector<T> BstUtility<T, C>::treeTraversal(Node *startingNode, TraversalOrder order, Node *leafSentinel) {
	Vector<T> vector {128};
	//tree/sub-tree is empty
	if(startingNode == leafSentinel) {
		return vector;
	}
	switch(order) {
		case IN_ORDER:
			BstUtility<T, C>::inOrderTraversal(startingNode, vector, leafSentinel);
			break;
		case POST_ORDER:
			BstUtility<T, C>::postOrderTraversal(startingNode, vector, leafSentinel);
			break;
		case PRE_ORDER:
			BstUtility<T, C>::preOrderTraversal(startingNode, vector, leafSentinel);
			break;
		case LEVEL_ORDER:
			BstUtility<T, C>::levelOrderTraversal(startingNode, vector, leafSentinel);
	}
	return vector;
}

template<class T, class C>
void BstUtility<T, C>::inOrderTraversal(Node *startingNode, Vector<T> &vector, Node *leafSentinel) {
	//sorted
	if(startingNode != leafSentinel) {
		inOrderTraversal(startingNode->leftChild, vector, leafSentinel);
		vector.push_back(startingNode->element);
		inOrderTraversal(startingNode->rightChild, vector, leafSentinel);
	}
}

template<class T, class C>
void BstUtility<T, C>::postOrderTraversal(Node *startingNode, Vector<T> &vector, Node *leafSentinel) {
	//DFS
	if(startingNode != leafSentinel) {
		inOrderTraversal(startingNode->leftChild, vector, leafSentinel);
		inOrderTraversal(startingNode->rightChild, vector, leafSentinel);
		vector.push_back(startingNode->element);
	}
}

template<class T, class C>
void BstUtility<T, C>::preOrderTraversal(Node *startingNode, Vector<T> &vector, Node *leafSentinel) {
	if(startingNode != leafSentinel) {
		vector.push_back(startingNode->element);
		inOrderTraversal(startingNode->leftChild, vector, leafSentinel);
		inOrderTraversal(startingNode->rightChild, vector, leafSentinel);
	}
}

template<class T, class C>
void BstUtility<T, C>::levelOrderTraversal(Node *startingtNode, Vector<T> &vector, Node *leafSentinel) {
	//BFS
	if(startingtNode != leafSentinel) {
		Queue<Node*> q;
		q.push(startingtNode);
		while(!q.empty()) {
			Node *temp = q.pop();
			if(temp->leftChild != leafSentinel) {
				q.push(temp->leftChild);
			}
			if(temp->rightChild != leafSentinel) {
				q.push(temp->rightChild);
			}
			vector.push_back(temp->element);
		}
	}	
}

template<class T, class C>
BstNode<T>* BstUtility<T, C>::contains(Node *startingNode, T element, Node *leafSentinel) {
	//binary search for node with given element
	if(startingNode != leafSentinel) {
		Node *temp = startingNode;
		while(temp != leafSentinel) {
			if(temp->element == element) {
				return temp;
			}
			if(BstUtility<T, C>::comparator(temp->element, element)) {
				temp = temp->leftChild;
			}else {
				temp = temp->rightChild;
			}
		}
	}
	return leafSentinel;
}

template<class T, class C>
T BstUtility<T, C>::preOrderSuccessor(Node *startingNode, Node *leafSentinel) {
	//right most element in left subtree
	while(startingNode->rightChild != leafSentinel) {
		startingNode = startingNode->rightChild;
	}
	return startingNode->element;
}

template<class T, class C>
T BstUtility<T, C>::postOrderSuccessor(Node *startingNode, Node *leafSentinel) {
	//left most element in right subtree
	while(startingNode->leftChild != leafSentinel) {
		startingNode = startingNode->leftChild;
	}
	return startingNode->element;
}

template<class T, class C>
void BstUtility<T, C>::leftRotation(Node *candidate, BinarySearchTree<T, C> *tree, Node *leafSentinel) {
	Node *parent = candidate->parent;
	Node *leftChild = candidate->leftChild;
	Node *grandparent = parent->parent;
	
	parent->rightChild = leftChild;
	candidate->leftChild = parent;
	
	parent->parent = candidate;
	candidate->parent = grandparent;
	
	if(leftChild != leafSentinel) {
		leftChild->parent = parent;
	}
	if(grandparent) {
		if(grandparent->leftChild == parent) {
			grandparent->leftChild = candidate;
		}else {
			grandparent->rightChild = candidate;
		}
	}else {
		tree->root = candidate;
	}
}

template<class T, class C>
void BstUtility<T, C>::rightRotation(Node *candidate, BinarySearchTree<T, C> *tree,  Node *leafSentinel) {
	Node *parent = candidate->parent;
	Node *rightChild = candidate->rightChild;
	Node *grandParent = parent->parent;
	
	candidate->rightChild = parent;
	parent->leftChild = rightChild;
	
	parent->parent = candidate;
	candidate->parent = grandParent;
	
	if(rightChild != leafSentinel) {
		rightChild->parent = parent;
	}
	if(grandParent) {
		if(grandParent->leftChild == parent) {
			grandParent->leftChild = candidate;
		}else {
			grandParent->rightChild = candidate;
		}
	}else {
		tree->root = candidate;
	}
}

template<class T, class C>
void BstUtility<T, C>::leftLeftCase(Node *candidate, BinarySearchTree<T, C> *tree, Node *leafSentinel) {
	BstUtility<T, C>::rightRotation(candidate, tree, leafSentinel);
}

template<class T, class C>
void BstUtility<T, C>::leftRightCase(Node *candidate, BinarySearchTree<T, C> *tree, Node *leafSentinel) {
	Node *rightChild = candidate->rightChild;
	BstUtility<T, C>::leftRotation(rightChild, tree, leafSentinel);
	BstUtility<T, C>::leftLeftCase(rightChild, tree, leafSentinel);
}

template<class T, class C>
void BstUtility<T, C>::rightRightCase(Node *candidate, BinarySearchTree<T, C> *tree, Node *leafSentinel) {
	BstUtility<T, C>::leftRotation(candidate, tree, leafSentinel);
}

template<class T, class C>
void BstUtility<T, C>::rightLeftCase(Node *candidate, BinarySearchTree<T, C> *tree, Node *leafSentinel) {
	Node *leftChild = candidate->leftChild;
	BstUtility<T, C>::rightRotation(leftChild, tree, leafSentinel);
	BstUtility<T, C>::rightRightCase(leftChild, tree, leafSentinel);
}