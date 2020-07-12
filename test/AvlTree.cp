#include "../include/AvlTree.h"
#include <iostream>

int main() {
	AvlTree<int> bst {5};
	for(int i = 1; i < 11; i++) {
		bst.insert(i);
	}
	
	bst.remove(8);
	bst.remove(4);
	bst.remove(6);
	bst.remove(7);
	
	auto in = bst.treeTraversal(LEVEL_ORDER);
	
	for(int i = 0; i < in.size(); i++) {
		std::cout << in[i] << std::endl;
	}
}