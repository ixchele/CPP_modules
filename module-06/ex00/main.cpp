#include <ScalarConverter.hpp>
#include <cmath>
#include <iostream>

int main (int ac, char **av) {
	if (ac != 2) {
		std::cout << "[!] usage: ./conver" << std::endl;
		return -1;
	}
	ScalarConverter::convert(av[1]);
	return 0;
}
