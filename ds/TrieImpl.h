#include "Trie.h"

using namespace jumbuna;

void Trie::insert(std::string &string, size_t charIndex, TrieNode *candidate) {
	if(charIndex == string.length()) {
		candidate->EOW = true;
	}else {
		char k = string[charIndex++];
		if(candidate->map.contains(k)) {
			insert(string, charIndex, candidate->map[k]);
		}else {
			TrieNode *node = nodeAllocator.create();
			candidate->map[k] = node;
			insert(string, charIndex, node);
		}
	}
}

void Trie::removeByWord(std::string &string, size_t charIndex, TrieNode *candidate) {
	if(charIndex == string.length() && candidate->EOW) {
		candidate->EOW = false;
		return;
	}
	char k = string[charIndex++];
	TrieNode *successor = candidate->map[k];
	removeByWord(string, charIndex, successor);
	if(successor->map.size() == 0 && !successor->EOW) {
		candidate->map.remove(k);
		nodeAllocator.destroy(successor);
	}
}

void Trie::removeByPrefix(std::string &string, size_t charIndex, TrieNode *candidate) {
	if(charIndex == string.length()) {
		Vector<char> keys = candidate->map.keys();
		for(int i = 0; i < keys.size(); i++) {
			recursiveNodeDelete(candidate->map[keys[i]]);
			candidate->map.remove(keys[i]);
		}
		return;
	}	
	char k = string[charIndex++];
	TrieNode *successor = candidate->map[k];
	removeByPrefix(string, charIndex, successor);
	if(successor->map.size() == 0) {
		candidate->map.remove(k);
		nodeAllocator.destroy(successor);
	}
}

bool Trie::fullStringSearch(std::string &string, size_t charIndex, TrieNode *candidate) {
	if(charIndex == string.length()) {
		return candidate->EOW;
	}
	char k = string[charIndex++];
	if(candidate->map.contains(k)) {
		return fullStringSearch(string, charIndex, candidate->map[k]);
	}else {
		return false;
	}
}

bool Trie::prefixStringSearch(std::string &string, size_t charIndex, TrieNode *candidate) {
	if(charIndex == string.length()) {
		return true;
	}
	char k = string[charIndex++];
	if(candidate->map.contains(k)) {
		return prefixStringSearch(string, charIndex, candidate->map[k]);
	}else {
		return false;
	}
}

void Trie::recursiveNodeDelete(TrieNode *candidate) {
	Vector<char> keys = candidate->map.keys();
	for(int i = 0;i < keys.size(); i++) {
		recursiveNodeDelete(candidate->map[keys[i]]);
		candidate->map.remove(keys[i]);
	}
	if(candidate->EOW) {
		--stringCount;
	}
	nodeAllocator.destroy(candidate);
}

void Trie::findPrefixEndPoint(std::string &prefix, size_t charIndex, TrieNode *candidate, Vector<std::string> &vector) {
	if(charIndex == prefix.length()) { 
		constructWord(prefix, vector, candidate);
	}else {
		char k = prefix[charIndex++];
		findPrefixEndPoint(prefix, charIndex, candidate->map[k], vector);
	}
}

void Trie::constructWord(std::string &prefix, Vector<std::string> &vector, TrieNode *candidate) {
	if(candidate->EOW) {
		vector.push_back(prefix);
	}
	Vector<char> keys = candidate->map.keys();
	for(int i = 0; i < keys.size(); i++) {
		std::string newPrefix = prefix + keys[i];
		constructWord(newPrefix, vector, candidate->map[keys[i]]);
	}
}

Trie::Trie()
:stringCount(0)
{
	root = nodeAllocator.create();
}

void Trie::insert(std::string string) {
	insert(string, 0, root);
	++stringCount;
}

void Trie::removeWord(std::string string) {
	if(fullStringSearch(string, 0, root)) {
		removeByWord(string, 0, root);
		--stringCount;
	}
}

void Trie::removePrefix(std::string prefix) {
	if(prefixStringSearch(prefix, 0, root)) {
		removeByPrefix(prefix, 0, root);
	}
}

bool Trie::containsFullString(std::string string) {
	return fullStringSearch(string, 0, root);
}

bool Trie::containsStringPrefix(std::string prefix) {
	return prefixStringSearch(prefix, 0, root);
}

size_t Trie::size() {
	return stringCount;
}

void Trie::clear() {
	Vector<char> keys = root->map.keys();
	for(int i = 0; i < keys.size(); i++) {
		recursiveNodeDelete(root->map[keys[i]]);
		root->map.remove(keys[i]);
	}
	stringCount = 0;
}

Vector<std::string> Trie::wordsWithPrefix(std::string prefix) {
	Vector<std::string> vector;
	if(containsStringPrefix(prefix)) {
		findPrefixEndPoint(prefix, 0, root, vector);
		return vector;
	}
	return vector;
}

Vector<std::string> Trie::correctiveText(std::string &string) {
	//emulation of auto correct :)
	size_t length = string.length();
	size_t halfWay = length/2;
	for(;length >= halfWay; --length) {
		std::string prefix = string.substr(0, length);
		if(containsStringPrefix(prefix)) {
			return wordsWithPrefix(prefix);
		}
	}
	return Vector<std::string>{};
}