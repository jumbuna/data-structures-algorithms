#include "RedBlackTree.h"

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

template<class T>
void RedBlackTree<T>::insert(Node *candidate, Node *parent, T element) {
	if(candidate == &leafSentinel && parent == &leafSentinel) {
		candidate = nodeAllocator.create(element, nullptr, &leafSentinel); 
		BinarySearchTree<T>::root = candidate;
	}else if(candidate == &leafSentinel) {
		candidate = nodeAllocator.create(element, parent, &leafSentinel);
		if(parent->element > element) {
			parent->leftChild = candidate;
		}else {
			parent->rightChild = candidate;
		}
	}else {
		if(candidate->element > element) {
			insert(candidate->leftChild, candidate, element);
		}else {
			insert(candidate->rightChild, candidate, element);
		}
	}
		
	balance(static_cast<RbNode*>(candidate));
}

template<class T>
void RedBlackTree<T>::balance(RbNode *candidate) {
	if(candidate->color == BLACK) {
		return;
	}
	insertCaseOne(candidate);
}

template<class T>
void RedBlackTree<T>::insertCaseOne(RbNode *candidate) {
	if(candidate == BinarySearchTree<T>::root) {
		candidate->color = BLACK;
	}else {
		insertCaseTwo(candidate);
	}
}

template<class T>
void RedBlackTree<T>::insertCaseTwo(RbNode *candidate) {
	RbNode *parent = candidate->getParent();
	if(parent->color == RED) {
		insertCaseThree(candidate, parent);
	}
}

template<class T>
void RedBlackTree<T>::insertCaseThree(RbNode *candidate, RbNode *parent) {
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
	insertCaseFour(candidate, parent);
}

template<class T>
void RedBlackTree<T>::insertCaseFour(RbNode *candidate, RbNode *parent) {
	RbNode *grandParent = parent->getParent();
	if(grandParent->getLeftChild() == parent) {
		if(candidate == parent->getLeftChild()) {
			BstUtility<T>::leftLeftCase(parent, this);
			parent->color = BLACK;
			grandParent->color = RED;
		}else {
			BstUtility<T>::leftRightCase(parent, this);
			candidate->color = BLACK;
			grandParent->color = RED;
		}
	}else {
		if(candidate == parent->getRightChild()) {
			BstUtility<T>::rightRightCase(parent, this);
			parent->color = BLACK;
			grandParent->color = RED;
		}else {
			BstUtility<T>::rightLeftCase(parent, this);
			candidate->color = BLACK;
			grandParent->color = RED;
		}
	}
}

template<class T>
void RedBlackTree<T>::remove(RbNode *candidate, T element) {
	if(candidate == &leafSentinel) {
		return;
	}
	if(candidate->element != element) {
		if(candidate->element > element) {
			remove(candidate->getLeftChild(), element);
		}else {
			remove(candidate->getRightChild(), element);
		}
		return;
	}
	
	RbNode *parent = candidate->getParent();
	if(candidate->rightChild == &leafSentinel && candidate->leftChild == &leafSentinel) {
		if(candidate->color == BLACK) {
			deleteCaseOne(candidate);
		}
		if(parent) {
			parent->getLeftChild() == candidate ? parent->leftChild = &leafSentinel : parent->rightChild = &leafSentinel;
		}
		
	}else if(candidate->rightChild == &leafSentinel) {
		RbNode *leftChild = candidate->getLeftChild();
		if(candidate->color == BLACK) {
			leftChild->color = BLACK;
		}
		if(parent) {
			parent->getLeftChild() == candidate ? parent->leftChild = leftChild : parent->rightChild = leftChild;
		}else {
			BinarySearchTree<T>::root = leftChild;
		}
		leftChild->parent = parent;
		nodeAllocator.destroy(candidate);
	} else if(candidate->leftChild == &leafSentinel) {
		RbNode *rightChild = candidate->getRightChild();
		if(candidate->color == BLACK) {
			rightChild->color = BLACK;
		}
		if(parent) {
			parent->getLeftChild() == candidate ? parent->leftChild = rightChild : parent->rightChild = rightChild;
		}else {
			BinarySearchTree<T>::root = rightChild;
		}
		rightChild->parent = parent;
		nodeAllocator.destroy(candidate);
	}else {
		T successor = BstUtility<T>::preOrderSuccessor(candidate->leftChild, &leafSentinel);
		candidate->element = successor;
		remove(candidate->getLeftChild(), successor);
	}
}

template<class T>
void RedBlackTree<T>::deleteCaseOne(RbNode *doubleBlackNode) {
	if(doubleBlackNode == BinarySearchTree<T>::root) {
		doubleBlackNode->color = BLACK;
	}else {
		deleteCaseTwo(doubleBlackNode);
	}
}

template<class T>
void RedBlackTree<T>::deleteCaseTwo(RbNode *doubleBlackNode) {
	RbNode *parent = doubleBlackNode->getParent();
	RbNode *sibling = parent->getLeftChild() == doubleBlackNode ? parent->getRightChild() : parent->getLeftChild();
	if(sibling->color == RED) {
		if(sibling == parent->getLeftChild()) {
			BstUtility<T>::leftLeftCase(sibling, this, &leafSentinel);
		}else {
			BstUtility<T>::rightRightCase(sibling, this, &leafSentinel);
		}
		parent->color = RED;
		sibling->color = BLACK;
	}
	deleteCaseThree(doubleBlackNode);
}

template<class T>
void RedBlackTree<T>::deleteCaseThree(RbNode *doubleBlackNode) {
	RbNode *parent = doubleBlackNode->getParent();
	RbNode *sibling = parent->getLeftChild() == doubleBlackNode ? parent->getRightChild() : parent->getLeftChild();
	RbNode *leftNephew = sibling->getLeftChild();
	RbNode *rightNephew = sibling->getRightChild();
	if(parent->color == BLACK && sibling->color == BLACK && leftNephew->color == BLACK && rightNephew->color == BLACK) {
		sibling->color = RED;
		deleteCaseOne(parent);
	}else {
		deleteCaseFour(doubleBlackNode);
	}
}

template<class T>
void RedBlackTree<T>::deleteCaseFour(RbNode *doubleBlackNode) {
	RbNode *parent = doubleBlackNode->getParent();
	RbNode *sibling = parent->getLeftChild() == doubleBlackNode ? parent->getRightChild() : parent->getLeftChild();
	RbNode *leftNephew = sibling->getLeftChild();
	RbNode *rightNephew = sibling->getRightChild();
	if(parent->color == RED && sibling->color == BLACK && leftNephew->color == BLACK && rightNephew->color == BLACK) {
		sibling->color = RED;
		parent->color = BLACK;
	}else {
		deleteCaseFive(doubleBlackNode);
	}
}

template<class T>
void RedBlackTree<T>::deleteCaseFive(RbNode *doubleBlackNode) {
	RbNode *parent = doubleBlackNode->getParent();
	RbNode *sibling = parent->getLeftChild() == doubleBlackNode ? parent->getRightChild() : parent->getLeftChild();
	RbNode *leftNephew = sibling->getLeftChild();
	RbNode *rightNephew = sibling->getRightChild();
	if(parent->getLeftChild() == sibling) {
		if(rightNephew->color == RED) {
			BstUtility<T>::rightRightCase(rightNephew, this);
			rightNephew->color = BLACK;
			sibling->color = RED;
		}
	}else {
		if(leftNephew->color == RED) {
			BstUtility<T>::leftLeftCase(leftNephew, this);
			leftNephew->color = BLACK;
			sibling->color = RED;
		}
	}
	deleteCaseSix(doubleBlackNode);
}

template<class T>
void RedBlackTree<T>::deleteCaseSix(RbNode *doubleBlackNode) {
	RbNode *parent = doubleBlackNode->getParent();
	RbNode *sibling = parent->getLeftChild() == doubleBlackNode ? parent->getRightChild() : parent->getLeftChild();
	RbNode *leftNephew = sibling->getLeftChild();
	RbNode *rightNephew = sibling->getRightChild();
	if(parent->getLeftChild() == sibling) {
		if(leftNephew->color == RED) {
			BstUtility<T>::leftLeftCase(sibling, this);
			sibling->color = parent->color;
			parent->color = BLACK;
			leftNephew->color = BLACK;
		}
	}else {
		if(rightNephew->color == RED) {
			BstUtility<T>::rightRightCase(sibling, this);
			sibling->color = parent->color;
			parent->color = BLACK;
			rightNephew->color = BLACK;
		}
	}
}

template<class T>
RedBlackTree<T>::RedBlackTree(std::size_t noOfElements)
:BinarySearchTree<T>()
{
	nodeAllocator.numberOfChunks = noOfElements;
	BinarySearchTree<T>::root = &leafSentinel;
}

template<class T>
void RedBlackTree<T>::insert(T element) {
	insert(BinarySearchTree<T>::root, BinarySearchTree<T>::root, element);
	++BinarySearchTree<T>::nodeCount;
}

template<class T>
void RedBlackTree<T>::remove(T element) {
	if(contains(element)) {
		remove(static_cast<RbNode*>(BinarySearchTree<T>::root), element);
		if(--BinarySearchTree<T>::nodeCount == 0) {
			BinarySearchTree<T>::root = &leafSentinel;
		}
	}
}

template<class T>
bool RedBlackTree<T>::contains(T element) {
	return BstUtility<T>::contains(BinarySearchTree<T>::root, element, &leafSentinel) != &leafSentinel;
}

template<class T>
std::size_t RedBlackTree<T>::size() {
	return BinarySearchTree<T>::nodeCount;
}

template<class T>
Vector<T> RedBlackTree<T>::treeTraversal(TraversalOrder order) {
	return BstUtility<T>::treeTraversal(BinarySearchTree<T>::root, order, &leafSentinel);
}
