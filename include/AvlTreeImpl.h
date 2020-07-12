#include "AvlTree.h"

template<class T>
AvlNode<T>::AvlNode(T element, AvlNode *parent)
:BstNode<T>(element, parent)
{
	height = balanceFactor = 0;
}

template<class T>
AvlNode<T>* AvlNode<T>::getLeftChild() {
	return static_cast<AvlNode<T>*> (BstNode<T>::leftChild);
}

template<class T>
AvlNode<T>* AvlNode<T>::getRightChild() {
	return static_cast<AvlNode<T>*> (BstNode<T>::rightChild);
}

template<class T>
AvlNode<T>* AvlNode<T>::getParent() {
	return static_cast<AvlNode<T>*> (BstNode<T>::parent);
}


template<class T>
void AvlTree<T>::insert(Node *candidate, Node *parent, T element) {
	if(!candidate && !parent) {
		BinarySearchTree<T>::root = nodeAllocator.create(element, static_cast<AvlNode*>(parent));
		return;
	}
	
	if(!candidate) {
		if(parent->element > element) {
			parent->leftChild = nodeAllocator.create(element, static_cast<AvlNode*>(parent));
		}else {
			parent->rightChild = nodeAllocator.create(element, static_cast<AvlNode*>(parent));
		}
		return;
	}
	
	if(candidate->element > element) {
		insert(candidate->leftChild, candidate, element);
	}else {
		insert(candidate->rightChild, candidate, element);
	}
	
	updateBalanceFactor(static_cast<AvlNode*>(candidate));
	balance(static_cast<AvlNode*>(candidate));
}

template<class T>
void AvlTree<T>::remove(Node *candidate, T element) {
	if(!candidate) {
		return;
	}
	if(candidate->element == element) {
		Node *parent = candidate->parent;
		
		if(!candidate->rightChild) {
			Node *leftChild = candidate->leftChild;
			if(parent) {
				if(parent->leftChild == candidate) {
					parent->leftChild = leftChild;
				}else {
					parent->rightChild = leftChild;
				}
			}
			if(leftChild) {
				leftChild->parent = parent;
			}
			nodeAllocator.destroy(static_cast<AvlNode*>(candidate));
		}else if(!candidate->leftChild) {
			Node *rightChild = candidate->rightChild;
			if(parent) {
				if(parent->rightChild == candidate) {
					parent->leftChild = rightChild;
				}else {
					parent->rightChild = rightChild;
				}
			}
			if(rightChild) {
				rightChild->parent = parent;
			}
			nodeAllocator.destroy(static_cast<AvlNode*>(candidate));
		}else {
			T successor = BstUtility<T>::preOrderSuccessor(candidate->leftChild);
			candidate->element = successor;
			remove(candidate->leftChild, successor);
		}
	} else {
		if(candidate->element > element) {
			remove(candidate->leftChild, element);
		}else {
			remove(candidate->rightChild, element);
		}
	}
	updateBalanceFactor(static_cast<AvlNode*>(candidate));
	balance(static_cast<AvlNode*>(candidate));
}

//template<class T>
//void AvlTree<T>::leftRotation(Node *candidate) {
//	Node *parent = candidate->parent;
//	Node *leftChild = candidate->getLeftChild();
//	Node *grandparent = candidate->parent;
//	
//	parent->rightChild = leftChild;
//	candidate->leftChild = parent;
//	
//	parent->parent = candidate;
//	candidate->parent = grandparent;
//	
//	if(leftChild) {
//		leftChild->parent = parent;
//	}
//	if(grandparent) {
//		if(grandparent->getLeftChild() == parent) {
//			grandparent->leftChild = candidate;
//		}else {
//			grandparent->rightChild = candidate;
//		}
//	}else {
//		root = candidate;
//	}
//}

//template<class T>
//void AvlTree<T>::rightRotation(Node *candidate) {
//	Node *parent = candidate->parent;
//	Node *rightChild = candidate->rightChild;
//	Node *grandaParent = parent->parent;
//	
//	candidate->rightChild = parent;
//	parent->leftChild = rightChild;
//	
//	parent->parent = candidate;
//	candidate->parent = grandaParent;
//	
//	if(rightChild) {
//		rightChild->parent = parent;
//	}
//	if(grandaParent) {
//		if(grandaParent->getLeftChild() == parent) {
//			grandaParent->leftChild = candidate;
//		}else {
//			grandaParent->rightChild = candidate;
//		}
//	}else {
//		root = candidate;
//	}
//}

//template<class T>
//void AvlTree<T>::leftLeftCase(Node *candidate) {
//	rightRotation(candidate);
//}
//
//template<class T>
//void AvlTree<T>::leftRightCase(Node *candidate) {
//	Node *rightChild = candidate->getRightChild();
//	leftRotation(rightChild);
//	leftLeftCase(rightChild);
//}
//
//template<class T>
//void AvlTree<T>::rightRightCase(Node *candidate) {
//	leftRotation(candidate);
//}
//
//template<class T>
//void AvlTree<T>::rightLeftCase(Node *candidate) {
//	Node *leftChild = candidate->getLeftChild();
//	rightRotation(leftChild);
//	rightRightCase(leftChild);
//}

template<class T>
void AvlTree<T>::updateBalanceFactor(AvlNode *candidate) {
	int leftHeight , rightHeight;
	leftHeight = rightHeight = -1;
	if(candidate->getLeftChild()) {
		AvlNode *leftChild = candidate->getLeftChild();
		leftHeight = leftChild->height;
	}
	if(candidate->getRightChild()) {
		AvlNode *rightChild = candidate->getRightChild();
		rightHeight = rightChild->height;
	}
	candidate->balanceFactor = leftHeight - rightHeight;
	candidate->height = 1 + std::max(leftHeight, rightHeight);
}

template<class T>
void AvlTree<T>::balance(AvlNode *candidate) {
	if(candidate->balanceFactor == +2) {
		AvlNode *leftChild = candidate->getLeftChild();
		if(leftChild->balanceFactor == 1) {
			BstUtility<T>::leftLeftCase(leftChild, this);
		}else if(leftChild->balanceFactor == -1) {
			BstUtility<T>::leftRightCase(leftChild, this);
		}
//		updateBalanceFactor(candidate);
	}
	
	if(candidate->balanceFactor == -2) {
		AvlNode *rightChild = candidate->getRightChild();
		if(rightChild->balanceFactor == 1) {
			BstUtility<T>::rightLeftCase(rightChild, this);
		}else if(rightChild->balanceFactor == -1) {
			BstUtility<T>::rightRightCase(rightChild, this);
		}
	}
	
	updateBalanceFactor(candidate);
}

template<class T>
AvlTree<T>::AvlTree(std::size_t noOfElements)
:BinarySearchTree<T>()
{
	nodeAllocator.numberOfChunks = noOfElements;
}

template<class T>
AvlTree<T>::AvlTree()
:BinarySearchTree<T>()
{}

template<class T>
void AvlTree<T>::insert(T element) {
	insert(BinarySearchTree<T>::root, BinarySearchTree<T>::root, element);
	++BinarySearchTree<T>::nodeCount;
}

template<class T>
void AvlTree<T>::remove(T element) {
	if(contains(element)) {
		remove(BinarySearchTree<T>::root, element);
		if(--BinarySearchTree<T>::nodeCount == 0) {
			BinarySearchTree<T>::root = nullptr;
		}
	}
}

template<class T>
bool AvlTree<T>::contains(T element) {
	return BstUtility<T>::contains(BinarySearchTree<T>::root, element);
}

template<class T>
std::size_t AvlTree<T>::size() {
	return BinarySearchTree<T>::nodeCount;
}

template<class T>
Vector<T> AvlTree<T>::treeTraversal(TraversalOrder order) {
	return BstUtility<T>::treeTraversal(BinarySearchTree<T>::root, order);
}