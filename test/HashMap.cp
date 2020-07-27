#include "../ds/HashMap.h"
#include <iostream>
#include <string>

using namespace jumbuna;

struct person {
	char gender = 'M';
	int age = 100;
};

int main() {
	Map<std::string, person> map{true};
	map["john"] = person{};
	map["jane"].age = 20;
	map.remove("jane");
	map["joyce"].age = 54;
	map["james"].age = 18;
	map["jim"].age = 6;
	map["joan"].age = 45;
	map["jill"].age = 90;
	map.insert("jill", map["jim"]);
	map.remove("jill");
	
//	auto f = map;
//	
	auto keys = map.keys();
//	
//	f["jill"].gender = 'F';
	
	for(int i = 0; i < keys.size(); i++) {
		std::cout << keys[i] << " -> " << map[keys[i]].age << std::endl;
	}
	
	std::cout << map.size();
}