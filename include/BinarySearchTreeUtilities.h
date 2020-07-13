#pragma once

#include "BinarySearchTree.h"
#include "Vector.h"
#include "Queue.h"
#include "BinarySearchTreeTraversals.h"

template<class T>
class BstUtility {
	using Node = BstNode<T>;
public:
	static Vector<T> treeTraversal(Node *, TraversalOrder, Node * = nullptr);
	static void inOrderTraversal(Node *, Vector<T> &, Node *);
	static void postOrderTraversal(Node *, Vector<T> &, Node *);
	static void preOrderTraversal(Node *, Vector<T> &, Node *);
	static void levelOrderTraversal(Node *, Vector<T> &, Node *);
	static bool contains(Node *, T, Node * = nullptr);
	static T preOrderSuccessor(Node *, Node * = nullptr);
	static void leftRotation(Node *, BinarySearchTree<T> *, Node * = nullptr);
	static void rightRotation(Node *, BinarySearchTree<T> *, Node * = nullptr);
	static void leftLeftCase(Node *, BinarySearchTree<T> *, Node * = nullptr);
	static void leftRightCase(Node *, BinarySearchTree<T> *, Node * = nullptr);
	static void rightRightCase(Node *, BinarySearchTree<T> *, Node * = nullptr);
	static void rightLeftCase(Node *, BinarySearchTree<T> *, Node * = nullptr);
};

template<class T>
Vector<T> BstUtility<T>::treeTraversal(Node *startingNode, TraversalOrder order, Node *leafSentinel) {
	Vector<T> vector {128};
	if(startingNode == leafSentinel) {
		return vector;
	}
	switch(order) {
		case IN_ORDER:
			BstUtility<T>::inOrderTraversal(startingNode, vector, leafSentinel);
			break;
		case POST_ORDER:
			BstUtility<T>::postOrderTraversal(startingNode, vector, leafSentinel);
			break;
		case PRE_ORDER:
			BstUtility<T>::preOrderTraversal(startingNode, vector, leafSentinel);
			break;
		case LEVEL_ORDER:
			BstUtility<T>::levelOrderTraversal(startingNode, vector, leafSentinel);
	}
	return vector;
}

template<class T>
void BstUtility<T>::inOrderTraversal(Node *startingNode, Vector<T> &vector, Node *leafSentinel) {
	if(startingNode != leafSentinel) {
		inOrderTraversal(startingNode->leftChild, vector, leafSentinel);
		vector.push_back(startingNode->element);
		inOrderTraversal(startingNode->rightChild, vector, leafSentinel);
	}
}

template<class T>
void BstUtility<T>::postOrderTraversal(Node *startingNode, Vector<T> &vector, Node *leafSentinel) {
	if(startingNode != leafSentinel) {
		inOrderTraversal(startingNode->leftChild, vector, leafSentinel);
		inOrderTraversal(startingNode->rightChild, vector, leafSentinel);
		vector.push_back(startingNode->element);
	}
}

template<class T>
void BstUtility<T>::preOrderTraversal(Node *startingNode, Vector<T> &vector, Node *leafSentinel) {
	if(startingNode != leafSentinel) {
		vector.push_back(startingNode->element);
		inOrderTraversal(startingNode->leftChild, vector, leafSentinel);
		inOrderTraversal(startingNode->rightChild, vector, leafSentinel);
	}
}

template<class T>
void BstUtility<T>::levelOrderTraversal(Node *startingtNode, Vector<T> &vector, Node *leafSentinel) {
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

template<class T>
bool BstUtility<T>::contains(Node *startingNode, T element, Node *leafSentinel) {
	if(startingNode != leafSentinel) {
		Node *temp = startingNode;
		while(temp != leafSentinel) {
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
T BstUtility<T>::preOrderSuccessor(Node *startingNode, Node *leafSentinel) {
	while(startingNode->rightChild != leafSentinel) {
		startingNode = startingNode->rightChild;
	}
	return startingNode->element;
}

template<class T>
void BstUtility<T>::leftRotation(Node *candidate, BinarySearchTree<T> *tree, Node *leafSentinel) {
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

template<class T>
void BstUtility<T>::rightRotation(Node *candidate, BinarySearchTree<T> *tree,  Node *leafSentinel) {
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

template<class T>
void BstUtility<T>::leftLeftCase(Node *candidate, BinarySearchTree<T> *tree, Node *leafSentinel) {
	BstUtility<T>::rightRotation(candidate, tree, leafSentinel);
}

template<class T>
void BstUtility<T>::leftRightCase(Node *candidate, BinarySearchTree<T> *tree, Node *leafSentinel) {
	Node *rightChild = candidate->rightChild;
	BstUtility<T>::leftRotation(rightChild, tree, leafSentinel);
	BstUtility<T>::leftLeftCase(rightChild, tree, leafSentinel);
}

template<class T>
void BstUtility<T>::rightRightCase(Node *candidate, BinarySearchTree<T> *tree, Node *leafSentinel) {
	BstUtility<T>::leftRotation(candidate, tree, leafSentinel);
}

template<class T>
void BstUtility<T>::rightLeftCase(Node *candidate, BinarySearchTree<T> *tree, Node *leafSentinel) {
	Node *leftChild = candidate->leftChild;
	BstUtility<T>::rightRotation(leftChild, tree, leafSentinel);
	BstUtility<T>::rightRightCase(leftChild, tree, leafSentinel);
}