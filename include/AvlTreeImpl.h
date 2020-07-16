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


template<class T, class C>
void AvlTree<T, C>::insert(Node *candidate, Node *parent, T element) {
	if(!candidate && !parent) {
		BinarySearchTree<T, C>::root = nodeAllocator.create(element, static_cast<AvlNode*>(parent));
		return;
	}
	
	if(!candidate) {
		if(BinarySearchTree<T, C>::comparator(parent->element, element)) {
			parent->leftChild = nodeAllocator.create(element, static_cast<AvlNode*>(parent));
		}else {
			parent->rightChild = nodeAllocator.create(element, static_cast<AvlNode*>(parent));
		}
		return;
	}
	
	if(BinarySearchTree<T, C>::comparator(candidate->element, element)) {
		insert(candidate->leftChild, candidate, element);
	}else {
		insert(candidate->rightChild, candidate, element);
	}
	
	updateBalanceFactor(static_cast<AvlNode*>(candidate));
	balance(static_cast<AvlNode*>(candidate));
}

template<class T, class C>
void AvlTree<T, C>::remove(Node *candidate, T element) {
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
		if(BinarySearchTree<T, C>::comparator(candidate->element, element)) {
			remove(candidate->leftChild, element);
		}else {
			remove(candidate->rightChild, element);
		}
	}
	updateBalanceFactor(static_cast<AvlNode*>(candidate));
	balance(static_cast<AvlNode*>(candidate));
}

template<class T, class C>
void AvlTree<T, C>::updateBalanceFactor(AvlNode *candidate) {
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

template<class T, class C>
void AvlTree<T, C>::balance(AvlNode *candidate) {
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

template<class T, class C>
AvlTree<T, C>::AvlTree(std::size_t noOfElements)
:BinarySearchTree<T, C>()
{
	nodeAllocator.numberOfChunks = noOfElements;
}

template<class T, class C>
AvlTree<T, C>::AvlTree()
:BinarySearchTree<T, C>()
{}

template<class T, class C>
void AvlTree<T, C>::insert(T element) {
	insert(BinarySearchTree<T, C>::root, BinarySearchTree<T, C>::root, element);
	++BinarySearchTree<T, C>::nodeCount;
}

template<class T, class C>
void AvlTree<T, C>::remove(T element) {
	if(contains(element)) {
		remove(BinarySearchTree<T, C>::root, element);
		if(--BinarySearchTree<T, C>::nodeCount == 0) {
			BinarySearchTree<T, C>::root = nullptr;
		}
	}
}

template<class T, class C>
bool AvlTree<T, C>::contains(T element) {
	return BstUtility<T>::contains(BinarySearchTree<T, C>::root, element, this) != nullptr;
}

template<class T, class C>
std::size_t AvlTree<T, C>::size() {
	return BinarySearchTree<T, C>::nodeCount;
}

template<class T, class C>
Vector<T> AvlTree<T, C>::treeTraversal(TraversalOrder order) {
	return BstUtility<T>::treeTraversal(BinarySearchTree<T, C>::root, order);
}