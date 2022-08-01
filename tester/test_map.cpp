#include <iostream>
#include <map>
#include "../map.hpp"

template <typename stdIt, typename ftIt>
bool	array_diff(stdIt stdFirst, stdIt stdLast, ftIt ftFirst, ftIt ftLast) {
	for (; stdFirst != stdLast && ftFirst != ftLast; ++stdFirst, ++ftFirst) {
		if (stdFirst->first != ftFirst->first)
			return 1;
	}
	return 0;
}

void	fill_array(std::map<int, int> &stdMap, ft::map<int, int> &ftMap, size_t size) {
	ft::pair<int, int>	buf;
	for (size_t i = 0; i < size; ++i) {
		buf = ft::make_pair(std::rand(), std::rand());
		stdMap.insert(std::make_pair(buf.first, buf.second));
		ftMap.insert(buf);
	}
}

void	map_diff(const std::string test_name, const std::map<int, int> &stdMap, const ft::map<int, int> &ftMap) {
	std::cout << "--" << test_name << "--" << std::endl;
	std::cout << "size : " << ((stdMap.size() == ftMap.size()) ? "\033[32mok\033[m " : "\033[31mwrong\033[m") << std::endl;
	std::cout << "max_size : " << ((stdMap.max_size() == ftMap.max_size()) ? "\033[32mok\033[m " : "\033[31mwrong\033[m") << std::endl;
	std::cout << "array diff : " << (!array_diff(stdMap.begin(), stdMap.end(), ftMap.begin(), ftMap.end()) ? "\033[32mok\033[m " : "\033[31mwrong\033[m") << std::endl;
	std::cout << std::endl;
}

void	test_constructor(const std::map<int, int> &stdRefCont, const ft::map<int, int> &ftRefCont) {
	std::cout << "Map constructor testing" << std::endl;
	std::cout << std::endl;

	std::map<int, int>	stdMap1;
	ft::map<int, int>	ftMap1;
	map_diff("default constructor", stdMap1, ftMap1);

	std::map<int, int>	stdMap2(stdRefCont.begin(), stdRefCont.end());
	ft::map<int, int>	ftMap2(ftRefCont.begin(), ftRefCont.end());
	map_diff("constructor from iter", stdMap2, ftMap2);

	std::map<int, int>	stdMap3(stdMap2);
	ft::map<int, int>	ftMap3(ftMap2);
	map_diff("copy constructor", stdMap3, ftMap3);
	std::cout << "------------------------" << std::endl;
}

void	test_modifiers(const std::map<int, int> &stdRefCont, const ft::map<int, int> &ftRefCont) {
	std::cout << "Map modifiers testing" << std::endl;
	std::cout << std::endl;

	std::pair<int, int>		stdElem(std::rand(), std::rand());
	ft::pair<int, int>		ftElem(stdElem.first, stdElem.second);

	std::map<int, int>	stdMap1(stdRefCont.begin(), stdRefCont.end());
	ft::map<int, int>	ftMap1(ftRefCont.begin(), ftRefCont.end());

	stdMap1.insert(stdElem);
	ftMap1.insert(ftElem);
	map_diff("insert one element", stdMap1, ftMap1);

	stdMap1.erase(++(++(++(++stdMap1.begin()))), --(--(--(--(--stdMap1.end())))));
	ftMap1.erase(++(++(++(++ftMap1.begin()))), --(--(--(--(--ftMap1.end())))));
	map_diff("erase", stdMap1, ftMap1);

	stdMap1.clear();
	ftMap1.clear();
	map_diff("clear", stdMap1, ftMap1);
}

void	test_map() {
	std::cout << "===========MAP===========" << std::endl;
	size_t				size = 10000;
	ft::map<int, int>	ftMap;
	std::map<int, int>	stdMap;
	std::srand(342);
	fill_array(stdMap, ftMap, size);


	test_constructor(stdMap, ftMap);
	test_modifiers(stdMap, ftMap);
}