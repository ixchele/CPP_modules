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
#include <stdexcept>
#include <string>
#include <csignal>
#include <sstream>
#include <tool_functions.hpp>

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

	if (count == 0)
		throw std::runtime_error(COLOR_RED "[!] there is no Forms to show!" COLOR_RESET);

	std::cout << COLOR_GREEN ;
	oss << "╭─────────────────────╮\n";
	oss << "│"
		<< std::right << std::setw(10) << "Index" << "|"
		<< std::right << std::setw(10) << "FormName"<< "│";
	oss << "\n├─────────────────────┤\n";
	for (size_t i = 0; i < count; ++i)
	{
		oss << COLOR_GREEN "│" COLOR_RESET
			<< std::right << std::setw(10) << i << "|"
			<< std::right << std::setw(10) << shrinkField(shrinkField(Forms[i].getName()))
			<< COLOR_GREEN "│" COLOR_RESET "\n";
	}
	oss << COLOR_GREEN "╰─────────────────────╯" COLOR_RESET;

	printSlowLines(oss.str(), 50000);
}

void	BureaucratActions(Bureaucrat *Bureaucrats, size_t Bcount, Form *Forms, size_t Fcount) {
	std::ostringstream	bureaucratInfos;
	std::string			action;
	size_t				idB;
	size_t				idF;

retryGetId:
	std::istringstream	inputId (getSafeInput("choose a Bureaucrat : "));
	if (!(inputId >> idB) || !inputId.eof() || idB < 0 || idB > Bcount - 1) {
		writeTextSlowly(COLOR_RED "[!] invalid id!\n" COLOR_RESET);
		goto retryGetId;
	}
	bureaucratInfos << Bureaucrats[idB];
retryGetAction:
	try {
		std::string inputAction = getSafeInput("choose an Action (increment/decrement grade or sign Form) : ");
		if (inputAction == "show infos")
			writeTextSlowly(COLOR_BLUE + bureaucratInfos.str() + COLOR_RESET + "\n");
		else if (inputAction == "increment grade") {
			Bureaucrats[idB].incrementGrade();
			writeTextSlowly(COLOR_GREEN "[✓] grade incremented successfully\n" COLOR_RESET);
		}
		else if (inputAction == "decrement grade") {
			Bureaucrats[idB].decrementGrade();
			writeTextSlowly(COLOR_GREEN "[✓] grade decremented successfully\n" COLOR_RESET);
		}
		else if (inputAction == "sign Form") {
			showForms(Forms, Fcount);
		retryGetIdForm:
			std::istringstream formId (getSafeInput("choose a Form to sign : "));
			if (!(formId >> idF) || !formId.eof() || idF < 0 || idF > Fcount - 1) {
				writeTextSlowly(COLOR_RED "[!] invalid id!\n" COLOR_RESET);
				goto retryGetIdForm;
			}
			Bureaucrats[idB].signForm(Forms[idF]);
			writeTextSlowly(COLOR_GREEN "[✓] Form signed successfully\n" COLOR_RESET);
		}
		else {
			writeTextSlowly(COLOR_RED "[!] invalid choice!\n" COLOR_RESET);
			goto retryGetAction;
		}
	} catch (Form::GradeException &e) {
		writeTextSlowly(e.what() ); std::cout << std::endl;
		goto retryGetAction;
	} catch (Bureaucrat::GradeException &e) {
		writeTextSlowly(e.what() ); std::cout << std::endl;
		goto retryGetAction;
	}
}

void	showBureaucrats(Bureaucrat *Bureaucrats, size_t Bcount, Form *Forms, size_t Fcount) {
	std::ostringstream oss;

	if (Bcount == 0)
		throw std::runtime_error(COLOR_RED "[!] there is no Bureaucrats to show!" COLOR_RESET);

	std::cout << COLOR_GREEN ;

	oss << "╭───────────────────────────────────────────────╮\n";
	oss << "│"
		<< std::right << std::setw(15) << "Index" << "|"
		<< std::right << std::setw(15) << "BureaucratName"<< "│"
		<< std::right << std::setw(15) << "BureaucratGrade"<< "│";
	oss << "\n├───────────────────────────────────────────────┤\n";
	for (size_t i = 0; i < Bcount; ++i)
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
	BureaucratActions(Bureaucrats, Bcount, Forms, Fcount);
	// std::string input = getSafeInput("choose a Bureaucrat : ");
}

void	cli(void) {
	std::string	input;
	Bureaucrat	Bureaucrats[10];
	Form		Forms[10];
	size_t		idxB = 0;
	size_t		Bcount = 0;
	size_t		Fcount = 0;
	size_t		idxF = 0;

	enableAlternateScreen();
	clearScreen();
	while (true) {
		try {
			input = getSafeInput("❯ ");
			clearFromCursor();
			if (input == "create Bureaucrat") {
				Bureaucrats[idxB] = createBureaucrat();
				idxB = (idxB+1) % 10;
				if (Bcount < 10) Bcount++;
			}
			else if (input == "create Form") {
				Forms[idxF] = createForm();
				idxF = (idxF+1) % 10;
				if (Fcount < 10) Fcount++;
			}
			else if (input == "show Forms")
				showForms(Forms, Fcount);
			else if (input == "show Bureaucrats")
				showBureaucrats(Bureaucrats, Bcount, Forms, Fcount);
		} catch (std::exception &e) {
			writeTextSlowly(e.what()); std::cout << std::endl;
		}
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
