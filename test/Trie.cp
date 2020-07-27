#include "../ds/Trie.h"
#include <iostream>

using namespace jumbuna;

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
	
//	trie.removePrefix("jo");
	
//	trie.clear();
	
	std::string s1;
	while(true) {
		std::cout << ">>> ";
		std::cin >> s1;
		auto p = trie.wordsWithPrefix(s1);
		if(p.size() != 0) {
			for(int i= 0; i < p.size(); i++) {
				std::cout << p[i] << ", ";
			}
		}else {
			std::cout << "No words found matching '" << s1 << "'" << std::endl;
			//emulate some autocorrect feature :)
			auto c = trie.correctiveText(s1);
			if(c.size() > 0) {
				std::cout << "did you mean?" <<std::endl;
				for(int i = 0; i < c.size(); i++) {
					std::cout << c[i] << ", ";
				}
			}
			
		}
		
		std::cout << std::endl;
//		std::cout << trie.containsFullString(s1) << std::endl;
	}
}