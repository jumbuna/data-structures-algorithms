#include "AATree.h"

template<class T>
AANode<T>::AANode(T element, BstNode<T> *parent)
:BstNode<T> (element, parent)
{
	level = 1;
}

template<class T>
AANode<T>* AANode<T>::getLeftChild() {
	return BstNode<T>::leftChild ? static_cast<AANode*> (BstNode<T>::leftChild) : nullptr;
}

template<class T>
AANode<T>* AANode<T>::getRightChild() {
	return BstNode<T>::rightChild ? static_cast<AANode*> (BstNode<T>::rightChild) : nullptr;
}
template<class T>
AANode<T>* AANode<T>::getParent() {
	return BstNode<T>::parent ? static_cast<AANode*> (BstNode<T>::parent) : nullptr;
}

template<class T>
bool AATree<T>::leftHorizontalLinkExists(aaNode *candidate) {
	aaNode *leftChild = candidate->getLeftChild();
	if(leftChild) {
		if(leftChild->level == candidate->level) {
			return true;
		}
	}
	return false;
}

template<class T>
bool AATree<T>::rightHorizontalLinkExists(aaNode *candidate) {
	aaNode *rightChild = candidate->getRightChild();
	if(rightChild) {
		aaNode *rightGrandChild = rightChild->getRightChild();
		if(rightGrandChild) {
			if(rightGrandChild->level == candidate->level) {
				return true;
			}
		}
	}
	return false;
}

template<class T>
void AATree<T>::split(aaNode *candidate) {
	if(rightHorizontalLinkExists(candidate)) {
		aaNode *rightChild = candidate->getRightChild();
		BstUtility<T>::rightRightCase(rightChild, this);
		rightChild->level += 1;
	}
}

template<class T>
void AATree<T>::skew(aaNode *candidate) {
	if(leftHorizontalLinkExists(candidate)) {
		Node *leftChild = candidate->getLeftChild();
		BstUtility<T>::leftLeftCase(leftChild, this);
	}
}

template<class T>
void AATree<T>::insert(Node *candidate, Node *parent, T element) {
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
	
	skew(static_cast<aaNode*> (candidate));
	split(static_cast<aaNode*> (candidate));
}

template<class T>
void AATree<T>::remove(Node *candidate, T element) {
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
			}else {
				BinarySearchTree<T>::root = leftChild;
			}
			if(leftChild) {
				leftChild->parent = parent;
			}
			nodeAllocator.destroy(static_cast<aaNode*> (candidate));
			return;
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
			nodeAllocator.destroy(static_cast<aaNode*> (candidate));
			return;
		}else {
			T successor = BstUtility<T>::preOrderSuccessor(candidate->leftChild);
			candidate->element = successor;
			remove(candidate->leftChild, successor);
		}
	}else {
		if(candidate->element > element) {
			remove(candidate->leftChild, element);
		}else {
			remove(candidate->rightChild, element);
		}
	}
	
	updateLevel(static_cast<aaNode*> (candidate));
	skew(static_cast<aaNode*> (candidate));
	split(static_cast<aaNode*> (candidate));
}

template<class T>
void AATree<T>::updateLevel(aaNode *candidate) {
	std::size_t leftLevel, rightLevel;
	leftLevel = rightLevel = 0;
	if(candidate->leftChild) {
		leftLevel = (*candidate->getLeftChild()).level;
	}
	if(candidate->rightChild) {
		rightLevel = (*candidate->getRightChild()).level;
	}
	
	if(candidate->level - std::min(leftLevel, rightLevel) == 2) {
		candidate->level -= 1;
	}
}

template<class T>
AATree<T>::AATree(std::size_t noOfelements)
:BinarySearchTree<T> ()
{
	nodeAllocator.numberOfChunks = noOfelements;
}

template<class T>
void AATree<T>::insert(T element) {
	insert(BinarySearchTree<T>::root, BinarySearchTree<T>::root, element);
	++BinarySearchTree<T>::nodeCount;
}

template<class T>
void AATree<T>::remove(T element) {
	if(contains(element)) {
		remove(BinarySearchTree<T>::root, element);
		--BinarySearchTree<T>::nodeCount;	
	}
}

template<class T>
bool AATree<T>::contains(T element) {
	return BstUtility<T>::contains(BinarySearchTree<T>::root, element);
}

template<class T>
std::size_t AATree<T>::size() {
	return BinarySearchTree<T>::nodeCount;
}

template<class T>
Vector<T> AATree<T>::treeTraversal(TraversalOrder order) {
	return BstUtility<T>::treeTraversal(BinarySearchTree<T>::root, order);
}