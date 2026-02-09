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
#include <iomanip>
#include <string>
#include <csignal>


Bureaucrat	createBureaucrat(void) {
	std::string	name;
	std::string	input;
	Bureaucrat	bureaucrat;
	long long	grade;

	name = getSafeInput("choose name for your Bureaucrat : ");
	bureaucrat = Bureaucrat(name, 150);

retryGettingGrade:
	try {
		input = getSafeInput("give your Bureaucrat a grade : ");
		std::stringstream	ss(input);
		ss >> grade;
		if (ss.fail() || !ss.eof())
			throw Bureaucrat::GradeException(COLOR_RED "[!] Bureaucrat grade must be a number between [1-150]" COLOR_RESET);
		bureaucrat.setGrade(grade);
	} catch (Bureaucrat::GradeException &e) {
		writeTextSlowly(e.what());
		std::cout << std::endl;
		goto retryGettingGrade;
	}
	writeTextSlowly(COLOR_BRIGHT_GREEN "[✓] Bureaucrat created successfully\n" COLOR_RESET);
	return bureaucrat;
}

Form	createForm(void) {
	std::stringstream	ss;
	std::string			name;
	std::string			input;
	long long			gradeToExec;
	long long			gradeToSign;
	Form				form;

	name = getSafeInput("choose name for your Form : ");
	form = Form(name, 150, 150);

retryGettingGradeToSign:
	try {
		input = getSafeInput("give your Form a grade to be signed : ");
		ss.clear();
		ss.str(input);
		ss >> gradeToSign;
		if (ss.fail() || !ss.eof())
			throw Form::GradeException(COLOR_RED "[!] Form grade to sign must be a number between [1-150]" COLOR_RESET);
		form = Form(name, gradeToSign, 150);
	} catch (Form::GradeException &e) {
		writeTextSlowly(e.what());
		std::cout << std::endl;
		goto retryGettingGradeToSign;
	}
retryGettingGradeToExec:
	try{
		input = getSafeInput("give your Form a grade to be executed : ");
		ss.clear();
		ss.str(input);
		ss >> gradeToExec;
		if (ss.fail() || !ss.eof())
			throw Form::GradeException(COLOR_RED "[!] Form grade to execute must be a number between [1-150]" COLOR_RESET);
		form = Form(name, gradeToSign, gradeToExec);
	} catch (Form::GradeException &e) {
		writeTextSlowly(e.what());
		std::cout << std::endl;
		goto retryGettingGradeToExec;
	}
	writeTextSlowly(COLOR_BRIGHT_GREEN "[✓] Form created successfully\n" COLOR_RESET);
	return form;
}


std::string	shrinkField(std::string field)
{
	if (field.size() <= 10)
		return field;
	field.resize(10);
	field.replace(9, 1, ".");
	return field;
}

void	showForms(const Form *Forms, const size_t count) {

	std::ostringstream oss;

	std::cout << COLOR_GREEN ;
	oss << "╭─────────────────────╮\n";
	oss << "│"
		<< std::right << std::setw(10) << "Index" << "|"
		<< std::right << std::setw(10) << "FormName"<< "│";
	oss << "\n├─────────────────────┤\n";
	for (size_t i = 0; i < 10; ++i)
	{
		oss << COLOR_GREEN "│" COLOR_RESET
			<< std::right << std::setw(10) << i << "|"
			<< std::right << std::setw(10) << shrinkField(shrinkField(Forms[i].getName()))
			<< COLOR_GREEN "│" COLOR_RESET "\n";
	}
	oss << COLOR_GREEN "╰─────────────────────╯" COLOR_RESET;
	
	printSlowLines(oss.str(), 50000);
	(void)count;
}

void	showBureaucrats(Bureaucrat *Bureaucrats, const size_t count) {
	std::ostringstream oss;

	std::cout << COLOR_GREEN ;
	(void)count;

	oss << "╭───────────────────────────────────────────────╮\n";
	oss << "│"
		<< std::right << std::setw(15) << "Index" << "|"
		<< std::right << std::setw(15) << "BureaucratName"<< "│"
		<< std::right << std::setw(15) << "BureaucratGrade"<< "│";
	oss << "\n├───────────────────────────────────────────────┤\n";
	for (size_t i = 0; i < 10; ++i)
	{
		oss << COLOR_GREEN "│" COLOR_RESET
			<< std::right << std::setw(15) << i
			<< COLOR_GREEN "│" COLOR_RESET
			<< std::right << std::setw(15) << shrinkField(shrinkField(Bureaucrats[i].getName()))
			<< COLOR_GREEN "│" COLOR_RESET
			<< std::right << std::setw(15) << Bureaucrats[i].getGrade()
			<< COLOR_GREEN "│" COLOR_RESET "\n";
	}
	oss << COLOR_GREEN "╰───────────────────────────────────────────────╯" COLOR_RESET;
	
	printSlowLines(oss.str(), 50000);

}

void	cli(void) {
	std::string	input;
	Bureaucrat	Bureaucrats[10];
	Form		Forms[10];
	size_t		idxB = 0;
	size_t		idxF = 0;

	enableAlternateScreen();
	clearScreen();
	while (true) {
		input = getSafeInput("❯ ");
		clearFromCursor();
		if (input == "create Bureaucrat") {
			Bureaucrats[idxB] = createBureaucrat();
			idxB = (idxB+1) % 10;
		}
		else if (input == "create Form") {
			Forms[idxF] = createForm();
			idxF = (idxF+1) % 10;
		}
		else if (input == "show Forms")
			showForms(Forms, idxF);
		else if (input == "show Bureaucrats")
			showBureaucrats(Bureaucrats, idxB);

	}
}

int main (int ac, char **av __attribute__((unused))) {
	if (ac != 1)
		return 0;
	signal(SIGWINCH, handle_resize);
	try {
			cli();
	} catch (std::exception &e) {
		std::cerr << "indefind error (" << e.what() << ")" << std::endl;
	}
	return 0;
}
