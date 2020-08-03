#pragma once

#include <string>
#include "../../ds/HashMap.h"

using BadTable = jumbuna::Map<char, int>;

namespace jumbuna {
	//bad table construction
void badTableConstruction(std::string &pattern, BadTable &table) {
	int patternLength = pattern.length();
	for(int i = 0; i < pattern.size(); i++) {
		int shift = patternLength - i - 1;
		table[pattern[i]] = shift <= 0 ? 1 : shift;
	}
}

int bayerMooreSearch(std::string &string, std::string &pattern, BadTable &table) {
	int patternLength = pattern.length();
	char currentChar;
	for(int i = patternLength-1; i < string.length(); i++) {
		currentChar = string[i];
		int j = 0;
		if(currentChar == pattern[patternLength-1]) {
			j = 1;
			--i;
			while(j < patternLength) {
				if(pattern[patternLength-1-j] != string[i]) {
					break;
				}
				++j;
				--i;
			}
		}
		if(j == patternLength) {
			return i+1;
		}
		currentChar = string[i];
		i += table.contains(currentChar) ? table[currentChar]+j-1 : patternLength+j-1; 
	}
	return -1;

}

int bayerMooreSearch(std::string &string, std::string &pattern) {
	BadTable table;
	badTableConstruction(pattern, table);
	return bayerMooreSearch(string, pattern, table);
}

int bayerMooreSearch(std::string &&string, std::string &&pattern) {
	return bayerMooreSearch(string, pattern);
}

}