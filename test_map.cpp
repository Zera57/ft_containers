// #include <map>
#include "map.hpp"
#include <iostream>
#include <string>
#include <stdlib.h>

void printMap(ft::map<int, int> &map_int) {
	std::cout << "Start iterator" << std::endl;
	auto it = map_int.begin();
	while ( it != map_int.end()) {
        std::cout << it->first << " | " << it->second << std::endl;
		++it;
	}
	std::cout << "End iterator" << std::endl;
	std::cout << "Start reverse_iterator" << std::endl;
	ft::map<int, int>::reverse_iterator itr = map_int.rbegin();
	// std::cout << "--itr " << itr.base()->parent << " | " << itr.base()->parent->value->first << " | " << itr.base()->parent->value->second << std::endl;
	// std::cout << "--itr " << (--map_int.rbegin()).base() << " | " << (--map_int.rbegin()).base()->value->first << " | " << (--map_int.rbegin()).base()->value->second << std::endl;
	while ( itr != map_int.rend()) {
        std::cout << itr->first << " | " << itr->second << std::endl;
		++itr;
	}
	std::cout << "End reverse_iterator" << std::endl;
	std::cout << "----------------------------------" << std::endl;
}


int main() {
	ft::map<int, int> map_int;
	std::cout << "Start insert" << std::endl;
	map_int.insert(ft::make_pair(9, 1));
	std::cout << "1" << std::endl;
	map_int.insert(ft::make_pair(8, 2));
	std::cout << "2" << std::endl;
	// map_int.insert(ft::make_pair(1, 3));
	// std::cout << "3" << std::endl;
	// map_int.insert(ft::make_pair(2, 4));
	// std::cout << "4" << std::endl;
	// map_int.insert(ft::make_pair(6, 5));
	// std::cout << "5" << std::endl;
	// map_int.insert(ft::make_pair(7, 6));
	// std::cout << "6" << std::endl;
	// map_int.insert(ft::make_pair(5, 7));
	// std::cout << "7" << std::endl;
	// map_int.insert(ft::make_pair(4, 8));
	// std::cout << "8" << std::endl;
	// map_int.insert(ft::make_pair(3, 9));
	// std::cout << "9" << std::endl;
	map_int.insert(ft::make_pair(11, 10));
	std::cout << "10" << std::endl;
	map_int.insert(ft::make_pair(10, 10));
	std::cout << "10" << std::endl;
	map_int.insert(ft::make_pair(12, 10));
	std::cout << "10" << std::endl;
	std::cout << "End insert" << std::endl;
	std::cout << "----------------------------------" << std::endl;

	printMap(map_int);

	// map_int.erase(map_int.begin());
	// auto it = map_int.begin();
    // std::cout << it->first << " | " << it->second << std::endl;
	map_int.erase(map_int.begin());
	

	printMap(map_int);

	ft::pair<ft::map<int, int>::const_iterator, ft::map<int, int>::const_iterator> a = map_int.equal_range(5);
	
	// it++;
	// it++;
	// it++;
	// it++;
	// it++;
	// it++;
	// it++;
    // std::cout << it->first << " | " << it->second.num << std::endl;
    // std::cout << map_int.end()->first << " | " << it->second.num << std::endl;
    return 0;
}