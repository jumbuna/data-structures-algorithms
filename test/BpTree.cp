#include "../include/BpTree.h"
#include <iostream>

int main() {
	BpTree<int, int> tree{3};
//	for(int i = 1; i < 10; i++) {
//		tree.insert(i, i);
//	}
	tree.insert(30);
	tree.insert(96);
	tree.insert(25);
	tree.insert(43);
	tree.insert(98);
	tree.insert(61);
	tree.insert(83);
	tree.insert(91);
	tree.insert(15);
	tree.insert(21);
	tree.insert(86);
	tree.insert(44);
	tree.insert(11);
	tree.insert(9);
	tree.insert(6);
	tree.insert(2);
//	tree.remove(6);
//	tree.remove(4);
//	tree.remove(3);
//	tree.remove(10);
//	tree.remove(11);
//	tree.remove(9);
//	tree.remove(7);
//	tree.remove(2);
//	tree.remove(5);
//	tree.remove(8);
//	tree.remove(1);
//	tree.insert(9000);
	auto v = tree.treeTraversal();
	for(int i = 0; i < v.size(); i++) {
		if(v[i] == 0) {
			std::cout << "-------------" << std::endl;
		}else {
			std::cout << v[i] << std::endl;
		}
		
	}
}