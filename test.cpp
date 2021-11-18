#include <iostream>
#include <vector>
#include "Vector.hpp"
#include <bits/stdc++.h>

int main() {
	std::vector<int> a;
	vector<int> myVector(5, 5);
	
	for (vector<int>::iterator i = myVector.begin(); i != myVector.end(); i++) {
		std::cout << *i << std::endl;
	}


	return (0);
}