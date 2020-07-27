#pragma once

#include "PoolAllocator.h"
#include "HashMap.h"
#include <string>
#include <iostream>
namespace jumbuna {
struct SuffixNode {
	Map<std::string, SuffixNode *> map;
	int position = -1;
};

class SuffixTree {
	Allocator<SuffixNode> nodeAllocator;
	SuffixNode *insert(std::string &, size_t, SuffixNode *);
	std::string matchingPrefix(std::string, std::string);
	bool searchPrefix(std::string &, size_t, SuffixNode *);
	void SubStringStartingKey(std::string &, size_t, SuffixNode *, Vector<int> &);
	void findSubStringStartingPosition(Vector<int> &, SuffixNode *); 
	SuffixNode *root;
//	void print(SuffixNode *);
public:
	SuffixTree(std::string);
	bool containsSubString(std::string);
	Vector<int> subStringPositions(std::string);
//	void print();
};
}
#include "SuffixTreeImpl.h"