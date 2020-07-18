#include "BpTree.h"

template<class K, class V, class C, class B>
BpTreeNode<K, V, C, B>::BpTreeNode(Node *parent, size_t order)
:parent(parent), keys(*keyAllocator.create(order)), children(*childrenAllocator.create(order+1)), previousNode(nullptr), nextNode(nullptr)
{}

template<class K, class V, class C, class B>
bool BpTreeNode<K, V, C, B>::nodePtrComparator::operator()(Node *n1, Node *n2) {
	return C{}(n1->keys.getSmallestElement(), n2->keys.getSmallestElement());
}

template<class K, class V, class C, class B>
void BpTreeNode<K, V, C, B>::insertData(K key, V value) {
	keys.insert(key);
	data[key] = value;
}

template<class K, class V, class C, class B>
void BpTreeNode<K, V, C, B>::removeKey(K key) {
	keys.remove(key);
	data.remove(key);
}

template<class K ,class V, class C, class B>
bool Utility<K, V, C, B>::isLeaf(Node *candidate) {
	return candidate->children.size() == 0;
}

template<class K , class V, class C, class B>
bool Utility<K, V, C, B>::isOverFlow(Node *candidate, size_t order) {
	return candidate->keys.size() == order;
}

template<class K , class V, class C, class B>
bool Utility<K, V, C, B>::isUnderFlow(Node *candidate, size_t order) {
	return candidate->keys.size() < ceil(order/2.0-1);
}

template<class K , class V, class C, class B>
BpTreeNode<K, V, C, B>* Utility<K, V, C, B>::successorChild(Node *candidate, K key) {
	if(C{}(candidate->keys.getSmallestElement(), key)) {
		return candidate->children.getSmallestElement();
	}else if(!C{}(candidate->keys.getLargestElement(), key)) {
		return candidate->children.getLargestElement();
	}else {
		Vector<K> keys = candidate->keys.treeTraversal();
		Vector<Node*> children = candidate->children.treeTraversal();
		for(int i = 1; i < keys.size(); i++) {
			if(C{}(keys[i], key)) {
				return children[i];
			}
		}
	}
	return nullptr;
}

template<class K , class V, class C, class B>
BpTreeNode<K, V, C, B>* Utility<K, V, C, B>::findInternalKeyNode(Node *candidate, K key) {
	if(candidate) {
		candidate = candidate->parent;
		while(candidate) {
			if(candidate->keys.contains(key)) {
				return candidate;
			}
			candidate = candidate->parent;
		}
	}
	return nullptr;
}

template<class K , class V, class C, class B>
void BpTree<K, V, C, B>::insert(Node *candidate, K key, V value) {
	if(!candidate) {
		root = nodeAllocator.create(nullptr, treeOrder);
		root->insertData(key, value);
		return;
	}
	
	if(Util::isLeaf(candidate)) {
		candidate->insertData(key, value);
		postInsertLeafNode(candidate);
		return;
	}else {
		insert(Util::successorChild(candidate, key), key, value);
	}
	
	postInsertInternalNode(candidate);
}

template<class K , class V, class C, class B>
void BpTree<K, V, C, B>::postInsertLeafNode(Node *candidate) {
	if(Util::isOverFlow(candidate, treeOrder)) {
		Node *parent = candidate->parent ? candidate->parent : candidate;
		int midian = treeOrder/2;
		Node *leftChild = nodeAllocator.create(parent, treeOrder);
		Node *rightChild = nodeAllocator.create(parent, treeOrder);
		Vector<K> keys = candidate->keys.treeTraversal();
		Vector<Node*> children = candidate->children.treeTraversal();
		for(int i = 0; i < keys.size(); i++) {
			if(i < midian) {
				leftChild->insertData(keys[i], candidate->data[keys[i]]);
			}else {
				rightChild->insertData(keys[i], candidate->data[keys[i]]);
			}
		}
		leftChild->nextNode = rightChild;
		rightChild->previousNode = leftChild;
		leftChild->previousNode = candidate->previousNode;
		rightChild->nextNode = candidate->nextNode;
		if(candidate->previousNode) {
			(*candidate->previousNode).nextNode = leftChild;
		}
		if(candidate->nextNode) {
			(*candidate->nextNode).previousNode = rightChild;
		}
		
		if(parent == candidate) {
			root = candidate;
			root->data.~Map();
			root->children.clear();
			root->keys.clear();
			root->keys.insert(keys[midian]);
			root->children.insert(leftChild);
			root->children.insert(rightChild);
			root->nextNode = root->previousNode = nullptr;
		}else {
			parent->keys.insert(keys[midian]);
			parent->children.remove(candidate);
			nodeAllocator.destroy(candidate);
			parent->children.insert(leftChild);
			parent->children.insert(rightChild);
		}
	}
}

template<class K , class V, class C, class B>
void BpTree<K, V, C, B>::postInsertInternalNode(Node *candidate) {
	if(Util::isOverFlow(candidate, treeOrder)) {
		Node *parent = candidate->parent ? candidate->parent : candidate;
		int midian = treeOrder/2;
		Node *leftChild = nodeAllocator.create(parent, treeOrder);
		Node *rightChild = nodeAllocator.create(parent, treeOrder);
		Vector<K> keys = candidate->keys.treeTraversal();
		Vector<Node*> children = candidate->children.treeTraversal();
		for(int i = 0; i < keys.size(); i++) {
			if(i < midian) {
				leftChild->keys.insert(keys[i]);
			}else if(i > midian) {
				rightChild->keys.insert(keys[i]);
			}
		}
		
		for(int i = 0; i < children.size(); i++) {
			if(i <= midian) {
				leftChild->children.insert(children[i]);
				children[i]->parent = leftChild;
			}else {
				rightChild->children.insert(children[i]);
				children[i]->parent = rightChild;
			}
		}
		
		if(parent == candidate) {
			root = candidate;
			root->children.clear();
			root->keys.clear();
			root->keys.insert(keys[midian]);
			root->children.insert(leftChild);
			root->children.insert(rightChild);
		}else {
			parent->keys.insert(keys[midian]);
			parent->children.remove(candidate);
			nodeAllocator.destroy(candidate);
			parent->children.insert(leftChild);
			parent->children.insert(rightChild);
		}
	}
}


template<class K , class V, class C, class B>
void BpTree<K, V, C, B>::remove(Node *candidate, K key) {
	if(!candidate) {
		return;
	}
	if(candidate->keys.contains(key) && Util::isLeaf(candidate)) {
		candidate->removeKey(key);
		if(candidate == root) {
			return;
		}
		Node *internalNode = Util::findInternalKeyNode(candidate, key);
		Node *nn = postRemoveLeafNode(candidate);
		if(internalNode) {
			internalNode->keys.remove(key);
			internalNode->keys.insert(nn->keys.getSmallestElement());
		}
		return;
	}else {
		remove(Util::successorChild(candidate, key));
	}
	postRemoveInternalNode(candidate);
}

template<class K , class V, class C, class B>
void BpTree<K, V, C, B>::postRemoveLeafNode(Node *candidate) {
	if(Util::isUnderFlow(candidate, treeOrder)) {
		Node *parent = candidate->parent;
		Vector<K> keys = parent->keys.treeTraversal();
		Vector<K> children = parent->children.treeTraversal();
		leafNodeRemoveCaseOne(candidate, keys, children);
	}
}

template<class K , class V, class C, class B>
Node* BpTree<K, V, C, B>::leafNodeRemoveCaseOne(Node *candidate, Vector<K> &keys, Vector<Node *> &siblings) {
	//left sibling check
	int index = siblings.indexOf(candidate);
	if(index != 0) {
		Node *sibling = siblings[index-1];
		if(sibling->keys.size() > ceil(treeOrder/2.0)-1) {
			borrowKeyFromLeftLeafNode(candidate, sibling);
			return candidate;
		}
	}
	leafNodeRemoveCaseTwo(candidate, keys, siblings);
}

template<class K , class V, class C, class B>
Node* BpTree<K, V, C, B>::leafNodeRemoveCaseTwo(Node *candidate, Vector<K> &keys, Vector<Node *> &siblings) {
	int index = siblings.indexOf(candidate);
	if(index != siblings.size()-1) {
		Node *sibling = siblings[index+1];
		if(sibling->keys.size() > ceil(treeOrder/2.0)-1) {
			borrowKeyFromRightLeafNode(candidate, sibling);
			return candidate;
		}
	}
	leafNodeRemoveCaseThree(candidate, keys, siblings);
}

template<class K , class V, class C, class B>
Node* BpTree<K, V, C, B>::leafNodeRemoveCaseThree(Node *candidate, Vector<K> &pkeys, Vector<Node *> &siblings) {
	int index = siblings.indexOf(candidate);
	if(index == 0) {
		Node *sibling = siblings[1];
		mergeLeafNodes(candidate, sibling);
	}else {
		
	}
}





























































template<class K , class V, class C, class B>
BpTree<K, V, C, B>::BpTree(size_t order)
:treeOrder(order), root(nullptr), keyCount(0)
{
	nodeAllocator.numberOfChunks = 128;
}

template<class K , class V, class C, class B>
void BpTree<K, V, C, B>::insert(K key, V value) {
	insert(root, key, value);
	++keyCount;
}

template<class K, class V, class C, class B>
Vector<K> BpTree<K, V, C, B>::treeTraversal(TraversalOrder order) {
	Vector<K> vector;
	if(root == nullptr) {
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
		Vector<K> keys = temp->keys.treeTraversal();
		vector.append(&keys);
		vector.push_back(0);
	}
	return vector;
}
