#include "../ds/SuffixTree.h"

using namespace jumbuna;

int main() {
	SuffixTree tree("aabaacaadaabaaba");
	auto x = tree.subStringPositions("aa");
	for(int i = 0; i < x.size(); i++) {
		std::cout << x[i] << std::endl;
	}
}