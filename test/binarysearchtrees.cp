#include "../include/AvlTree.h"
#include "../include/AATree.h"
#include "../include/SplayTree.h"
#include "../include/RedBlackTree.h"
#include "../include/UnbalancedBinarySearchTree.h"
#include <iostream>

struct comp {
	bool operator()(int x, int y) {
		std::cout << "called";
		return x>y;
	}
};

int main() {
//	UnbalancedBinarySearchTree<int> tree {11};
//	AvlTree<int> tree {11};
//	RedBlackTree<int> tree {11};
//	AATree<int> tree {11};
	SplayTree<int> tree {11};
	
	BinarySearchTree<int> &bst = tree;
	for(int i = 1; i < 11; i++) {
		bst.insert(i);
	}
	
	bst.remove(8);
	bst.remove(4);
	bst.remove(5);
	bst.remove(7);
	bst.remove(2);
	bst.remove(1);
	bst.remove(6);
	
	auto in = bst.treeTraversal();
	
	for(int i = 0; i < in.size(); i++) {
		std::cout << in[i] << std::endl;
	}
}