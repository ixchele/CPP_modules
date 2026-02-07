#include "colors.h"
#include <Bureaucrat.hpp>
#include <iostream>
#include <ostream>

Bureaucrat::GradeException::GradeException(const std::string &error)
	: std::runtime_error(error) {
	//pass
}

Bureaucrat::GradeTooHighException::GradeTooHighException(const std::string &error)
	: GradeException(error) {
	//pass
}

Bureaucrat::GradeTooLowException::GradeTooLowException(const std::string &error)
	: GradeException(error) {
	//pass
}

Bureaucrat::Bureaucrat(void) : _name("Steve"), _grade(150) {
	//pass
}

Bureaucrat::Bureaucrat(std::string name, long long grade) : _name(name) {
	setGrade(grade);
}

Bureaucrat::Bureaucrat(const Bureaucrat &other) : _name(other.getName()), _grade(other.getGrade()) {
	*this = other;
}

Bureaucrat::~Bureaucrat(void) {
	//pass
}

Bureaucrat	&Bureaucrat::operator=(const Bureaucrat &other) {
	if (this == &other)
		return *this;
	this->~Bureaucrat();
	new(this) Bureaucrat(other);
	return *this;
}

int	Bureaucrat::getGrade(void) const {
	return _grade;
}

std::string	Bureaucrat::getName(void) const {
	return _name;
}

void	Bureaucrat::setGrade(long long grade) {
	if (grade < 1)
		throw Bureaucrat::GradeTooHighException(COLOR_RED "[!] Bureaucrat grade is too high" COLOR_RESET);
	else
		if (grade > 150)
			throw Bureaucrat::GradeTooLowException(COLOR_RED "[!] Bureaucrat grade is too low" COLOR_RESET);
	_grade = grade;
}

void	Bureaucrat::incrementGrade(void) {
	setGrade(_grade - 1);
}

void	Bureaucrat::decrementGrade(void) {
	setGrade(_grade + 1);
}

std::ostream	&operator<<(std::ostream &os, const Bureaucrat &other) {
	os << other.getName() << ", bureaucrat grade " << other.getGrade() << ".";
	return os;
}
