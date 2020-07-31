#include <iostream>
#include "../algs/substring-search/Kmp.h"

using namespace std;
int main(int argc, char *argv[]) {
	std::cout << kmpSubStringSearch("abcxabcdabxabcdabcdabcy", "abcdabcy") <<std::endl;
	//reuseable table
	KmpTable table;
	constructKmpTable("abcdabcy", table);
	std::cout << kmpSubStringSearch("abcxabcdabxabcdabcdabcy", "abcdabcy", table);
}