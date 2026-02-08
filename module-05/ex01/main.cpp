#include "Form.hpp"
#include "colors.h"
#include "tool_functions.hpp"
#include <Bureaucrat.hpp>
#include <cstddef>
#include <exception>
#include <iostream>
#include <cstdlib>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>


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
	Bureaucrat	*Bureaucrats[10];
	Form		*Forms[10];
	size_t		idx = 0;
	
	try {
		while (true) {
			safeGetLine(input);
			if (input == "create Bureaucrat")
			{
				std::stringstream ss;
				Bureaucrats[idx] = createBureaucrat();
				ss << *Bureaucrats[idx];
				writeTextSlowly(COLOR_BRIGHT_GREEN "[✓] Bureaucrat created successfully\n" COLOR_RESET);
				writeTextSlowly("your Bureaucrat infos ; ");
				writeTextSlowly(ss.str());
				std::cout << std::endl;
				idx = (idx+1) % 10;
			}
		}
	} catch (std::exception &e) {
		std::cerr << "indefind error (" << e.what() << ")" << std::endl;
	}
	return 0;
}
