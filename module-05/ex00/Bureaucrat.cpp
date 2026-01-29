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

Bureaucrat::Bureaucrat(std::string name, int grade) : _name(name) {
	setGrade(grade);
}

Bureaucrat::Bureaucrat(Bureaucrat &other) : _name(other.getName()), _grade(other.getGrade()) {
	//pass
}

Bureaucrat::~Bureaucrat(void) {
	//pass
}

int	Bureaucrat::getGrade(void) const {
	return _grade;
}

std::string	Bureaucrat::getName(void) const {
	return _name;
}

void	Bureaucrat::setGrade(int grade) {
	if (grade < 1)
		throw Bureaucrat::GradeTooHighException("Bureaucrat grade is too high");
	else
		if (grade > 150)
			throw Bureaucrat::GradeTooLowException("Bureaucrat grade is too low");
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
