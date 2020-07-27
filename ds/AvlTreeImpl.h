#include "AvlTree.h"

namespace jumbuna {
template<class T>
AvlNode<T>::AvlNode(T element, AvlNode *parent)
:BstNode<T>(element, parent)
{
	//inital BF & height
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
	//first insertion
	if(!candidate && !parent) {
		BinarySearchTree<T, C>::root = nodeAllocator.create(element, static_cast<AvlNode*>(parent));
		return;
	}
	//reached insertion point/child of leaf node
	if(!candidate) {
		if(BinarySearchTree<T, C>::comparator(parent->element, element)) {
			parent->leftChild = nodeAllocator.create(element, static_cast<AvlNode*>(parent));
		}else {
			parent->rightChild = nodeAllocator.create(element, static_cast<AvlNode*>(parent));
		}
		return;
	}
	//internal node
	if(BinarySearchTree<T, C>::comparator(candidate->element, element)) {
		insert(candidate->leftChild, candidate, element);
	}else {
		insert(candidate->rightChild, candidate, element);
	}
	//balance the tree
	updateBalanceFactor(static_cast<AvlNode*>(candidate));
	balance(static_cast<AvlNode*>(candidate));
}

template<class T, class C>
void AvlTree<T, C>::remove(Node *candidate, T element) {
	if(!candidate) {
		//called only when a search is node done before beginning removal
		return;
	}
	if(candidate->element == element) {
		Node *parent = candidate->parent;
		//leafnode/leftchild only
		if(!candidate->rightChild) {
			Node *leftChild = candidate->leftChild;
			if(parent) {
				if(parent->leftChild == candidate) {
					parent->leftChild = leftChild;
				}else {
					parent->rightChild = leftChild;
				}
			}else{
				BinarySearchTree<T, C>::root = leftChild;
			}
			if(leftChild) {
				leftChild->parent = parent;
			}
			nodeAllocator.destroy(static_cast<AvlNode*>(candidate));
			return;
		}else if(!candidate->leftChild) {
			//leafnode/rightchild only
			Node *rightChild = candidate->rightChild;
			if(parent) {
				if(parent->rightChild == candidate) {
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
			nodeAllocator.destroy(static_cast<AvlNode*>(candidate));
			return;
		}else {
			//internal node with both LC & RC
			T successor = BstUtility<T, C>::preOrderSuccessor(candidate->leftChild);
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
	//post remove balance
	updateBalanceFactor(static_cast<AvlNode*>(candidate));
	balance(static_cast<AvlNode*>(candidate));
}

template<class T, class C>
void AvlTree<T, C>::updateBalanceFactor(AvlNode *candidate) {
	//initial height -1 so that height of candidate is 0 incase no children are present i.e 1 + -1 = 0
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
	//new balance factor
	candidate->balanceFactor = leftHeight - rightHeight;
	//new height
	candidate->height = 1 + std::max(leftHeight, rightHeight);
}

template<class T, class C>
void AvlTree<T, C>::balance(AvlNode *candidate) {
	//left heavy
	if(candidate->balanceFactor == +2) {
		AvlNode *leftChild = candidate->getLeftChild();
		//left left heavy
		if(leftChild->balanceFactor == 1) {
			BstUtility<T, C>::leftLeftCase(leftChild, this);
		}else if(leftChild->balanceFactor == -1) {
			//left right heavy
			BstUtility<T, C>::leftRightCase(leftChild, this);
		}
	}
	//right heavy
	if(candidate->balanceFactor == -2) {
		AvlNode *rightChild = candidate->getRightChild();
		if(rightChild->balanceFactor == 1) {
			//right left heavy
			BstUtility<T, C>::rightLeftCase(rightChild, this);
		}else if(rightChild->balanceFactor == -1) {
			//right right heavy
			BstUtility<T, C>::rightRightCase(rightChild, this);
		}
	}
	
	//update the BF after the rotations
	updateBalanceFactor(candidate);
}

template<class T, class C>
AvlTree<T, C>::AvlTree(std::size_t noOfElements)
:BinarySearchTree<T, C>()
{
	//exact size of buffer to be allocated
	nodeAllocator.numberOfChunks = noOfElements;
}

template<class T, class C>
void AvlTree<T, C>::insert(T element) {
	insert(BinarySearchTree<T, C>::root, BinarySearchTree<T, C>::root, element);
	++BinarySearchTree<T, C>::nodeCount;
}

template<class T, class C>
void AvlTree<T, C>::remove(T element) {
	if(contains(element)) {
		remove(BinarySearchTree<T, C>::root, element);
		--BinarySearchTree<T, C>::nodeCount;
	}
}

template<class T, class C>
bool AvlTree<T, C>::contains(T element) {
	return BstUtility<T, C>::contains(BinarySearchTree<T, C>::root, element) != nullptr;
}

template<class T, class C>
std::size_t AvlTree<T, C>::size() {
	return BinarySearchTree<T, C>::nodeCount;
}

template<class T, class C>
Vector<T> AvlTree<T, C>::treeTraversal(TraversalOrder order) {
	return BstUtility<T, C>::treeTraversal(BinarySearchTree<T, C>::root, order);
}

template<class T, class C>
void AvlTree<T, C>::clear() {
	nodeAllocator.reset();
	BinarySearchTree<T, C>::root = nullptr;
	BinarySearchTree<T, C>::nodeCount = 0;
}

}