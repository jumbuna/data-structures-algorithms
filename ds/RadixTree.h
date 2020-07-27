#pragma once

#include "PoolAllocator.h"
#include "HashMap.h"
#include "Vector.h"
#include <string>
#include <algorithm>

namespace jumbuna {
struct RadixNode {
	Map<std::string, RadixNode*> map;
	bool EOW;
};

class RadixTree {
	void insert(std::string &, size_t, RadixNode *);
	void removeByWord(std::string &, size_t, RadixNode *);
	void removeByPrefix(std::string &, size_t, RadixNode *);
	bool fullStringSearch(std::string&, size_t, RadixNode *);
	bool prefixStringSearch(std::string&, size_t, RadixNode *);
	void recursiveNodeDelete(RadixNode *);
	void findPrefixEndPoint(std::string &, size_t, RadixNode *, Vector<std::string> &);
	void constructWord(std::string &, Vector<std::string> &, RadixNode *);
	std::string commonPrefix(std::string, std::string);
	RadixNode *root;
	size_t stringCount;
	Allocator<RadixNode> nodeAllocator;
public:
	RadixTree();
	void insert(std::string);
	void removeWord(std::string);
	void removePrefix(std::string);
	bool containsFullString(std::string);
	bool containsStringPrefix(std::string);
	Vector<std::string> wordsWithPrefix(std::string);
	//lack of a better functionName :)
	Vector<std::string> correctiveText(std::string&);
	size_t size();
	void clear();
};
}

#include "RadixTreeImpl.h"