#include <iostream>
#include <stdio.h>
#include <vector>
#include "Vector.hpp"

int main() {
	std::vector<int> a(5, 5);
	std::vector<int> b(4, 4);
	
	vector<int> myVector(5, 5);

	for (vector<int>::iterator i = myVector.begin(); i != myVector.end(); i++) {
		std::cout << *i << std::endl;
	}
	std::cout << "size " << myVector.size() << std::endl;
	std::cout << "capacity " << myVector.capacity() << std::endl;
	std::cout << std::endl;

	// myVector.resize(8);
	// myVector.resize(12);
	myVector.assign(5, 2);
	myVector.reserve(6);
	myVector.insert(myVector.begin(), 3);
	// myVector.insert(myVector.begin(), 3, 0);

	for (vector<int>::iterator i = myVector.begin(); i != myVector.end(); i++) {
		std::cout << *i << std::endl;
	}
	std::cout << "size " << myVector.size() << std::endl;
	std::cout << "capacity " << myVector.capacity() << std::endl;
	std::cout << std::endl;

	// std::cout << "capacity " << a.capacity() << std::endl;
	// a.resize(8);
	// a.resize(12);
	a.assign(5, 2);
	a.reserve(6);
	a.insert(a.begin(), 3);
	// a.insert(a.begin(), 3, 0);
	for (std::vector<int>::iterator i = a.begin(); i != a.end(); i++) {
		std::cout << *i << std::endl;
	}

	std::cout << "size " << a.size() << std::endl;
	std::cout << "capacity " << a.capacity() << std::endl;
	// std::cout << "iter " << (a.rbegin() == (a.end() - 1)) << std::endl;
	std::cout << std::endl;

	return (0);
}
