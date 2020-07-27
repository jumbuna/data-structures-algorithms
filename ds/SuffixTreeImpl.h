#include "SuffixTree.h"

using namespace jumbuna;

SuffixNode* SuffixTree::insert(std::string &suffix, size_t charIndex, SuffixNode *candidate) {
	if(charIndex == suffix.length()) {
		return candidate;
	}
	Vector<std::string> keys = candidate->map.keys();
	for(int i = 0; i < keys.size(); i++) {
		if(keys[i][0] == suffix[charIndex]) {
			std::string mp = matchingPrefix(keys[i], suffix.substr(charIndex, suffix.length()));
			std::string nk = keys[i].substr(mp.length()-1, keys[i].length());
			SuffixNode *newnode = nodeAllocator.create();
			newnode->map[nk] = candidate->map[keys[i]];
			candidate->map.remove(keys[i]);
			candidate->map[mp] = newnode;
			return insert(suffix, charIndex+mp.length(), newnode);
		}
	}
	SuffixNode *newnode = nodeAllocator.create();
	candidate->map[suffix.substr(charIndex, suffix.length())] = newnode;
	return newnode; 
}

std::string SuffixTree::matchingPrefix(std::string s1, std::string s2) {
	size_t min = std::min(s1.length(), s2.length());
	int i = 0;
	for(; i < min; i++) {
		if(s1[i] != s2[i]) {
			break;
		}
	}
	return s1.substr(0, i);
}

bool SuffixTree::searchPrefix(std::string &string, size_t charIndex, SuffixNode *candidate) {
	Vector<std::string> keys = candidate->map.keys();
	for(int i = 0; i < keys.size(); i++) {
		if(keys[i][0] == string[charIndex]) {
			std::string mp = matchingPrefix(keys[i], string.substr(charIndex, string.length()));
			if(mp.length()+charIndex == string.length()) {
				return true;
			}else if(keys[i].length() >= string.length()-charIndex) {
				return false;
			}else {
				return searchPrefix(string, charIndex+mp.length(), candidate->map[keys[i]]);
			}
		}
	}
	return false;
}

void SuffixTree::SubStringStartingKey(std::string &prefix, size_t charIndex, SuffixNode *candidate, Vector<int> &vector) {
	if(prefix.length() <= charIndex) {
		findSubStringStartingPosition(vector, candidate);
	}else {
		Vector<std::string> keys = candidate->map.keys();
		for(int i = 0; i < keys.size(); i++) {
			if(keys[i][0] == prefix[charIndex]) {
				SubStringStartingKey(prefix, charIndex+keys[i].length(), candidate->map[keys[i]], vector);
			}
		}
	}
}

void SuffixTree::findSubStringStartingPosition(Vector<int> &vector, SuffixNode * candidate) {
	Vector<std::string> keys = candidate->map.keys();
	for(int i = 0; i < keys.size(); i++) {
		if(candidate->map[keys[i]]->position != -1) {
			vector.push_back(candidate->map[keys[i]]->position);
		}
//		findSubStringStartingPosition(vector, candidate->map[keys[i]]);
	}
//	if(candidate->position != -1) {
//		vector.push_back(candidate->position);
//	}
}

SuffixTree::SuffixTree(std::string caseString) {
	root = nodeAllocator.create();
	std::string suffix;
	for(int i = 0; i < caseString.length(); i++) {
		suffix = caseString.substr(i, caseString.length()) + '$';
		insert(suffix, 0, root)->position = i;
	}
}

bool SuffixTree::containsSubString(std::string subString) {
//	subString += '$';
	return searchPrefix(subString, 0, root);
}

Vector<int> SuffixTree::subStringPositions(std::string subString) {
	Vector<int> vector;
	if(containsSubString(subString)) {
		SubStringStartingKey(subString, 0, root, vector);
	}
	return vector;
}

//void SuffixTree::print() {
//	print(root);
//}
//
//void SuffixTree::print(SuffixNode *candidate) {
//	Vector<std::string> keys = candidate->map.keys();
//	for(int i = 0; i < keys.size(); i++) {
//		std::cout << keys[i] << std::endl;
//	}
//	std::cout << candidate->position;
//	std::cout << "\n-----------------------------------\n";
//	
//	for(int i = 0; i < keys.size(); i++) {
//		print(candidate->map[keys[i]]);
//	}
//	
//}