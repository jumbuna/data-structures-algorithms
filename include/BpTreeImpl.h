#include "BpTree.h"

template<class K, class V, class C, class B>
BpTreeNode<K, V, C, B>::BpTreeNode(Node *parent, size_t order)
:parent(parent), keys(*keyAllocator.create(order)), children(*childrenAllocator.create(order+1)), previousNode(nullptr), nextNode(nullptr)
{}

template<class K, class V, class C, class B>
bool BpTreeNode<K, V, C, B>::nodePtrComparator::operator()(Node *n1, Node *n2) {
	//compare the first keys in both nodes 
	return C{}(n1->keys.getSmallestElement(), n2->keys.getSmallestElement());
}

template<class K, class V, class C, class B>
void BpTreeNode<K, V, C, B>::insertData(K key, V value) {
	//insert key into both the map and the keys Bst
	keys.insert(key);
	data[key] = value;
}

template<class K, class V, class C, class B>
void BpTreeNode<K, V, C, B>::removeKey(K key) {
	//remove key from both the map and keys Bst
	keys.remove(key);
	data.remove(key);
}

template<class K ,class V, class C, class B>
bool Utility<K, V, C, B>::isLeaf(Node *candidate) {
	//leaf nodes have no children
	return candidate->children.size() == 0;
	//also
//	return candidate->data.size() != 0;
}

template<class K , class V, class C, class B>
bool Utility<K, V, C, B>::isOverFlow(Node *candidate, size_t order) {
	//number of keys equals to tree order
	return candidate->keys.size() == order;
}

template<class K , class V, class C, class B>
bool Utility<K, V, C, B>::isUnderFlow(Node *candidate, size_t order) {
	//number of keys is less than ceil(order/2)-1
	return candidate->keys.size() < ceil(order/2.0)-1;
}

template<class K , class V, class C, class B>
BpTreeNode<K, V, C, B>* Utility<K, V, C, B>::successorChild(Node *candidate, K key) {
	//node's first key compared to key satisfies comparator condition
	if(C{}(candidate->keys.getSmallestElement(), key)) {
		return candidate->children.getSmallestElement();
	}else if(!C{}(candidate->keys.getLargestElement(), key)) {
		//none of keys in node satisfy comparator condition when compared to the key
		return candidate->children.getLargestElement();
	}else {
		//find the first key in the node which satisfies comparator condition
		Vector<K> keys = candidate->keys.treeTraversal();
		Vector<Node*> children = candidate->children.treeTraversal();
		for(int i = 1; i < keys.size(); i++) {
			//children[i] = nodes whose keys are less than keys[i]
			if(C{}(keys[i], key)) {
				return children[i];
			}
		}
	}
	//unreachable code
	return nullptr;
}

template<class K , class V, class C, class B>
BpTreeNode<K, V, C, B>* Utility<K, V, C, B>::findInternalKeyNode(Node *candidate, K key) {
	//follow parent until root node or node with keys is reached
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
	//first key in tree
	if(!candidate) {
		//assign root & first to equal first node
		root = nodeAllocator.create(nullptr, treeOrder);
		root->insertData(key, value);
		firstLeaf = root;
		return;
	}
	
	if(Util::isLeaf(candidate)) {
		//reached leaf
		candidate->insertData(key, value);
		//fix a possible overflowing leaf node 
		postInsertLeafNode(candidate);
		return;
	}else {
		//internal node on path to leaf node
		insert(Util::successorChild(candidate, key), key, value);
	}
	//fix a possible overflowing internal node
	postInsertInternalNode(candidate);
}

template<class K , class V, class C, class B>
void BpTree<K, V, C, B>::postInsertLeafNode(Node *candidate) {
	//only when leaf is overflowing
	if(Util::isOverFlow(candidate, treeOrder)) {
		//parent of the new nodes to be created
		Node *parent = candidate->parent ? candidate->parent : candidate;
		//index of middle key/splitting key index
		int midian = treeOrder/2;
		//create new nodes
		Node *leftChild = nodeAllocator.create(parent, treeOrder);
		Node *rightChild = nodeAllocator.create(parent, treeOrder);
		//sorted
		Vector<K> keys = candidate->keys.treeTraversal();
		Vector<Node*> children = candidate->children.treeTraversal();
		for(int i = 0; i < keys.size(); i++) {
			if(i < midian) {
				//first half of keys go to the left
				leftChild->insertData(keys[i], candidate->data[keys[i]]);
			}else {
				//rest of keys including the splitting go to the right
				rightChild->insertData(keys[i], candidate->data[keys[i]]);
			}
		}
		//assign/re-assign leaf node pointers
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
		if(candidate == firstLeaf) {
			//left becomes new first key
			firstLeaf = leftChild;
		}
		
		if(parent == candidate) {
			//candidate is the root node also
			//remove values since values are only stored in leaf node
			root->data.~Map();
			root->children.clear();
			root->keys.clear();
			root->keys.insert(keys[midian]);
			root->children.insert(leftChild);
			root->children.insert(rightChild);
			//only for leaf nodes
			root->nextNode = root->previousNode = nullptr;
		}else {
			//push splitting key to parent
			parent->keys.insert(keys[midian]);
			//remove old child and add the two new children
			parent->children.remove(candidate);
			parent->children.insert(leftChild);
			parent->children.insert(rightChild);
			//free memory
			nodeAllocator.destroy(candidate);
		}
	}
}

template<class K , class V, class C, class B>
void BpTree<K, V, C, B>::postInsertInternalNode(Node *candidate) {
	//only if overflowing
	if(Util::isOverFlow(candidate, treeOrder)) {
		Node *parent = candidate->parent ? candidate->parent : candidate;
		//index of splitting key
		int midian = treeOrder/2;
		Node *leftChild = nodeAllocator.create(parent, treeOrder);
		Node *rightChild = nodeAllocator.create(parent, treeOrder);
		Vector<K> keys = candidate->keys.treeTraversal();
		Vector<Node*> children = candidate->children.treeTraversal();
		for(int i = 0; i < keys.size(); i++) {
			//keys before splitting key move to the left child
			if(i < midian) {
				leftChild->keys.insert(keys[i]);
			}else if(i > midian) {
				//keys after move to righ node
				rightChild->keys.insert(keys[i]);
			}
		}
		for(int i = 0; i < children.size(); i++) {
			if(i <= midian) {
				//children before move to left
				leftChild->children.insert(children[i]);
				children[i]->parent = leftChild;
			}else {
				rightChild->children.insert(children[i]);
				children[i]->parent = rightChild;
			}
		}
		
		if(parent == candidate) {
			//candidate is the root
			root->children.clear();
			root->keys.clear();
			root->keys.insert(keys[midian]);
			root->children.insert(leftChild);
			root->children.insert(rightChild);
		}else {
			//push splitting key to parent
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
			//prevent key re-insertion incase where internal node is parent and key was removed during a merge
			if(internalNode->keys.contains(key)) {
				internalNode->keys.remove(key);
				internalNode->keys.insert(nn->keys.getSmallestElement());
			}	
		}
		return;
	}else {
		remove(Util::successorChild(candidate, key), key);
	}
	postRemoveInternalNode(candidate);
}

template<class K , class V, class C, class B>
BpTreeNode<K, V, C, B>* BpTree<K, V, C, B>::postRemoveLeafNode(Node *candidate) {
	if(Util::isUnderFlow(candidate, treeOrder)) {
		Node *parent = candidate->parent;
		Vector<K> keys = parent->keys.treeTraversal();
		Vector<Node*> children = parent->children.treeTraversal();
		return leafNodeRemoveCaseOne(candidate, keys, children);
	}
	return candidate;
}

template<class K , class V, class C, class B>
BpTreeNode<K, V, C, B>* BpTree<K, V, C, B>::leafNodeRemoveCaseOne(Node *candidate, Vector<K> &keys, Vector<Node *> &siblings) {
	//left sibling check
	int index = siblings.indexOf(candidate);
	if(index != 0) {
		Node *sibling = siblings[index-1];
		if(sibling->keys.size() > ceil(treeOrder/2.0)-1) {
			borrowKeyFromLeftLeafNode(candidate, sibling);
			Node *parent = candidate->parent;
			parent->keys.remove(keys[index-1]);
			parent->keys.insert(candidate->keys.getSmallestElement());
			return candidate;
		}
	}
	return leafNodeRemoveCaseTwo(candidate, keys, siblings);
}

template<class K , class V, class C, class B>
BpTreeNode<K, V, C, B>* BpTree<K, V, C, B>::leafNodeRemoveCaseTwo(Node *candidate, Vector<K> &keys, Vector<Node *> &siblings) {
	int index = siblings.indexOf(candidate);
	if(index != siblings.size()-1) {
		Node *sibling = siblings[index+1];
		if(sibling->keys.size() > ceil(treeOrder/2.0)-1) {
			borrowKeyFromRightLeafNode(candidate, sibling);
			Node *parent = candidate->parent;
			parent->keys.remove(keys[index]);
			parent->keys.insert(sibling->keys.getSmallestElement());
			return candidate;
		}
	}
	return leafNodeRemoveCaseThree(candidate, keys, siblings);
}

template<class K , class V, class C, class B>
BpTreeNode<K, V, C, B>* BpTree<K, V, C, B>::leafNodeRemoveCaseThree(Node *candidate, Vector<K> &keys, Vector<Node *> &siblings) {
	Node *parent = candidate->parent;
	int index = siblings.indexOf(candidate);
	if(index == 0) {
		Node *sibling = siblings[1];
		mergeLeafNodes(candidate, sibling);
		parent->children.remove(sibling);
		parent->keys.remove(keys[index]);
		nodeAllocator.destroy(sibling);
		return candidate;
	}else {
		Node *sibling = siblings[index-1];
		mergeLeafNodes(sibling, candidate);
		if(candidate->keys.size() == 0) {
			candidate->keys.insert(keys[index-1]);
		}
		parent->children.remove(candidate);
		parent->keys.remove(keys[index-1]);
		nodeAllocator.destroy(candidate);
		return sibling;
	}
}

template<class K , class V, class C, class B>
void BpTree<K, V, C, B>::borrowKeyFromLeftLeafNode(Node *candidate, Node *sibling) {
	K largestKey = sibling->keys.getLargestElement();
	candidate->insertData(largestKey, sibling->data[largestKey]);
	sibling->removeKey(largestKey);
}

template<class K , class V, class C, class B>
void BpTree<K, V, C, B>::borrowKeyFromRightLeafNode(Node *candidate, Node *sibling) {
	K smallestKey = sibling->keys.getSmallestElement();
	candidate->insertData(smallestKey, sibling->data[smallestKey]);
	sibling->removeKey(smallestKey);
}

template<class K , class V, class C, class B>
void BpTree<K, V, C, B>::mergeLeafNodes(Node *candidate, Node *sibling) {
	Vector<K> keys = sibling->keys.treeTraversal();
	for(int i = 0; i < keys.size(); i++) {
		candidate->insertData(keys[i], sibling->data[keys[i]]);
	}
	candidate->nextNode = sibling->nextNode;
	if(sibling->nextNode) {
		(*sibling->nextNode).previousNode = candidate;
	}
}

template<class K , class V, class C, class B>
void BpTree<K, V, C, B>::postRemoveInternalNode(Node *candidate) {
	if(!Util::isUnderFlow(candidate, treeOrder)) {
		return;
	}
	if(candidate == root) {
		if(candidate->keys.size() == 0) {
			root = candidate->children.getSmallestElement();
			root->parent = nullptr;
		}
		return;
	}
	Node *parent = candidate->parent;
	Vector<K> keys = parent->keys.treeTraversal();
	Vector<Node*> children = parent->children.treeTraversal();
	internalNodeRemoveCaseOne(candidate, keys, children);
}

template<class K , class V, class C, class B>
void BpTree<K, V, C, B>::internalNodeRemoveCaseOne(Node *candidate, Vector<K> &keys, Vector<Node *> &siblings) {
	//left sibling check
	int index = siblings.indexOf(candidate);
	if(index != 0) {
		Node *sibling = siblings[index-1];
		if(sibling->keys.size() > ceil(treeOrder/2.0)-1) {
			borrowKeyFromLeftInternalNode(candidate, sibling, keys[index-1]);
			return;
		}
	}
	internalNodeRemoveCaseTwo(candidate, keys, siblings);
}

template<class K , class V, class C, class B>
void BpTree<K, V, C, B>::internalNodeRemoveCaseTwo(Node *candidate, Vector<K> &keys, Vector<Node *> &siblings) {
	int index = siblings.indexOf(candidate);
	if(index != siblings.size()-1) {
		Node *sibling = siblings[index+1];
		if(sibling->keys.size() > ceil(treeOrder/2.0)-1) {
			borrowKeyFromRightInternalNode(candidate, sibling, keys[index]);
			return;
		}
	}
	internalNodeRemoveCaseThree(candidate, keys, siblings);
}

template<class K , class V, class C, class B>
void BpTree<K, V, C, B>::internalNodeRemoveCaseThree(Node *candidate, Vector<K> &keys, Vector<Node *> &siblings) {
	Node *parent = candidate->parent;
	int index = siblings.indexOf(candidate);
	if(index == 0) {
		Node *sibling = siblings[1];
		mergeInternalNodes(candidate, sibling, keys[0]);
		parent->children.remove(sibling);
		parent->keys.remove(keys[0]);
		nodeAllocator.destroy(sibling);
	}else {
		Node *sibling = siblings[index-1];
		mergeInternalNodes(sibling, candidate, keys[index-1]);
		if(candidate->keys.size() == 0) {
			candidate->keys.insert(keys[index-1]);
		}
		parent->children.remove(candidate);
		parent->keys.remove(keys[index-1]);
		nodeAllocator.destroy(candidate);
	}
}

template<class K , class V, class C, class B>
void BpTree<K, V, C, B>::borrowKeyFromLeftInternalNode(Node *candidate, Node *sibling, K parentKey) {
	Node *parent = candidate->parent;
	Node *largestChild = sibling->children.getLargestElement();
	K largestKey = sibling->keys.getLargestElement();
	candidate->keys.insert(parentKey);
	parent->keys.remove(parentKey);
	parent->keys.insert(largestKey);
	sibling->keys.remove(largestKey);
	sibling->children.remove(largestChild);
	candidate->children.insert(largestChild);
	largestChild->parent = candidate;
}

template<class K , class V, class C, class B>
void BpTree<K, V, C, B>::borrowKeyFromRightInternalNode(Node *candidate, Node *sibling, K parentKey) {
	Node *parent = candidate->parent;
	Node *smallestChild = sibling->children.getSmallestElement();
	K smallestKey = sibling->keys.getSmallestElement();
	candidate->keys.insert(parentKey);
	parent->keys.remove(parentKey);
	parent->keys.insert(smallestKey);
	sibling->keys.remove(smallestKey);
	sibling->children.remove(smallestChild);
	candidate->children.insert(smallestChild);
	smallestChild->parent = candidate;
}

template<class K , class V, class C, class B>
void BpTree<K, V, C, B>::mergeInternalNodes(Node *candidate, Node *sibling, K parentKey) {
	candidate->keys.insert(parentKey);
	Vector<K> keys = sibling->keys.treeTraversal();
	Vector<Node *> children = sibling->children.treeTraversal();
	for(int i = 0; i < keys.size(); i++) {
		candidate->keys.insert(keys[i]);
	}
	for(int i = 0; i < children.size(); i++) {
		candidate->children.insert(children[i]);
		children[i]->parent = candidate;
	}
}

template<class K , class V, class C, class B>
BpTree<K, V, C, B>::BpTree(size_t order)
:treeOrder(order), root(nullptr), keyCount(0), firstLeaf(nullptr)
{
	nodeAllocator.numberOfChunks = 128;
}

template<class K , class V, class C, class B>
void BpTree<K, V, C, B>::insert(K key, V value) {
	insert(root, key, value);
	++keyCount;
}

template<class K , class V, class C, class B>
void BpTree<K, V, C, B>::remove(K key) {
	if(contains(key)) {
		remove(root, key);
		--keyCount;
	}
}

template<class K , class V, class C, class B>
bool BpTree<K, V, C, B>::contains(K key) {
	if(root == nullptr) {
		return false;
	}
	Node *temp = root;
	while(!Util::isLeaf(temp)) {
		if(temp->keys.contains(key)) {
			return true;
		}
		temp = Util::successorChild(temp, key);
	}
	return temp->keys.contains(key);
}

template<class K , class V, class C, class B>
size_t BpTree<K, V, C, B>::size() {
	return keyCount;
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

template<class K, class V, class C, class B>
Vector<std::pair<K, V>> BpTree<K, V, C, B>::KeyValuePairs() {
	Vector<std::pair<K, V>> vector;
	if(firstLeaf == nullptr) {
		return vector;
	}
	Node *temp = firstLeaf;
	while(temp) {
		Vector<K> keys = temp->keys.treeTraversal();
		for(int i = 0; i<keys.size(); i++) {
			vector.push_back({keys[i], temp->data[keys[i]]});
		}
		temp = temp->nextNode;
	}
	return vector;
}