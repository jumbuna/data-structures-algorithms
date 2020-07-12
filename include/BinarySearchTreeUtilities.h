#pragma once

#include "BinarySearchTree.h"
#include "Vector.h"
#include "Queue.h"
#include "BinarySearchTreeTraversals.h"

template<class T>
class BstUtility {
	using Node = BstNode<T>;
public:
	static Vector<T> treeTraversal(Node *, TraversalOrder);
	static void inOrderTraversal(Node *, Vector<T> &);
	static void postOrderTraversal(Node *, Vector<T> &);
	static void preOrderTraversal(Node *, Vector<T> &);
	static void levelOrderTraversal(Node *, Vector<T> &);
	static bool contains(Node *, T);
	static T preOrderSuccessor(Node *);
	static void leftRotation(Node *, BinarySearchTree<T> *);
	static void rightRotation(Node *, BinarySearchTree<T> *);
	static void leftLeftCase(Node *, BinarySearchTree<T> *);
	static void leftRightCase(Node *, BinarySearchTree<T> *);
	static void rightRightCase(Node *, BinarySearchTree<T> *);
	static void rightLeftCase(Node *, BinarySearchTree<T> *);
};

template<class T>
Vector<T> BstUtility<T>::treeTraversal(Node *startingNode, TraversalOrder order) {
	Vector<T> vector {128};
	if(startingNode == nullptr) {
		return vector;
	}
	switch(order) {
		case IN_ORDER:
			BstUtility<T>::inOrderTraversal(startingNode, vector);
			break;
		case POST_ORDER:
			BstUtility<T>::postOrderTraversal(startingNode, vector);
			break;
		case PRE_ORDER:
			BstUtility<T>::preOrderTraversal(startingNode, vector);
			break;
		case LEVEL_ORDER:
			BstUtility<T>::levelOrderTraversal(startingNode, vector);
	}
	return vector;
}

template<class T>
void BstUtility<T>::inOrderTraversal(Node *startingNode, Vector<T> &vector) {
	if(startingNode) {
		inOrderTraversal(startingNode->leftChild, vector);
		vector.push_back(startingNode->element);
		inOrderTraversal(startingNode->rightChild, vector);
	}
}

template<class T>
void BstUtility<T>::postOrderTraversal(Node *startingNode, Vector<T> &vector) {
	if(startingNode) {
		inOrderTraversal(startingNode->leftChild, vector);
		inOrderTraversal(startingNode->rightChild, vector);
		vector.push_back(startingNode->element);
	}
}

template<class T>
void BstUtility<T>::preOrderTraversal(Node *startingNode, Vector<T> &vector) {
	if(startingNode) {
		vector.push_back(startingNode->element);
		inOrderTraversal(startingNode->leftChild, vector);
		inOrderTraversal(startingNode->rightChild, vector);
	}
}

template<class T>
void BstUtility<T>::levelOrderTraversal(Node *startingtNode, Vector<T> &vector) {
	if(startingtNode) {
		Queue<Node*> q;
		q.push(startingtNode);
		while(!q.empty()) {
			Node *temp = q.pop();
			if(temp->leftChild) {
				q.push(temp->leftChild);
			}
			if(temp->rightChild) {
				q.push(temp->rightChild);
			}
			vector.push_back(temp->element);
		}
	}	
}

template<class T>
bool BstUtility<T>::contains(Node *startingNode, T element) {
	if(startingNode) {
		Node *temp = startingNode;
		while(temp) {
			if(temp->element == element) {
				return true;
			}
			if(temp->element > element) {
				temp = temp->leftChild;
			}else {
				temp = temp->rightChild;
			}
		}
	}
	return false;
}

template<class T>
T BstUtility<T>::preOrderSuccessor(Node *startingNode) {
	while(startingNode->rightChild) {
		startingNode = startingNode->rightChild;
	}
	return startingNode->element;
}

template<class T>
void BstUtility<T>::leftRotation(Node *candidate, BinarySearchTree<T> *tree) {
	Node *parent = candidate->parent;
	Node *leftChild = candidate->leftChild;
	Node *grandparent = parent->parent;
	
	parent->rightChild = leftChild;
	candidate->leftChild = parent;
	
	parent->parent = candidate;
	candidate->parent = grandparent;
	
	if(leftChild) {
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

template<class T>
void BstUtility<T>::rightRotation(Node *candidate, BinarySearchTree<T> *tree) {
	Node *parent = candidate->parent;
	Node *rightChild = candidate->rightChild;
	Node *grandParent = parent->parent;
	
	candidate->rightChild = parent;
	parent->leftChild = rightChild;
	
	parent->parent = candidate;
	candidate->parent = grandParent;
	
	if(rightChild) {
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

template<class T>
void BstUtility<T>::leftLeftCase(Node *candidate, BinarySearchTree<T> *tree) {
	BstUtility<T>::rightRotation(candidate, tree);
}

template<class T>
void BstUtility<T>::leftRightCase(Node *candidate, BinarySearchTree<T> *tree) {
	Node *rightChild = candidate->rightChild;
	BstUtility<T>::leftRotation(rightChild, tree);
	BstUtility<T>::leftLeftCase(rightChild, tree);
}

template<class T>
void BstUtility<T>::rightRightCase(Node *candidate, BinarySearchTree<T> *tree) {
	BstUtility<T>::leftRotation(candidate, tree);
}

template<class T>
void BstUtility<T>::rightLeftCase(Node *candidate, BinarySearchTree<T> *tree) {
	Node *leftChild = candidate->leftChild;
	BstUtility<T>::rightRotation(leftChild, tree);
	BstUtility<T>::rightRightCase(leftChild, tree);
}