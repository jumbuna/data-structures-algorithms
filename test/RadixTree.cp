#include "../ds/RadixTree.h"
#include <iostream>

using namespace jumbuna;

int main() {
	RadixTree tree;
	tree.insert("romane");
	tree.insert("romanus");
	tree.insert("romulus");
	tree.insert("rubens");
	tree.insert("ruber");
	tree.insert("rubicon");
	tree.insert("rubicundus");
	
	tree.removeWord("romane");
	
//	tree.clear();
	
	while (true) {
		std::string s1;
		std::cout << ">>> ";
		std::cin >> s1;
		auto v = tree.wordsWithPrefix(s1);
		for(int i = 0; i < v.size(); i++) {
			std::cout << v[i] << ", ";
		}
		std::cout << std::endl;
	}
}