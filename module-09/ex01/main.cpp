#include "RPN.hpp"
#include <exception>
#include <iostream>

int main (int ac, char *av[]) {
	if (ac != 2)
		return (std::cout << "Usage: ./RPN <expression>", -1);


	try {
		RPN	a(av[1]);
		std::cout << a.result() << std::endl;

	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}
