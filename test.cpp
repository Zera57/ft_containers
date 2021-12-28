#include <iostream>
#include <stdio.h>
#include <vector>
#include "Vector.hpp"

int main() {
	std::vector<int> a(0);
	std::vector<int> b(4, 4);
	
	vector<int> myVector(0);
	for (size_t i = 0; i < 5; i++)
	{
		a.push_back(i + 1);
		myVector.push_back(i + 1);
	}
	

	for (vector<int>::iterator i = myVector.begin(); i != myVector.end(); i++) {
		std::cout << *i << std::endl;
	}
	std::cout << "size " << myVector.size() << std::endl;
	std::cout << "capacity " << myVector.capacity() << std::endl;
	std::cout << std::endl;


	// myVector.resize(8);
	// myVector.resize(12);
	// myVector.assign(5, 2);
	// myVector.reserve(8);
	myVector.insert(myVector.begin(), 3, 0);
	std::cout << *myVector.erase(myVector.begin() + 1, myVector.begin() + 4) << std::endl;
	std::cout << *myVector.erase(myVector.begin() + 2) << std::endl;
	// myVector.insert(myVector.begin(), 3, 0);
	std::cout << "-------------" << std::endl;
	for (vector<int>::iterator i = myVector.begin(); i != myVector.end(); i++) {
		std::cout << *i << std::endl;
	}
	std::cout << "size " << myVector.size() << std::endl;
	std::cout << "capacity " << myVector.capacity() << std::endl;
	std::cout << "-------------" << std::endl;

	// a.resize(8);
	// a.resize(12);
	// a.assign(5, 2);
	// a.reserve(8);
	a.insert(a.begin(), 3, 0);
	std::cout << *a.erase(a.begin() + 1, a.begin() + 4) << std::endl;
	std::cout << *a.erase(a.begin() + 2) << std::endl;
	// a.insert(a.begin(), 3, 0);
	std::cout << "-------------" << std::endl;
	for (std::vector<int>::iterator i = a.begin(); i != a.end(); i++) {
		std::cout << *i << std::endl;
	}

	std::cout << "size " << a.size() << std::endl;
	std::cout << "capacity " << a.capacity() << std::endl;
	// std::cout << "iter " << (a.rbegin() == (a.end() - 1)) << std::endl;
	std::cout << "-------------" << std::endl;

	return (0);
}
