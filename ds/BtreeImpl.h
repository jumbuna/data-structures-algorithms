#include "Btree.h"

template<class T, class C, class B>
T Utility<T, C, B>::preOrderSuccessor(Node *candidate) {
	while(!isLeaf(candidate)) {
		candidate = candidate->children.getLargestElement();
	}
	return candidate->keys.getLargestElement();
}

template<class T, class C, class B>
BtreeNode<T, C, B>::BtreeNode(BtreeNode<T, C, B> *parent, std::size_t order)
:parent(parent), keys(*nodeAllocator.create(order)), children(*rbAllocator.create(order+1))
{}

template<class T, class C, class B>
bool BtreeNode<T, C, B>::NodePointerComparator::operator()(BtreeNode<T, C, B> *n1, BtreeNode<T, C, B> *n2) {
	//compare first keys of given node
	return C{}(n1->keys.getSmallestElement(), n2->keys.getSmallestElement());
}

template<class T, class C, class B>
bool Utility<T, C, B>::isOverflow(BtreeNode<T, C, B> *candidate, std::size_t treeOrder) {
	return candidate->keys.size() == treeOrder;
}

template<class T, class C, class B>
bool Utility<T, C, B>::isUnderflow(BtreeNode<T, C, B> *candidate, std::size_t treeOrder) {
	return candidate->keys.size() < (ceil(treeOrder/2.0)-1);
}

template<class T, class C, class B>
bool Utility<T, C, B>::isLeaf(BtreeNode<T, C, B> *candidate) {
	return candidate->children.size() == 0;
}

template<class T, class C, class B>
BtreeNode<T, C, B>* Utility<T, C, B>::successorChild(BtreeNode<T, C, B> *candidate, T element) {
	if(C{}(candidate->keys.getSmallestElement(), element)) {
		return candidate->children.getSmallestElement();
	}else if(!C{}(candidate->keys.getLargestElement(), element)) {
		return candidate->children.getLargestElement();
	}else {
		Vector<T> keys = candidate->keys.treeTraversal();
		Vector<BtreeNode<T, C, B>*> children = candidate->children.treeTraversal();
		for(int i = 1; i < keys.size(); i++) {
			if(C{}(keys[i], element)) {
				return children[i];
			}
		}
	}
	return nullptr;
}

template<class T, class C, class B>
void Btree<T, C, B>::insert(Node *candidate, Node *parent, T element) {
	if(!candidate && !parent) {
		root = nodeAllocator.create(parent, treeOrder);
		root->keys.insert(element);
		return;
	}
	if(Utility<T, C, B>::isLeaf(candidate)) {
		candidate->keys.insert(element);
	}else {
		Node *successor = Util::successorChild(candidate, element);
		insert(successor, candidate, element);
	}
	
	postInsertBalance(candidate);
}

template<class T, class C, class B>
void Btree<T, C, B>::postInsertBalance(Node *candidate) {
	if(Utility<T, C, B>::isOverflow(candidate, treeOrder)) {
		Vector<T> elements = candidate->keys.treeTraversal(IN_ORDER);
		Vector<Node*> children = candidate->children.treeTraversal(IN_ORDER);
		std::size_t midian = treeOrder/2;
		Node *parent = candidate->parent ? candidate->parent : candidate;
		Node *leftHalf = nodeAllocator.create(parent, treeOrder);
		Node *rightHalf = nodeAllocator.create(parent, treeOrder);
		for(int i = 0; i < elements.size(); i++) {
			if(i < midian) {
				leftHalf->keys.insert(elements[i]);
			}else if(i > midian) {
				rightHalf->keys.insert(elements[i]);
			}
		}
		for(int i = 0; i < children.size(); i++) {
			if(i <= midian) {
				leftHalf->children.insert(children[i]);
				children[i]->parent = leftHalf;
			}else {
				rightHalf->children.insert(children[i]);
				children[i]->parent = rightHalf;
			}
		}
		if(parent == candidate) {
			candidate->keys.clear();
			candidate->children.clear();
			candidate->keys.insert(elements[midian]);
			candidate->children.insert(leftHalf);
			candidate->children.insert(rightHalf);
			root = candidate;
			root->parent = nullptr;
		}else {
			parent->keys.insert(elements[midian]);
			parent->children.remove(candidate);
			parent->children.insert(leftHalf);
			parent->children.insert(rightHalf);
			nodeAllocator.destroy(candidate);
		}
	}
}

template<class T, class C, class B>
void Btree<T, C, B>::remove(Node *candidate, T element) {
	if(candidate == nullptr) {
		return;
	}
	if(candidate->keys.contains(element)) {
		if(Utility<T, C, B>::isLeaf(candidate)) {
			candidate->keys.remove(element);
		}else {
			Vector<T> keys = candidate->keys.treeTraversal();
			Vector<Node *> children = candidate->children.treeTraversal();
			int index = keys.indexOf(element);
			T successor = Util::preOrderSuccessor(children[index]);
			candidate->keys.remove(element);
			candidate->keys.insert(successor);
			remove(children[index], successor);
		}
	}else {
		remove(Util::successorChild(candidate, element), element);
	}
	
	postRemoveBalance(candidate);
}

template<class T, class C, class B>
void Btree<T, C, B>::postRemoveBalance(Node *candidate) {
	if(!Util::isUnderflow(candidate, treeOrder)) {
		return;
	}
	if(candidate == root) {
		if(candidate->keys.size() == 0) {
			if(candidate->children.size() == 1) {
				root = candidate->children.getSmallestElement();
				nodeAllocator.destroy(candidate);
				root->parent = nullptr;
			}
		}
		return;
	}
	Node *parent = candidate->parent;
	Vector<T> keys = parent->keys.treeTraversal();
	Vector<Node *> children = parent->children.treeTraversal();
	removeCaseOne(candidate, keys, children);
}

template<class T, class C, class B>
void Btree<T, C, B>::removeCaseOne(Node *candidate, Vector<T> &keys, Vector<Node *> &siblings) {
	//left sibling
	int index = siblings.indexOf(candidate);
	if(index != 0) {
		Node *sibling = siblings[index-1];
		if(sibling->keys.size() > ceil(treeOrder/2.0-1)) {
			borrowKeyFromLeftSibling(candidate, sibling, keys[index-1]);
			return;
		}
	}
	removeCaseTwo(candidate, keys, siblings);
}

template<class T, class C, class B>
void Btree<T, C, B>::removeCaseTwo(Node *candidate, Vector<T> &keys, Vector<Node *> &siblings) {
	//right sibling
	int index = siblings.indexOf(candidate);
	if(index != siblings.size()-1) {
		Node *sibling = siblings[index+1];
		if(sibling->keys.size() > ceil(treeOrder/2.0-1)) {
			borrowKeyFromRightSibling(candidate, sibling, keys[index]);
			return;
		}
	}
	removeCaseThree(candidate, keys, siblings);
}

template<class T, class C, class B>
void Btree<T, C, B>::removeCaseThree(Node *candidate, Vector<T> &keys, Vector<Node *> &siblings) {
	Node *parent = candidate->parent;
	int index = siblings.indexOf(candidate);
	if(index == 0) {
		Node *sibling = siblings[index+1];
		mergeSiblings(candidate, sibling, keys[index]);
		parent->children.remove(sibling);
		nodeAllocator.destroy(sibling);
		parent->keys.remove(keys[index]);
	}else {
		Node *sibling = siblings[index-1];
		mergeSiblings(sibling, candidate, keys[index-1]);
		if(candidate->keys.size() == 0) {
			//3-4 tree which can have nodes with 0 keys
			candidate->keys.insert(keys[index-1]);
		}
		parent->children.remove(candidate);
		nodeAllocator.destroy(candidate);
		parent->keys.remove(keys[index-1]);
	}
}

template<class T, class C, class B>
void Btree<T, C, B>::borrowKeyFromLeftSibling(Node *candidate, Node *sibling, T parentKey) {
	Node *parent = candidate->parent;
	candidate->keys.insert(parentKey);
	parent->keys.remove(parentKey);
	T largestKey = sibling->keys.getLargestElement();
	parent->keys.insert(largestKey);
	sibling->keys.remove(largestKey);
	if(!Util::isLeaf(sibling)) {
		Node *largestChild = sibling->children.getLargestElement();
		largestChild->parent = candidate;
		candidate->children.insert(largestChild);
	}
}

template<class T, class C, class B>
void Btree<T, C, B>::borrowKeyFromRightSibling(Node *candidate, Node *sibling, T parentKey) {
	Node *parent = candidate->parent;
	candidate->keys.insert(parentKey);
	parent->keys.remove(parentKey);
	T smallestKey = sibling->keys.getSmallestElement();
	parent->keys.insert(smallestKey);
	sibling->keys.remove(smallestKey);
	if(!Util::isLeaf(sibling)) {
		Node *smallestChild = sibling->children.getSmallestElement();
		smallestChild->parent = candidate;
		candidate->children.insert(smallestChild);
	}
}

template<class T, class C, class B>
void Btree<T, C, B>::mergeSiblings(Node *candidate, Node *sibling, T parentKey) {
	Vector<T> keys = sibling->keys.treeTraversal();
	Vector<Node *> children = sibling->children.treeTraversal();
	for(int i = 0; i < keys.size(); i++) {
		candidate->keys.insert(keys[i]);
	}
	for(int i = 0; i < children.size(); i++) {
		candidate->children.insert(children[i]);
		children[i]->parent = candidate;
	}
	candidate->keys.insert(parentKey);
}

template<class T, class C, class B>
Btree<T, C, B>::Btree(std::size_t order) 
:root(nullptr), elementCount(0), treeOrder(order)
{
	order = std::max(order, (std::size_t) 3);
	nodeAllocator.numberOfChunks = 20;
}

template<class T, class C, class B>
void Btree<T, C, B>::insert(T element) {
	insert(root, root, element);
	++elementCount;
}

template<class T, class C, class B>
void Btree<T, C, B>::remove(T element) {
	if(contains(element)) {
		remove(root, element);
		--elementCount;
	}
}

template<class T, class C, class B>
bool Btree<T, C, B>::contains(T element) {
	if(size()  > 0) {
		Node *temp = root;
		while(temp) {
			if(Util::isLeaf(temp)) {
				return temp->keys.contains(element);
			}
			if(temp->keys.contains(element)) {
				return true;
			}else {
				temp = Util::successorChild(temp, element);
			}
		}
	}
	return false;
}

template<class T, class C, class B>
std::size_t Btree<T, C, B>::size() {
	return elementCount;
}

template<class T, class C, class B>
Vector<T> Btree<T, C, B>::treeTraversal(TraversalOrder order) {
	Vector<T> vector;
	if(size() == 0) {
		return vector;
	}
	Queue<Node*> qu;
	qu.push(root);
	while(!qu.empty()) {
		Node *temp = qu.pop();
		Vector<Node *> children = temp->children.treeTraversal();
		for(int i = 0; i < children.size(); i++) {
			qu.push(children[i]);
		}
		Vector<T> keys = temp->keys.treeTraversal();
		vector.append(&keys);
	}
	return vector;
}