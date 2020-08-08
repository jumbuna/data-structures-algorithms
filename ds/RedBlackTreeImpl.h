#include "RedBlackTree.h"

using namespace jumbuna;

template<class T>
RBNode<T>::RBNode(T element, BstNode<T> *parent, BstNode<T> *leafSentinel)
:BstNode<T> (element, parent, leafSentinel)
{
	color = RED;
}

template<class T>
RBNode<T>::RBNode()
:BstNode<T>()
{
	color = BLACK;
}

template<class T>
RBNode<T>* RBNode<T>::getLeftChild() {
	return static_cast<RBNode*> (BstNode<T>::leftChild);
}

template<class T>
RBNode<T>* RBNode<T>::getRightChild() {
	return static_cast<RBNode*> (BstNode<T>::rightChild);
}
template<class T>
RBNode<T>* RBNode<T>::getParent() {
	return static_cast<RBNode*> (BstNode<T>::parent);
}

template<class T, class C>
void RedBlackTree<T, C>::insert(Node *candidate, Node *parent, T element) {
	if(candidate == &leafSentinel && parent == &leafSentinel) {
		candidate = nodeAllocator.create(element, nullptr, &leafSentinel); 
		BinarySearchTree<T, C>::root = candidate;
		return;
	}
	if(candidate == &leafSentinel) {
		candidate = nodeAllocator.create(element, parent, &leafSentinel);
		if(BinarySearchTree<T, C>::comparator(parent->element, element)) {
			parent->leftChild = candidate;
		}else {
			parent->rightChild = candidate;
		}
		balance(static_cast<RbNode*>(candidate));
		return;
	}
	if(BinarySearchTree<T, C>::comparator(candidate->element, element)) {
		insert(candidate->leftChild, candidate, element);
	}else {
		insert(candidate->rightChild, candidate, element);
	}
}

template<class T, class C>
void RedBlackTree<T, C>::balance(RbNode *candidate) {
	if(candidate->color == RED) {
		insertCaseOne(candidate);
	}
}

template<class T, class C>
void RedBlackTree<T, C>::insertCaseOne(RbNode *candidate) {
	if(candidate == BinarySearchTree<T, C>::root) {
		candidate->color = BLACK;
	}else {
		insertCaseTwo(candidate);
	}
}

template<class T, class C>
void RedBlackTree<T, C>::insertCaseTwo(RbNode *candidate) {
	RbNode *parent = candidate->getParent();
	if(parent->color == RED) {
		insertCaseThree(candidate, parent);
	}
}

template<class T, class C>
void RedBlackTree<T, C>::insertCaseThree(RbNode *candidate, RbNode *parent) {
	RbNode *grandParent = parent->getParent();
	RbNode *uncle = grandParent->getLeftChild() == parent ? grandParent->getRightChild() : grandParent->getLeftChild();
	if(uncle != &leafSentinel) {
		if(uncle->color == RED) {
			grandParent->color = RED;
			parent->color = BLACK;
			uncle->color = BLACK;
			insertCaseOne(grandParent);
			return;
		}
	}
	insertCaseFour(candidate, parent, grandParent, parent == grandParent->leftChild, candidate == parent->leftChild);
}

template<class T, class C>
void RedBlackTree<T, C>::insertCaseFour(RbNode *candidate, RbNode *parent, RbNode *grandParent, bool parentIsLeft, bool candidateIsLeft) {
	grandParent->color = RED;
	if(parentIsLeft && candidateIsLeft) {
		BstUtility<T, C>::leftLeftCase(parent, this);
		parent->color = BLACK;
	} else if(parentIsLeft) {
		BstUtility<T, C>::leftRightCase(candidate, this);
		candidate->color = BLACK;
	} else if(candidateIsLeft) {
		BstUtility<T, C>::rightLeftCase(candidate, this);
		candidate->color = BLACK;
	} else {
		BstUtility<T, C>::rightRightCase(parent, this);
	}
}

template<class T, class C>
void RedBlackTree<T, C>::remove(RbNode *candidate, T element) {
	if(candidate == &leafSentinel) return;
	if(candidate->element != element) {
		if(BinarySearchTree<T, C>::comparator(candidate->element, element)) remove(candidate->getLeftChild(), element);
		else remove(candidate->getRightChild(), element);
		return;
	}
	RbNode *parent = candidate->getParent();
	if(candidate->rightChild == &leafSentinel || candidate->leftChild == &leafSentinel) {
		RbNode *child = candidate->rightChild == &leafSentinel ? candidate->getLeftChild() : candidate->getRightChild();
		if(candidate->color == BLACK) {
			if(child->color == BLACK) deleteCaseOne(candidate);
			else child->color = BLACK;
		}
		if(parent) {
			if(parent->leftChild == candidate) parent->leftChild = child;
			else parent->rightChild = child;
		} else {
			BinarySearchTree<T, C>::root = child;
		}
		if(child != &leafSentinel) child->parent = parent;
		nodeAllocator.destroy(candidate);
		--BinarySearchTree<T, C>::nodeCount;
	} else {
		T successor = BstUtility<T, C>::preOrderSuccessor(candidate->leftChild, &leafSentinel);
		candidate->element = successor;
		remove(candidate->getLeftChild(), successor);
	}
}

template<class T, class C>
void RedBlackTree<T, C>::deleteCaseOne(RbNode *doubleBlackNode) {
	if(doubleBlackNode == BinarySearchTree<T, C>::root) doubleBlackNode->color = BLACK;
	else deleteCaseTwo(doubleBlackNode);
}

template<class T, class C>
void RedBlackTree<T, C>::deleteCaseTwo(RbNode *doubleBlackNode) {
	RbNode *parent = doubleBlackNode->getParent();
	RbNode *sibling = parent->getLeftChild() == doubleBlackNode ? parent->getRightChild() : parent->getLeftChild();
	if(sibling->color == RED) {
		if(sibling == parent->getLeftChild()) BstUtility<T, C>::leftLeftCase(sibling, this, &leafSentinel);
		else BstUtility<T, C>::rightRightCase(sibling, this, &leafSentinel);
		parent->color = RED;
		sibling->color = BLACK;
		deleteCaseFour(doubleBlackNode, parent);
		return;
	}
	deleteCaseThree(doubleBlackNode, parent, sibling);
}

template<class T, class C>
void RedBlackTree<T, C>::deleteCaseThree(RbNode *doubleBlackNode, RbNode *parent, RbNode *siblng) {
	RbNode *leftNephew = sibling->getLeftChild();
	RbNode *rightNephew = sibling->getRightChild();
	if(parent->color == BLACK && sibling->color == BLACK && leftNephew->color == BLACK && rightNephew->color == BLACK) {
		sibling->color = RED;
		deleteCaseOne(parent);
		return;
	}
	deleteCaseFour(doubleBlackNode, parent);
}

template<class T, class C>
void RedBlackTree<T, C>::deleteCaseFour(RbNode *doubleBlackNode, RbNode *parent) {
	RbNode *sibling = parent->getLeftChild() == doubleBlackNode ? parent->getRightChild() : parent->getLeftChild();
	RbNode *leftNephew = sibling->getLeftChild();
	RbNode *rightNephew = sibling->getRightChild();
	if(parent->color == RED && sibling->color == BLACK && leftNephew->color == BLACK && rightNephew->color == BLACK) {
		sibling->color = RED;
		parent->color = BLACK;
	}else {
		deleteCaseFive(doubleBlackNode, parent, sibling);
	}
}

template<class T, class C>
void RedBlackTree<T, C>::deleteCaseFive(RbNode *doubleBlackNode, RbNode *parent, RbNode *sibling) {
	RbNode *leftNephew = sibling->getLeftChild();
	RbNode *rightNephew = sibling->getRightChild();
	if(parent->getLeftChild() == sibling) {
		if(rightNephew->color == RED) {
			BstUtility<T, C>::rightRightCase(rightNephew, this);
			rightNephew->color = BLACK;
			sibling->color = RED;
		}
	}else {
		if(leftNephew->color == RED) {
			BstUtility<T, C>::leftLeftCase(leftNephew, this);
			leftNephew->color = BLACK;
			sibling->color = RED;
		}
	}
	deleteCaseSix(doubleBlackNode, parent, sibling);
}

template<class T, class C>
void RedBlackTree<T, C>::deleteCaseSix(RbNode *doubleBlackNode, RbNode *parent, RbNode *sibling) {
	RbNode *leftNephew = sibling->getLeftChild();
	RbNode *rightNephew = sibling->getRightChild();
	if(parent->getLeftChild() == sibling) {
		if(leftNephew->color == RED) {
			BstUtility<T, C>::leftLeftCase(sibling, this);
			sibling->color = parent->color;
			parent->color = BLACK;
			leftNephew->color = BLACK;
		}
	}else {
		if(rightNephew->color == RED) {
			BstUtility<T, C>::rightRightCase(sibling, this);
			sibling->color = parent->color;
			parent->color = BLACK;
			rightNephew->color = BLACK;
		}
	}
}

template<class T, class C>
RedBlackTree<T, C>::RedBlackTree(std::size_t noOfElements)
:BinarySearchTree<T, C>()
{
	nodeAllocator.numberOfChunks = noOfElements;
	BinarySearchTree<T, C>::root = &leafSentinel;
	BinarySearchTree<T, C>::leafSentinel = &leafSentinel;
}

template<class T, class C>
void RedBlackTree<T, C>::insert(T element) {
	insert(BinarySearchTree<T, C>::root, BinarySearchTree<T, C>::root, element);
	++BinarySearchTree<T, C>::nodeCount;
}

template<class T, class C>
void RedBlackTree<T, C>::remove(T element) {
	remove(static_cast<RbNode*>(BinarySearchTree<T, C>::root), element);
}

template<class T, class C>
bool RedBlackTree<T, C>::contains(T element) {
	return BstUtility<T, C>::contains(BinarySearchTree<T, C>::root, element, &leafSentinel) != &leafSentinel;
}

template<class T, class C>
std::size_t RedBlackTree<T, C>::size() {
	return BinarySearchTree<T, C>::nodeCount;
}

template<class T, class C>
Vector<T> RedBlackTree<T, C>::treeTraversal(TraversalOrder order) {
	return BstUtility<T, C>::treeTraversal(BinarySearchTree<T, C>::root, order, &leafSentinel);
}

template<class T, class C>
void RedBlackTree<T, C>::clear() {
	if(size() > 0) nodeAllocator.reset();
	BinarySearchTree<T, C>::root = &leafSentinel;
	BinarySearchTree<T, C>::nodeCount = 0;
}