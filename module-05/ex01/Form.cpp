#include "colors.h"
#include <Form.hpp>
#include <Bureaucrat.hpp>
#include <ios>
#include <iostream>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>

Form::GradeException::GradeException(const std::string &error)
	: std::runtime_error(error) {
	//pass
}

Form::GradeTooHighException::GradeTooHighException(const std::string &error)
	: GradeException(error) {
	//pass
}

Form::GradeTooLowException::GradeTooLowException(const std::string &error)
	: GradeException(error) {
	//pass
}

Form::SignGradeTooHighException::SignGradeTooHighException(const std::string &error)
	: GradeTooHighException(error) {
	//pass
}

Form::ExecGradeTooHighException::ExecGradeTooHighException(const std::string &error)
	: GradeTooHighException(error) {
	//pass
}

Form::SignGradeTooLowException::SignGradeTooLowException(const std::string &error)
	: GradeTooLowException(error) {
	//pass
}

Form::ExecGradeTooLowException::ExecGradeTooLowException(const std::string &error)
	: GradeTooLowException(error) {
	//pass
}

Form::Form(void) : _name("generic form"), _isSigned(false), _gradeRequiredToSign(150), _gradeRequiredToExecute(150) {
	//pass
}

Form::Form(std::string name, long long gradeRequiredToSign, long long gradeRequiredToExecute)
	: _name(name), _isSigned(false), _gradeRequiredToSign(gradeRequiredToSign), _gradeRequiredToExecute(gradeRequiredToExecute) {
	if (gradeRequiredToSign < 1)
		throw SignGradeTooHighException(COLOR_RED "[!] Form required grade to sign too high" COLOR_RESET);
	if (gradeRequiredToSign > 150)
		throw SignGradeTooLowException(COLOR_RED "[!] Form required grade to sign too low" COLOR_RESET);
	if (gradeRequiredToExecute < 1)
		throw ExecGradeTooHighException(COLOR_RED "[!] Form required grade to execute too high" COLOR_RESET);
	if (gradeRequiredToExecute > 150)
		throw ExecGradeTooLowException(COLOR_RED "[!] Form required grade to execute too low" COLOR_RESET);
}


Form::Form(const Form &other)
	: _name(other.getName()),
	  _isSigned(other.isSigned()),
	  _gradeRequiredToSign(other.gradeRequiredToSign()),
	  _gradeRequiredToExecute(other.gradeRequiredToExecute()) {
}

Form::~Form(void) {
	//pass
}

Form	&Form::operator=(const Form &other) {
	if (this == &other)
		return *this;
	this->~Form();
	new(this) Form(other);
	return *this;
}

std::string	Form::getName(void) const {
	return _name;
}

bool	Form::isSigned(void) const {
	return _isSigned;
}

long long	Form::gradeRequiredToSign(void) const {
	return _gradeRequiredToSign;
}

long long	Form::gradeRequiredToExecute(void) const {
	return _gradeRequiredToExecute;
}

void	Form::beSigned(const Bureaucrat &bureaucrat) {
	if (bureaucrat.getGrade() > gradeRequiredToSign()) {
		std::string error = bureaucrat.getName() + " couldn't sign " + getName() + "because his grade is too low";
		throw Form::GradeTooLowException(error);
	}
	if (isSigned() == false) {
		std::string error = bureaucrat.getName() + " couldn't sign " + getName() + "because " + getName() + " is already signed";
		throw std::runtime_error(error);
	}
	std::cout << bureaucrat.getName() + " signed " + getName() << std::endl; 
	_isSigned = true;
}

std::ostream &operator<<(std::ostream &os, const Form &other) {
	os << std::boolalpha;
	os << "form: " + other.getName() + "," + " is signed: " << other.isSigned(); 
	os << ", grade required to sign: " << other.gradeRequiredToSign();
	os << ", grade required to execute: " << other.gradeRequiredToExecute();
	return os;
}
