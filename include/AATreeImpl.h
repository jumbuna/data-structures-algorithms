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

template<class T, class C>
bool AATree<T, C>::leftHorizontalLinkExists(aaNode *candidate) {
	aaNode *leftChild = candidate->getLeftChild();
	if(leftChild) {
		if(leftChild->level == candidate->level) {
			return true;
		}
	}
	return false;
}

template<class T, class C>
bool AATree<T, C>::rightHorizontalLinkExists(aaNode *candidate) {
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

template<class T, class C>
void AATree<T, C>::split(aaNode *candidate) {
	if(rightHorizontalLinkExists(candidate)) {
		aaNode *rightChild = candidate->getRightChild();
		BstUtility<T, C>::rightRightCase(rightChild, this);
		rightChild->level += 1;
	}
}

template<class T, class C>
void AATree<T, C>::skew(aaNode *candidate) {
	if(leftHorizontalLinkExists(candidate)) {
		Node *leftChild = candidate->getLeftChild();
		BstUtility<T, C>::leftLeftCase(leftChild, this);
	}
}

template<class T, class C>
void AATree<T, C>::insert(Node *candidate, Node *parent, T element) {
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
	
	skew(static_cast<aaNode*> (candidate));
	split(static_cast<aaNode*> (candidate));
}

template<class T, class C>
void AATree<T, C>::remove(Node *candidate, T element) {
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
				BinarySearchTree<T, C>::root = leftChild;
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
				BinarySearchTree<T, C>::root = rightChild;
			}
			if(rightChild) { 
				rightChild->parent = parent;
			}
			nodeAllocator.destroy(static_cast<aaNode*> (candidate));
			return;
		}else {
			T successor = BstUtility<T, C>::preOrderSuccessor(candidate->leftChild);
			candidate->element = successor;
			remove(candidate->leftChild, successor);
		}
	}else {
		if(BinarySearchTree<T, C>::comparator(candidate->element, element)) {
			remove(candidate->leftChild, element);
		}else {
			remove(candidate->rightChild, element);
		}
	}
	
	updateLevel(static_cast<aaNode*> (candidate));
	skew(static_cast<aaNode*> (candidate));
	split(static_cast<aaNode*> (candidate));
}

template<class T, class C>
void AATree<T, C>::updateLevel(aaNode *candidate) {
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

template<class T, class C>
AATree<T, C>::AATree(std::size_t noOfelements)
:BinarySearchTree<T, C> ()
{
	nodeAllocator.numberOfChunks = noOfelements;
}

template<class T, class C>
void AATree<T, C>::insert(T element) {
	insert(BinarySearchTree<T, C>::root, BinarySearchTree<T, C>::root, element);
	++BinarySearchTree<T, C>::nodeCount;
}

template<class T, class C>
void AATree<T, C>::remove(T element) {
	if(contains(element)) {
		remove(BinarySearchTree<T, C>::root, element);
		--BinarySearchTree<T, C>::nodeCount;	
	}
}

template<class T, class C>
bool AATree<T, C>::contains(T element) {
	return BstUtility<T, C>::contains(BinarySearchTree<T, C>::root, element) != nullptr;
}

template<class T, class C>
std::size_t AATree<T, C>::size() {
	return BinarySearchTree<T, C>::nodeCount;
}

template<class T, class C>
Vector<T> AATree<T, C>::treeTraversal(TraversalOrder order) {
	return BstUtility<T, C>::treeTraversal(BinarySearchTree<T, C>::root, order);
}

template<class T, class C>
void AATree<T, C>::clear() {
	nodeAllocator.Pool<T>::reset();
	BinarySearchTree<T, C>::root = nullptr;
	BinarySearchTree<T, C>::nodeCount = 0;
}