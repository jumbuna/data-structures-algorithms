#pragma once

#include "PoolAllocator.h"
#include "HashMap.h"
#include <string>

struct TrieNode {
	Map<char, TrieNode*> map;
	bool EOW = false; //end of word
};

class Trie {
	void insert(std::string &, size_t, TrieNode *);
	void removeByWord(std::string &, size_t, TrieNode *);
	void removeByPrefix(std::string&, size_t, TrieNode *);
	bool fullStringSearch(std::string&, size_t, TrieNode *);
	bool prefixStringSearch(std::string&, size_t, TrieNode *);
	void recursiveNodeDelete(TrieNode *);
	void findPrefixEndPoint(std::string &, size_t, TrieNode *, Vector<std::string> &);
	void constructWord(std::string &, Vector<std::string> &, TrieNode *);
	TrieNode *root;
	size_t stringCount;
	Allocator<TrieNode> nodeAllocator;
public:
	Trie();
	void insert(std::string);
	void removeWord(std::string);
	void removePrefix(std::string);
	bool containsFullString(std::string);
	bool containsStringPrefix(std::string);
	Vector<std::string> wordsWithPrefix(std::string);
	Vector<std::string> correctiveText(std::string&);
	size_t size();
	void clear();
};

#include "TrieImpl.h"