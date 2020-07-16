#include "UnbalancedBinarySearchTree.h"

template<class T, class C>
void UnbalancedBinarySearchTree<T, C>::insert(Node *candidate, Node *parent, T element) {
	if(!candidate && !parent) {
		BinarySearchTree<T, C>::root = nodeAllocator.create(element, parent);
		return;
	}
	
	if(!candidate) {
		if(BinarySearchTree<T, C>::comparator(parent->element, element)) {
			parent->leftChild = nodeAllocator.create(element, parent);
		}else {
			parent->rightChild = nodeAllocator.create(element, parent);
		}
		return;
	}
	
	if(BinarySearchTree<T, C>::comparator(candidate->element, element)) {
		insert(candidate->leftChild, candidate, element);
	}else {
		insert(candidate->rightChild, candidate, element);
	}
}

template<class T, class C>
void UnbalancedBinarySearchTree<T, C>::removeNode(Node *candidate, T element) {
	if(!candidate) {
		return;
	}
	if(candidate->element != element) {
		if(BinarySearchTree<T, C>::comparator(candidate->element, element)) {
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
			BinarySearchTree<T, C>::root = leftChild;
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
			BinarySearchTree<T, C>::root = rightChild;
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

template<class T, class C>
UnbalancedBinarySearchTree<T, C>::UnbalancedBinarySearchTree(std::size_t noOfElements)
:BinarySearchTree<T, C>()
{
	nodeAllocator.numberOfChunks = noOfElements;
}

template<class T, class C>
UnbalancedBinarySearchTree<T, C>::UnbalancedBinarySearchTree()
:BinarySearchTree<T, C>()
{}

template<class T, class C>
void UnbalancedBinarySearchTree<T, C>::insert(T element) {
	insert(BinarySearchTree<T, C>::root, BinarySearchTree<T, C>::root, element);
	++BinarySearchTree<T, C>::nodeCount;
}

template<class T, class C>
void UnbalancedBinarySearchTree<T, C>::remove(T element) {
	if(contains(element)) {
		removeNode(BinarySearchTree<T, C>::root, element);
		if(--BinarySearchTree<T, C>::nodeCount == 0) {
			BinarySearchTree<T, C>::root = nullptr;
		}
	}
}

template<class T, class C>
bool UnbalancedBinarySearchTree<T, C>::contains(T element) {
	return BstUtility<T>::contains(BinarySearchTree<T, C>::root, element, this) != nullptr;
}

template<class T, class C>
std::size_t UnbalancedBinarySearchTree<T, C>::size() {
	return BinarySearchTree<T, C>::nodeCount;
}

template<class T, class C>
Vector<T> UnbalancedBinarySearchTree<T, C>::treeTraversal(TraversalOrder order) {
	return BstUtility<T>::treeTraversal(BinarySearchTree<T, C>::root, order);
}