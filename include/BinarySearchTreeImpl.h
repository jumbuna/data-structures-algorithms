#include "BinarySearchTree.h"

template<class T>
BstNode<T>::BstNode(T element)
:element(element), rightChild(nullptr), leftChild(nullptr)
{}

template<class T>
void BinarySearchTree<T>::insert(Node *&candidate, Node *&parent, T &element) {
	if(!candidate && !parent) {
		root = nodeAllocator.create(element);
		return;
	}
	
	if(!candidate) {
		if(parent->element > element) {
			parent->leftChild = nodeAllocator.create(element);
		}else {
			parent->rightChild = nodeAllocator.create(element);
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
void BinarySearchTree<T>::removeNode(Node *&candidate, Node *&parent, T &element) {
	if(!candidate) {
		return;
	}
	if(candidate->element != element) {
		if(candidate->element > element) {
			removeNode(candidate->leftChild, candidate, element);
		}else {
			removeNode(candidate->rightChild, candidate, element);
		}
		return;
	}
	
	if(!candidate->rightChild) {
		if(parent) {
			if(parent->element > element) {
				parent->leftChild = candidate->leftChild;
			}else {
				parent->rightChild = candidate->leftChild;
			}
		}
		nodeAllocator.destroy(candidate);
	}else if(!candidate->leftChild) {
		if(parent) {
			if(parent->element > element) {
				parent->leftChild = candidate->rightChild;
			}else {
				parent->rightChild = candidate->rightChild;
			}
		}
		nodeAllocator.destroy(candidate);
	}else {
		T &successor = preOrderSuccessor(candidate->leftChild);
		candidate->element = successor;
		removeNode(candidate->leftChild, candidate, successor);
	}	
}

template<class T>
T& BinarySearchTree<T>::preOrderSuccessor(Node *&leftChild) {
	while(leftChild->rightChild) {
		leftChild = leftChild->rightChild;
	}
	return leftChild->element;
}

template<class T>
void BinarySearchTree<T>::inOrderTraversal(Node *startingNode, Vector<T> &vector) {
	if(startingNode) {
		inOrderTraversal(startingNode->leftChild, vector);
		vector.push_back(startingNode->element);
		inOrderTraversal(startingNode->rightChild, vector);
	}
}

template<class T>
void BinarySearchTree<T>::postOrderTraversal(Node *startingNode, Vector<T> &vector) {
	if(startingNode) {
		inOrderTraversal(startingNode->leftChild, vector);
		inOrderTraversal(startingNode->rightChild, vector);
		vector.push_back(startingNode->element);
	}
}

template<class T>
void BinarySearchTree<T>::preOrderTraversal(Node *startingNode, Vector<T> &vector) {
	if(startingNode) {
		vector.push_back(startingNode->element);
		inOrderTraversal(startingNode->leftChild, vector);
		inOrderTraversal(startingNode->rightChild, vector);
	}
}

template<class T>
void BinarySearchTree<T>::levelOrderTraversal(Node *startintNode, Vector<T> &vector) {
	if(startintNode) {
		Queue<Node*> q;
		q.push(startintNode);
		while(!q.empty()) {
			Node *temp = q.pop();
			if(temp->leftChild) {
				q.push(temp->leftChild);
			}
			if(temp->rightChild) {
				q.push(temp->rightChild);
			}
			vector.push_back(temp->element);
		}
	}	
}

template<class T>
BinarySearchTree<T>::BinarySearchTree(std::size_t noOfElements)
:BinarySearchTree()
{
	nodeAllocator.numberOfChunks = noOfElements;
}

template<class T>
BinarySearchTree<T>::BinarySearchTree()
:root(nullptr), nodeCount(0)
{}

template<class T>
void BinarySearchTree<T>::insert(T element) {
	insert(root, root, element);
	++nodeCount;
}

template<class T>
void BinarySearchTree<T>::remove(T element) {
	if(contains(element)) {
		removeNode(root, root, element);
		if(--nodeCount == 0) {
			root = nullptr;
		}
	}
}

template<class T>
bool BinarySearchTree<T>::contains(T element) {
	if(root) {
		Node *temp = root;
		while(temp) {
			if(temp->element == element) {
				return true;
			}
			if(temp->element > element) {
				temp = temp->leftChild;
			}else {
				temp = temp->rightChild;
			}
		}
	}
	
	return false;
}

template<class T>
std::size_t BinarySearchTree<T>::size() {
	return nodeCount;
}

template<class T>
Vector<T> BinarySearchTree<T>::treeTraversal(TraversalOrder order) {
	Vector<T> vector;
	if(root == nullptr) {
		return vector;
	}
	switch(order) {
		case IN:
			inOrderTraversal(root, vector);
			break;
		case POST:
			postOrderTraversal(root, vector);
			break;
		case PRE:
			preOrderTraversal(root, vector);
			break;
		case LEVEL:
			levelOrderTraversal(root, vector);
	}
	return vector;
}
