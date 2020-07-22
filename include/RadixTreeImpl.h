#include "RadixTree.h"

void RadixTree::insert(std::string &string, size_t charIndex, RadixNode *candidate) {
	if(charIndex == string.length()) {
		candidate->EOW = true;
		return;
	}
	Vector<std::string> keys = candidate->map.keys();
	bool matchingPrefixFound = false;
	std::string matchingKey;
	for(int i = 0; i < keys.size(); i++) {
		if(keys[i][0] == string[charIndex]) {
			matchingPrefixFound = true;
			matchingKey = keys[i];
		}
	}
	if(matchingPrefixFound) {
		std::string substring = string.substr(charIndex, string.length());
		if(matchingKey.compare(substring) == 0) {
			insert(string, string.length(), candidate->map[matchingKey]);
		}else {
			std::string mp = commonPrefix(matchingKey, substring);
			if(mp.compare(matchingKey) == 0) {
				insert(string, charIndex+mp.length(), candidate->map[matchingKey]);
			}else if(mp.compare(substring) == 0) {
				insert(string, string.length(), candidate->map[matchingKey]);
			}else {
				RadixNode *successor = candidate->map[matchingKey];
				RadixNode *newNode = nodeAllocator.create();
				candidate->map.remove(matchingKey);
				candidate->map[mp] = newNode;
				newNode->map[matchingKey.substr(mp.length(), matchingKey.length())] = successor;
				insert(string, charIndex+mp.length(), newNode);
			}
		}	
	}else {
		RadixNode *node = nodeAllocator.create();
		candidate->map[string.substr(charIndex, string.length())] = node;
		node->EOW = true;
		return;
	}
}

void RadixTree::removeByWord(std::string &string, size_t charIndex, RadixNode *candidate) {
	if(charIndex == string.length()) {
		candidate->EOW = false;
		--stringCount;
		return;
	}
	Vector<std::string> keys = candidate->map.keys();
	for(int i = 0; i < keys.size(); i++) {
		if(keys[i][0] == string[charIndex]) {
			std::string mk = keys[i];
			RadixNode *successor = candidate->map[mk];
			removeByWord(string, charIndex+mk.length(), successor);
			if(successor->map.size() == 0 && !successor->EOW) {
				nodeAllocator.destroy(successor);
				candidate->map.remove(mk);
			}else if(successor->map.size() == 1) {
				std::string successorKey = successor->map.keys()[0];
				candidate->map.remove(mk);
				mk += successorKey;
				candidate->map[mk] = successor->map[successorKey];
				nodeAllocator.destroy(successor);
			}
			break;
		}
	}
}

void RadixTree::removeByPrefix(std::string &prefix, size_t charIndex, RadixNode *candidate) {
	Vector<std::string> keys = candidate->map.keys();
	for(int i = 0; i < keys.size(); i++) {
		if(keys[i][0] == prefix[charIndex]) {
			std::string mk = commonPrefix(keys[i], prefix.substr(charIndex,prefix.length()));
			RadixNode *successor = candidate->map[keys[i]];
			if(charIndex+mk.length() >= prefix.length()) {
				recursiveNodeDelete(successor);
				candidate->map.remove(keys[i]);
			}else {
				removeByPrefix(prefix, charIndex+mk.length(), successor);
				if(successor->map.size() == 0) {
					candidate->map.remove(keys[i]);
					nodeAllocator.destroy(successor);
				}
			}
			break;
		}
	}
}

std::string RadixTree::commonPrefix(std::string s1, std::string s2) {
	int min = std::min(s1.length(), s2.length());
	int i = 0;
	for(; i < min; i++) {
		if(s1[i] != s2[i]) {
			break;
		}
	}
	return s1.substr(0, i);
}

bool RadixTree::fullStringSearch(std::string &string, size_t charIndex, RadixNode *candidate) {
	if(charIndex == string.length()) {
		return candidate->EOW;
	}
	Vector<std::string> keys = candidate->map.keys();
	for(int i = 0; i < keys.size(); i++) {
		if(keys[i][0] == string[charIndex]) {
			return fullStringSearch(string, charIndex+keys[i].length(), candidate->map[keys[i]]);
		}
	}
	return false;
}

bool RadixTree::prefixStringSearch(std::string &prefix, size_t charIndex, RadixNode *candidate) {
	Vector<std::string> keys = candidate->map.keys();
	for(int i = 0; i < keys.size(); i++) {
		if(keys[i][0] == prefix[charIndex]) {
			std::string mk = commonPrefix(keys[i], prefix.substr(charIndex, prefix.length()));
			if(mk.length()+charIndex == prefix.length()) {
				return true;
			}else if(keys[i].length() >= prefix.length()-charIndex) {
				return false;
			}else {
				return prefixStringSearch(prefix, charIndex+mk.length(), candidate->map[keys[i]]);
			}
		}
	}
	return false;
}

void RadixTree::findPrefixEndPoint(std::string &prefix, size_t charIndex, RadixNode *candidate, Vector<std::string> &vector) {
	Vector<std::string> keys = candidate->map.keys();
	for(int i = 0; i < keys.size(); i++) {
		if(keys[i][0] == prefix[charIndex]) {
			std::string mk = commonPrefix(keys[i], prefix.substr(charIndex, prefix.length()));
			if(charIndex+mk.length() == prefix.length()) {
				std::string sp = prefix.substr(0, charIndex) + keys[i];
				constructWord(sp, vector, candidate->map[keys[i]]);
			}else {
				findPrefixEndPoint(prefix, charIndex+mk.length(), candidate->map[keys[i]], vector);
			}
			break;
		}
	}
}

void RadixTree::constructWord(std::string &prefix, Vector<std::string> &vector, RadixNode *candidate) {
	if(candidate->EOW) {
		vector.push_back(prefix);
	}
	Vector<std::string> keys = candidate->map.keys();
	for(int i = 0; i < keys.size(); i++) {
		std::string newPrefix = prefix+keys[i];
		constructWord(newPrefix, vector, candidate->map[keys[i]]);
	}
}

void RadixTree::recursiveNodeDelete(RadixNode *candidate) {
	Vector<std::string> keys = candidate->map.keys();
	for(int i = 0; i < keys.size(); i++) {
		recursiveNodeDelete(candidate->map[keys[i]]);
		candidate->map.remove(keys[i]);
	}
	if(candidate->EOW) {
		--stringCount;
	}
	nodeAllocator.destroy(candidate);
}

RadixTree::RadixTree()
:stringCount(0)
{
	root = nodeAllocator.create();
}

void RadixTree::insert(std::string string) {
	insert(string, 0, root);
	++stringCount;
}

bool RadixTree::containsFullString(std::string string) {
	return fullStringSearch(string, 0, root);
}

bool RadixTree::containsStringPrefix(std::string prefix) {
	return prefixStringSearch(prefix, 0, root);
}

void RadixTree::removePrefix(std::string prefix) {
	if(prefixStringSearch(prefix, 0, root))
	removeByPrefix(prefix, 0, root);
}

Vector<std::string> RadixTree::wordsWithPrefix(std::string prefix) {
	Vector<std::string> vector;
	if(containsStringPrefix(prefix)) {
		findPrefixEndPoint(prefix, 0, root, vector);
	}
	return vector;
}

void RadixTree::removeWord(std::string string) {
	if(containsFullString(string)) {
		removeByWord(string, 0, root);
	}
}

size_t RadixTree::size() {
	return stringCount;
}

void RadixTree::clear() {
	Vector<std::string> keys = root->map.keys();
	for(int i = 0; i < keys.size(); i++) {
		recursiveNodeDelete(root->map[keys[i]]);
		root->map.remove(keys[i]);
	}
}