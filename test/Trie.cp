#include "../include/Trie.h"
#include <iostream>

int main() {
	std::cout.setf(std::ios::boolalpha);
	Trie trie;
	trie.insert("gone");
	trie.insert("gore");
	trie.insert("gum");
	trie.insert("jump");
	trie.insert("john");
	trie.insert("kit");
	trie.insert("cough");
	trie.insert("promise");
	trie.insert("closer");
	trie.insert("function");
	trie.insert("joy");
	trie.insert("joyce");
	trie.insert("joyner");
	trie.insert("joyful");
	trie.insert("join");
	trie.insert("jog");
	trie.insert("jumper");
	
	trie.removePrefix("jo");
	
//	trie.clear();
	
	std::string s1;
	while(true) {
		std::cout << ">>> ";
		std::cin >> s1;
		auto p = trie.wordsWithPrefix(s1);
		for(int i= 0; i < p.size(); i++) {
			std::cout << p[i] << ", ";
		}
		std::cout << std::endl;
//		std::cout << trie.containsFullString(s1) << std::endl;
	}
}