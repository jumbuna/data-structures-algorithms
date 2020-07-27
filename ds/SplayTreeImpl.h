#include "SplayTree.h"

template<class T, class C>
void SplayTree<T, C>::zigCase(Node *candidate) {
	if(candidate != BinarySearchTree<T, C>::root) {
		Node *parent = candidate->parent;
		if(!parent->parent) {
			if(parent->leftChild == candidate) {
				BstUtility<T, C>::leftLeftCase(candidate, this);
			}else {
				BstUtility<T, C>::rightRightCase(candidate, this);
			}
		}
	}
}

template<class T, class C>
void SplayTree<T, C>::zigZigCase(Node *candidate) {
	if(candidate != BinarySearchTree<T, C>::root) {
		Node *parent = candidate->parent;
		Node *grandParent = parent->parent;
		if(grandParent) {
			if(grandParent->leftChild == parent && parent->leftChild == candidate) {
				BstUtility<T, C>::leftLeftCase(parent, this);
				BstUtility<T, C>::leftLeftCase(candidate, this);
			}else if(grandParent->rightChild == parent && parent->rightChild == candidate) {
				BstUtility<T, C>::rightRightCase(parent, this);
				BstUtility<T, C>::rightRightCase(candidate, this);
			}
		}
	}
}


template<class T, class C>
void SplayTree<T, C>::zigZagCase(Node *candidate) {
	if(candidate != BinarySearchTree<T, C>::root) {
		Node *parent = candidate->parent;
		Node *grandParent = parent->parent;
		if(grandParent) {
			if(grandParent->rightChild == parent && parent->leftChild == candidate) {
				BstUtility<T, C>::leftLeftCase(candidate, this);
				BstUtility<T, C>::rightRightCase(candidate, this);
			}else if(grandParent->leftChild == parent && parent->rightChild == candidate) {
				BstUtility<T, C>::rightRightCase(candidate, this);
				BstUtility<T, C>::leftLeftCase(candidate, this);
			}
		}
	}
}

template<class T, class C>
void SplayTree<T, C>::splay(Node *candidate) {
	while(candidate != BinarySearchTree<T, C>::root) {
		zigCase(candidate);
		zigZigCase(candidate);
		zigZagCase(candidate);
	}
}

template<class T, class C>
bool SplayTree<T, C>::find(T element) {
	Node *elementNode = BstUtility<T, C>::contains(BinarySearchTree<T, C>::root, element);
	if(elementNode) {
		splay(elementNode);
		return true;
	}
	return false;
}

template<class T, class C>
void SplayTree<T, C>::insert(Node *candidate, Node *parent, T element) {
	if(!candidate && !parent) {
		BinarySearchTree<T, C>::root = nodeAllocator.create(element, parent);
		return;
	}
	
	if(!candidate) {
		candidate = nodeAllocator.create(element, parent);
		if(BinarySearchTree<T, C>::comparator(parent->element, element)) {
			parent->leftChild = candidate;
		}else {
			parent->rightChild = candidate;
		}
		splay(candidate);
		return;
	}
	
	if(BinarySearchTree<T, C>::comparator(candidate->element, element)) {
		insert(candidate->leftChild, candidate, element);
	}else {
		insert(candidate->rightChild, candidate, element);
	}
}

template<class T, class C>
void SplayTree<T, C>::remove(Node *candidate, T element) {
	if(BinarySearchTree<T, C>::root == candidate) {
		Node *leftChild = candidate->leftChild;
		Node *rightChild = candidate->rightChild;
		if(!rightChild) {
			BinarySearchTree<T, C>::root = leftChild;
			if(leftChild) {
				leftChild->parent = nullptr;
			}
		}else if(!leftChild) {
			BinarySearchTree<T, C>::root = rightChild;
			if(rightChild) {
				rightChild->parent = nullptr;
			}
		}else {
			leftChild->parent = nullptr;
			BinarySearchTree<T, C>::root = leftChild;
			T successor = BstUtility<T, C>::preOrderSuccessor(leftChild);
			find(successor);
			BinarySearchTree<T, C>::root->rightChild = rightChild;
			rightChild->parent = BinarySearchTree<T, C>::root;
		}
	}
}

template<class T, class C>
SplayTree<T, C>::SplayTree(std::size_t noOfElements)
:BinarySearchTree<T, C> ()
{
	nodeAllocator.numberOfChunks = noOfElements;
}

template<class T, class C>
void SplayTree<T, C>::insert(T element) {
	if(!find(element)) {
		insert(BinarySearchTree<T, C>::root, BinarySearchTree<T, C>::root, element);
		++BinarySearchTree<T, C>::nodeCount;
	}
}

template<class T, class C>
void SplayTree<T, C>::remove(T element) {
	if(find(element)) {
		remove(BinarySearchTree<T, C>::root, element);
		--BinarySearchTree<T, C>::nodeCount;
	}
}

template<class T, class C>
bool SplayTree<T, C>::contains(T element) {
	return find(element);
}

template<class T, class C>
std::size_t SplayTree<T, C>::size() {
	return BinarySearchTree<T, C>::nodeCount;
}

template<class T, class C>
Vector<T> SplayTree<T, C>::treeTraversal(TraversalOrder order) {
	return BstUtility<T, C>::treeTraversal(BinarySearchTree<T, C>::root, order);
}

template<class T, class C>
void SplayTree<T, C>::clear() {
	nodeAllocator.reset();
	BinarySearchTree<T, C>::root = nullptr;
	BinarySearchTree<T, C>::nodeCount = 0;
}