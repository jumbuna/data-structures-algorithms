#include "SplayTree.h"

template<class T>
void SplayTree<T>::zigCase(Node *candidate) {
	if(candidate != BinarySearchTree<T>::root) {
		Node *parent = candidate->parent;
		if(!parent->parent) {
			if(parent->leftChild == candidate) {
				BstUtility<T>::leftLeftCase(candidate, this);
			}else {
				BstUtility<T>::rightRightCase(candidate, this);
			}
		}
	}
}

template<class T>
void SplayTree<T>::zigZigCase(Node *candidate) {
	if(candidate != BinarySearchTree<T>::root) {
		Node *parent = candidate->parent;
		Node *grandParent = parent->parent;
		if(grandParent) {
			if(grandParent->leftChild == parent && parent->leftChild == candidate) {
				BstUtility<T>::leftLeftCase(parent, this);
				BstUtility<T>::leftLeftCase(candidate, this);
			}else if(grandParent->rightChild == parent && parent->rightChild == candidate) {
				BstUtility<T>::rightRightCase(parent, this);
				BstUtility<T>::rightRightCase(candidate, this);
			}
		}
	}
}


template<class T>
void SplayTree<T>::zigZagCase(Node *candidate) {
	if(candidate != BinarySearchTree<T>::root) {
		Node *parent = candidate->parent;
		Node *grandParent = parent->parent;
		if(grandParent) {
			if(grandParent->rightChild == parent && parent->leftChild == candidate) {
				BstUtility<T>::leftLeftCase(candidate, this);
				BstUtility<T>::rightRightCase(candidate, this);
			}else if(grandParent->leftChild == parent && parent->rightChild == candidate) {
				BstUtility<T>::rightRightCase(candidate, this);
				BstUtility<T>::leftLeftCase(candidate, this);
			}
		}
	}
}

template<class T>
void SplayTree<T>::splay(Node *candidate) {
	while(candidate != BinarySearchTree<T>::root) {
		zigCase(candidate);
		zigZigCase(candidate);
		zigZagCase(candidate);
	}
}

template<class T>
bool SplayTree<T>::find(T element) {
	Node *elementNode = BstUtility<T>::contains(BinarySearchTree<T>::root, element);
	if(elementNode) {
		splay(elementNode);
		return true;
	}
	return false;
}

template<class T>
void SplayTree<T>::insert(Node *candidate, Node *parent, T element) {
	if(!candidate && !parent) {
		BinarySearchTree<T>::root = nodeAllocator.create(element, parent);
		return;
	}
	
	if(!candidate) {
		candidate = nodeAllocator.create(element, parent);
		if(parent->element > element) {
			parent->leftChild = candidate;
		}else {
			parent->rightChild = candidate;
		}
		splay(candidate);
		return;
	}
	
	if(candidate->element > element) {
		insert(candidate->leftChild, candidate, element);
	}else {
		insert(candidate->rightChild, candidate, element);
	}
}

template<class T>
void SplayTree<T>::remove(Node *candidate, T element) {
	if(BinarySearchTree<T>::root == candidate) {
		Node *leftChild = candidate->leftChild;
		Node *rightChild = candidate->rightChild;
		if(!rightChild) {
			BinarySearchTree<T>::root = leftChild;
			if(leftChild) {
				leftChild->parent = nullptr;
			}
		}else if(!leftChild) {
			BinarySearchTree<T>::root = rightChild;
			if(rightChild) {
				rightChild->parent = nullptr;
			}
		}else {
			leftChild->parent = nullptr;
			BinarySearchTree<T>::root = leftChild;
			T successor = BstUtility<T>::preOrderSuccessor(leftChild);
			find(successor);
			BinarySearchTree<T>::root->rightChild = rightChild;
			rightChild->parent = BinarySearchTree<T>::root;
		}
	}
}

template<class T>
SplayTree<T>::SplayTree(std::size_t noOfElements)
:BinarySearchTree<T> ()
{
	nodeAllocator.numberOfChunks = noOfElements;
}

template<class T>
void SplayTree<T>::insert(T element) {
	if(!find(element)) {
		insert(BinarySearchTree<T>::root, BinarySearchTree<T>::root, element);
		++BinarySearchTree<T>::nodeCount;
	}
}

template<class T>
void SplayTree<T>::remove(T element) {
	if(find(element)) {
		remove(BinarySearchTree<T>::root, element);
		--BinarySearchTree<T>::nodeCount;
	}
}

template<class T>
bool SplayTree<T>::contains(T element) {
	return find(element);
}

template<class T>
std::size_t SplayTree<T>::size() {
	return BinarySearchTree<T>::nodeCount;
}

template<class T>
Vector<T> SplayTree<T>::treeTraversal(TraversalOrder order) {
	return BstUtility<T>::treeTraversal(BinarySearchTree<T>::root, order);
}
