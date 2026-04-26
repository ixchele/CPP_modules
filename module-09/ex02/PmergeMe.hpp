#pragma once

#include <deque>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <limits>


template <typename Container>
void	fillContainer(Container &container, const std::string &input) {
	std::stringstream	ssInput(input);
	long				number = 0;	

	while (1) {
		ssInput >> number;

		if (ssInput.fail())
			break;

		if (number < 0 || number > std::numeric_limits<int>::max())
			throw std::runtime_error("Error");

		container.push_back(number);
	}

	if (!ssInput.eof())
		throw std::runtime_error("Error");
}
