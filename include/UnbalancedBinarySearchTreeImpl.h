#include "UnbalancedBinarySearchTree.h"

template<class T>
void UnbalancedBinarySearchTree<T>::insert(Node *candidate, Node *parent, T element) {
	if(!candidate && !parent) {
		BinarySearchTree<T>::root = nodeAllocator.create(element, parent);
		return;
	}
	
	if(!candidate) {
		if(parent->element > element) {
			parent->leftChild = nodeAllocator.create(element, parent);
		}else {
			parent->rightChild = nodeAllocator.create(element, parent);
		}
		return;
	}
	
	if(candidate->element > element) {
		insert(candidate->leftChild, candidate, element);
	}else {
		insert(candidate->rightChild, candidate, element);
	}
}

template<class T>
void UnbalancedBinarySearchTree<T>::removeNode(Node *candidate, T element) {
	if(!candidate) {
		return;
	}
	if(candidate->element != element) {
		if(candidate->element > element) {
			removeNode(candidate->leftChild, element);
		}else {
			removeNode(candidate->rightChild, element);
		}
		return;
	}
	Node *parent = candidate->parent;
	if(!candidate->rightChild) {
		Node *leftChild = candidate->leftChild;
		if(parent) {
			if(parent->leftChild == candidate) {
				parent->leftChild = leftChild;
			}else {
				parent->rightChild = leftChild;
			}
		}else {
			BinarySearchTree<T>::root = leftChild;
		}
		if(leftChild) {
			leftChild->parent = parent;
		}
		nodeAllocator.destroy(candidate);
	}else if(!candidate->leftChild) {
		Node *rightChild = candidate->rightChild;
		if(parent) {
			if(parent->leftChild == candidate) {
				parent->leftChild = rightChild;
			}else {
				parent->rightChild = rightChild;
			}
		}else {
			BinarySearchTree<T>::root = rightChild;
		}
		if(rightChild) {
			rightChild->parent = parent;
		}
		nodeAllocator.destroy(candidate);
	}else {
		T successor = BstUtility<T>::preOrderSuccessor(candidate->leftChild);
		candidate->element = successor;
		removeNode(candidate->leftChild, successor);
	}	
}

template<class T>
UnbalancedBinarySearchTree<T>::UnbalancedBinarySearchTree(std::size_t noOfElements)
:BinarySearchTree<T>()
{
	nodeAllocator.numberOfChunks = noOfElements;
}

template<class T>
UnbalancedBinarySearchTree<T>::UnbalancedBinarySearchTree()
:BinarySearchTree<T>()
{}

template<class T>
void UnbalancedBinarySearchTree<T>::insert(T element) {
	insert(BinarySearchTree<T>::root, BinarySearchTree<T>::root, element);
	++BinarySearchTree<T>::nodeCount;
}

template<class T>
void UnbalancedBinarySearchTree<T>::remove(T element) {
	if(contains(element)) {
		removeNode(BinarySearchTree<T>::root, element);
		if(--BinarySearchTree<T>::nodeCount == 0) {
			BinarySearchTree<T>::root = nullptr;
		}
	}
}

template<class T>
bool UnbalancedBinarySearchTree<T>::contains(T element) {
	return BstUtility<T>::contains(BinarySearchTree<T>::root, element);
}

template<class T>
std::size_t UnbalancedBinarySearchTree<T>::size() {
	return BinarySearchTree<T>::nodeCount;
}

template<class T>
Vector<T> UnbalancedBinarySearchTree<T>::treeTraversal(TraversalOrder order) {
	return BstUtility<T>::treeTraversal(BinarySearchTree<T>::root, order);
}