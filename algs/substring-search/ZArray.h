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
//O(m+n)
void zConstruction(std::string &str, Zarray &array) {
	array.clear();
	array.push_back(0);
	int l = 0;
	for(int i = 1; i < str.length(); i++) {
		int j = l + i;
		while(str[j] == str[l] && j < str.length()) {
			++l;
			++j;
		}
		array.push_back(l);
		if(l <= 1) {
			l = 0;
		}else {
			int k = 1;
			for(; k < l && ((array[k] + i+k) < j); k++) {
				array.push_back(array[k]);
				++i;
			}
			if(i == j) {
				l = 0;
				--i;
			}else {
				l = array[k];
			}
		}
	}
}

Vector<int> ZAlgorithm(std::string &string, std::string &pattern, char separator = '$') {
	Vector<int> vec;
	int patternLength = pattern.length();
	std::string concated;
	concated.append(pattern);
	concated.push_back(separator);
	concated.append(string);
	Zarray array;
	zConstruction(concated, array);
	for(int i = 0; i < array.size(); i++) {
		if(array[i] == patternLength) {
			vec.push_back(i-patternLength-1);
		}
	}
	return vec;
}

Vector<int> ZAlgorithm(std::string &&string, std::string &&pattern, char separator = '$') {
	return ZAlgorithm(string, pattern, separator);
}
}