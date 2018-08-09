#pragma once
#include <iostream>
#include <sstream>
#include <iomanip>

template <class Container>
void mySplit(const std::string& str, Container& cont, char delim = ' ')
{
	std::stringstream ss(str);
	std::string token;
	while (std::getline(ss, token, delim)) {
		cont.push_back(token);
	}
}