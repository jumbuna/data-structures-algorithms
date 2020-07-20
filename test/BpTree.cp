#include "../include/BpTree.h"
#include "../include/AATree.h"
#include "../include/AvlTree.h"
#include "../include/SplayTree.h"
#include <iostream>

int main() {
	BpTree<int, int, std::greater<int>, AvlTree<int>> tree{3};
	tree.insert(30, 1);
	tree.insert(96, 2);
	tree.insert(25, 3);
	tree.insert(43, 4);
	tree.insert(98, 5);
	tree.insert(61, 6);
	tree.insert(83, 7);
	tree.insert(91, 8);
	tree.insert(15, 9);
	tree.insert(21, 10);
	tree.insert(86, 11);
	tree.insert(44, 12);
	tree.insert(11, 13);
	tree.insert(9, 14);
	tree.insert(6, 15);
	tree.insert(2, 16);
	
	tree.remove(44);
	tree.remove(21);
	tree.remove(98);
	tree.remove(25);
	tree.remove(6);
	tree.remove(15);
	tree.remove(30);
//	tree.remove(2);
//	tree.remove(5);
//	tree.remove(8);
//	tree.remove(1);
//	tree.insert(9000);
	auto v = tree.KeyValuePairs();
	for(int i = 0; i < v.size(); i++) {
//		if(v[i] == 0) {
//			std::cout << "-------------" << std::endl;
//		}else {
			std::cout << v[i].first << " ---> " << v[i].second << std::endl;
//		}
		
	}
}