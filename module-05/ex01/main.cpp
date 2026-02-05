#include "colors.h"
#include "tool_functions.hpp"
#include <Bureaucrat.hpp>
#include <exception>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>


void	safeGetLine(std::string &input) {
	if (!std::getline(std::cin, input))
		std::exit(1);
}

Bureaucrat	*createBureaucrat(void) {
	std::string	name;
	short		grade;
	std::string	input;

	writeTextSlowly("choose name for your Bureaucrat : ");
	safeGetLine(name);
	Bureaucrat	*bureaucrat = new Bureaucrat(name, 150);
retryGettingGrade:
	try {
		writeTextSlowly("give your Bureaucrat a grade : ");
		safeGetLine(input);
		std::stringstream	ss(input);
		ss >> grade;
		if (ss.fail() || !ss.eof())
			throw Bureaucrat::GradeException(COLOR_RED "[!] Bureaucrat grade must be a number between [1-150]" COLOR_RESET);
		bureaucrat->setGrade(grade);
	} catch (Bureaucrat::GradeException &e) {
		writeTextSlowly(e.what());
		std::cout << std::endl;
		goto retryGettingGrade;
	}
	return bureaucrat;
}

int main (int ac, char **av __attribute__((unused))) {
	if (ac != 1)
		return 0;

	std::string	input;

	try {
		while (true) {
			std::stringstream ss;
			Bureaucrat	*bureaucrat = createBureaucrat();
			ss << *bureaucrat;
			writeTextSlowly(COLOR_BRIGHT_GREEN "[✓] Bureaucrat created successfully\n" COLOR_RESET);
			writeTextSlowly("your Bureaucrat infos ; ");
			writeTextSlowly(ss.str());
			std::cout << std::endl;
			delete bureaucrat;
		}
	} catch (std::exception &e) {
		std::cerr << "indefind error (" << e.what() << ")" << std::endl;
	}
	return 0;
}
