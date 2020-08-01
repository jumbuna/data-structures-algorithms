#include <iostream>
#include "../algs/substring-search/Kmp.h"
#include "../algs/substring-search/Brute.h"
#include "../algs/substring-search/RabinKarp.h"

using namespace std;
int main(int argc, char *argv[]) {
	std::cout << kmpSubStringSearch("abcxabcdabxabcdabcdabcy", "abcdabcy") << std::endl;
	//reuseable table
	KmpTable table;
	constructKmpTable("acacabacacabacacac", table);
	std::cout << kmpSubStringSearch("abcxabcdabxabcdabcdabcy", "abcdabcy", table) << std::endl;
	std::cout << bruteSearch("abcxabcdabxabcdabcdabcy", "abcdabcy") << std::endl;
	std::cout << rabinKarp("abcxabcdabxabcdabcdabcy", "abcdabcy") << std::endl;
}