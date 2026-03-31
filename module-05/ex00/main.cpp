#include "Bureaucrat.hpp"
#include <iostream>

int main() {
	try {
		Bureaucrat hermes("Hermes Conrad", 2);
		std::cout << hermes << std::endl;
		hermes.incrementGrade();
		std::cout << hermes << std::endl;
		hermes.incrementGrade();
	} catch (std::exception &e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	try {
		Bureaucrat trainee("Trainee", 151);
	} catch (std::exception &e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
