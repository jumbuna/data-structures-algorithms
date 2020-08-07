#include <iostream>
#include "../algs/substring-search/Kmp.h"
#include "../algs/substring-search/Brute.h"
#include "../algs/substring-search/RabinKarp.h"
#include "../algs/substring-search/ZArray.h"
#include "../algs/substring-search/BayerMoore.h"

using namespace std;
int main(int argc, char *argv[]) {
	//internal table construction
	std::cout << jumbuna::kmpSubStringSearch("abcxabcdabxabcdabcdabcy", "abcdabcy") << std::endl;
	//reuseable table
	//KmpTable table;
	//jumbuna::constructKmpTable("acacabacacabacacac", table);
	//std::cout << jumbuna::kmpSubStringSearch("abcxabcdabxabcdabcdabcy", "abcdabcy", table) << std::endl;
	std::cout << jumbuna::bruteSearch("abcxabcdabxabcdabcdabcy", "abcdabcy") << std::endl;
	std::cout << jumbuna::rabinKarp("abcxabcdabxabcdabcdabcy", "abcdabcy") << std::endl;
	std::cout << jumbuna::bayerMooreSearch("abcxabcdabxabcdabcdabcy", "abcdabcy") << std::endl;
	auto vec = jumbuna::zAlgorithmSearch("abcxabcdabxabcdabcdabcy", "abcdabcy");
	for(int i = 0; i < vec.size(); i++) {
		std::cout << vec[i] << std::endl;
	}
}