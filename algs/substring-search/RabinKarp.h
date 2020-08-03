#pragma once

#include <string>
#include <cmath>

#define prime 3

namespace jumbuna {
long subStringHash(std::string &string, int i, int m) {
	long hash = 0;
	for(int j = 0; j < m; j++) {
		hash += string[i+j] * pow(prime, j);
	}
	return hash;
}
void runningHash(long &previousHash, int m, char &old, char &nw) {
	previousHash -= old;
	previousHash /= prime;
	previousHash += (nw * pow(prime, m-1));
}

int rabinKarp(std::string string, std::string pattern) {
	int patternLength = pattern.length();
	long patternHash = subStringHash(pattern, 0, patternLength);
	long hash = 0;
	for(int i = 0; i <= string.length()-pattern.length(); i++) {
		if(i == 0) {
			hash = subStringHash(string, 0, patternLength);
		}else {
			runningHash(hash, patternLength, string[i-1], string[i+patternLength-1]);
		}
		if(hash == patternHash) {
			int j = 0;
			for(; j < patternLength; j++) {
				if(pattern[j] != string[i+j]) {
					break;
				}
			}
			//match found
			if(j == patternLength) {
				return i;
			}
		}
	}
	return -1;
}
}