#include "../include/BinarySearchTree.h"
#include <iostream>

int main() {
	BinarySearchTree<int> bst {5};
	bst.insert(20);
	bst.insert(5);
	bst.insert(99);
	bst.insert(100);
	bst.insert(2);
	
	auto in = bst.treeTraversal();
	
	for(int i = 0; i < in.size(); i++) {
		std::cout << in[i] << std::endl;
	}
}