#pragma once

#include <string>
#include "../../ds/Vector.h"

namespace jumbuna {
using Zarray = Vector<int>;
//O(n^2)
void lazyZconstruction(std::string &str, Zarray &array) {
	array.clear();
	array.push_back(0);
	for(int i = 1; i  < str.length(); i++) {
		int l = 0;
		int j = i;
		while(str[j] == str[l] && j < str.length()) {
			++j;
			++l;
		}
		array.push_back(l);
	}
}

Vector<int> zAlgorithmSearch(std::string &string, std::string &pattern, char separator = '$') {
	Vector<int> vec;
	int patternLength = pattern.length();
	std::string concated;
	concated.append(pattern);
	concated.push_back(separator);
	concated.append(string);
	Zarray array;
	//(m+n) time z-array construction
	array.push_back(0);
	int previousMatches = 0;
	for(int i = 1; i < concated.length(); i++) {
		int mismatchIndex = previousMatches + i;
		while(concated[mismatchIndex] == concated[previousMatches] && mismatchIndex < concated.length()) {
			++previousMatches;
			++mismatchIndex;
		}
		array.push_back(previousMatches);
		if(previousMatches == patternLength) {
			vec.push_back(array.size() - patternLength - 2);
		}
		if(previousMatches <= 1) {
			previousMatches = 0;
		}else {
			int k = 1;
			for(; k < previousMatches && ((array[k] + i+k) < mismatchIndex); k++) {
				array.push_back(array[k]);
				++i;
			}
			if(i == mismatchIndex) {
				previousMatches = 0;
				--i;
			}else {
				previousMatches = array[k];
			}
		}
	}
	
	return vec;
}

Vector<int> zAlgorithmSearch(std::string &&string, std::string &&pattern, char separator = '$') {
	return zAlgorithmSearch(string, pattern, separator);
}
}