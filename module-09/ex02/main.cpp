#include <cstddef>
#include <string>
#include <iostream>
#include <PmergeMe.hpp>

int main (int ac, char *av[]) {
	for (std::size_t i = 0; i < 16; ++i)
		std::cout << JacobsthalSeq(i) << std::endl;
	return 0;
}
