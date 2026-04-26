#include <deque>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <vector>


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

template <typename Container>
void printContainer(const Container &container) {
    typename Container::const_iterator it;
    for (it = container.begin(); it != container.end(); ++it) {
        std::cout << *it << (it + 1 != container.end() ? " " : "");
    }
    std::cout << std::endl;
}


int main (int argc, char *argv[]) {

	std::vector<int>	a;
	std::deque<int>		b;
	fillContainer(a, std::string(argv[1]));
	fillContainer(b, std::string(argv[1]));
	printContainer(a);
	printContainer(b);
}
