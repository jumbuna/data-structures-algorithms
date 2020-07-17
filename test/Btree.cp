#include "../include/Btree.h"
#include <iostream>

int main() {
	Btree<int> tree{7};
	for(int i = 1; i < 100; i++) {
		tree.insert(i);
	}
	tree.remove(6);
	tree.remove(4);
	tree.remove(3);
	tree.remove(10);
	tree.remove(11);
	tree.remove(9);
	tree.remove(7);
	tree.remove(2);
	tree.remove(5);
	tree.remove(8);
	tree.remove(1);
	tree.insert(9000);
	auto v = tree.treeTraversal();
	for(int i = 0; i < v.size(); i++)
		std::cout << v[i] << std::endl;
}