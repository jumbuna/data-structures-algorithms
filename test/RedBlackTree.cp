#include "../include/RedBlackTree.h"
#include <iostream>

int main() {
	RedBlackTree<int> bst {10};
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