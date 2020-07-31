#pragma once

#include "../../ds/Vector.h"
#include <string>
#include <iostream>

//linear space complexity
//O(m+n) time complexity

namespace jumbuna {
using KmpTable = Vector<int>;

int kmpSubStringSearch(std::string &string, std::string &pattern, KmpTable &table) {
	int i = 0;
	for(int j = 0; j < string.length(); j++) {
		if(string[j] == pattern[i]) {
			i += 1;
			if(i == table.size()) {
				return (j - i) + 1;
			}
		}else {
			i = i == 0 ? 0 : table[i-1];
			if(string[j] == pattern[i]) {
				i += 1;
			}
		}
	}
	return -1;
}

int kmpSubStringSearch(std::string &&string, std::string &&pattern, KmpTable &table) {
	return kmpSubStringSearch(string, pattern, table);
}

void constructKmpTable(std::string &pattern, KmpTable &table) {
	//table construction
	table.clear();
	int i = 0;
	table.push_back(0);
	for(int j = 1; j < pattern.size(); j++) {
		if(pattern[j] == pattern[i]) {
			table.push_back(++i);
		}else {
			i = i == 0 ? 0 : table[i-1];
			if(pattern[i] == pattern[j]) {
				table.push_back(i+1);
			}else {
				table.push_back(i);
			}
		}
	}
}

void constructKmpTable(std::string &&pattern, KmpTable &table) {
	constructKmpTable(pattern, table);
}

int kmpSubStringSearch(std::string string, std::string pattern) {
	KmpTable table {pattern.length()};
	constructKmpTable(pattern, table);
	return kmpSubStringSearch(string, pattern, table);
}

}
