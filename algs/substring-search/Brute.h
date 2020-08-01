#pragma once

//constant space complexity
//O(mn) time complexity

#include <string>

namespace jumbuna {
int bruteSearch(std::string string, std::string pattern) {
	for(int i = 0; i < string.length(); i++) {
		if(string.length()- i >= pattern.length()) {
			int j = 0;
			for(; j < pattern.length(); j++) {
				if(string[i+j] != pattern[j]) {
					break;
				}
			}
			if(j == pattern.length()) {
				return i;
			}
		}else {
			break;
		}
	}
	return -1;
}
}