#include "colors.h"
#include <AForm.hpp>
#include <Bureaucrat.hpp>
#include <ios>
#include <iostream>
#include <ostream>
#include <string>

AForm::GradeException::GradeException(const std::string &error)
	: std::runtime_error(error) {
	//pass
}

AForm::GradeTooHighException::GradeTooHighException(const std::string &error)
	: GradeException(error) {
	//pass
}

AForm::GradeTooLowException::GradeTooLowException(const std::string &error)
	: GradeException(error) {
	//pass
}

AForm::SignGradeTooHighException::SignGradeTooHighException(const std::string &error)
	: GradeTooHighException(error) {
	//pass
}

AForm::ExecGradeTooHighException::ExecGradeTooHighException(const std::string &error)
	: GradeTooHighException(error) {
	//pass
}

AForm::SignGradeTooLowException::SignGradeTooLowException(const std::string &error)
	: GradeTooLowException(error) {
	//pass
}

AForm::ExecGradeTooLowException::ExecGradeTooLowException(const std::string &error)
	: GradeTooLowException(error) {
	//pass
}

AForm::AForm(void) : _name("generic form"), _isSigned(false), _gradeRequiredToSign(150), _gradeRequiredToExecute(150) {
	//pass
}

AForm::AForm(std::string name, std::string target, long long gradeRequiredToSign, long long gradeRequiredToExecute)
	: _target(target), _name(name), _isSigned(false), _gradeRequiredToSign(gradeRequiredToSign), _gradeRequiredToExecute(gradeRequiredToExecute) {
	if (gradeRequiredToSign < 1)
		throw SignGradeTooHighException(COLOR_RED "[!] AForm required grade to sign too high" COLOR_RESET);
	if (gradeRequiredToSign > 150)
		throw SignGradeTooLowException(COLOR_RED "[!] AForm required grade to sign too low" COLOR_RESET);
	if (gradeRequiredToExecute < 1)
		throw ExecGradeTooHighException(COLOR_RED "[!] AForm required grade to execute too high" COLOR_RESET);
	if (gradeRequiredToExecute > 150)
		throw ExecGradeTooLowException(COLOR_RED "[!] AForm required grade to execute too low" COLOR_RESET);
}


AForm::AForm(const AForm &other)
	: _name(other.getName()),
	  _isSigned(other.isSigned()),
	  _gradeRequiredToSign(other.gradeRequiredToSign()),
	  _gradeRequiredToExecute(other.gradeRequiredToExecute()) {
}

AForm::~AForm(void) {
	//pass
}

AForm	&AForm::operator=(const AForm &other) {
	if (this == &other)
		return *this;
	setTarget(other.getTarget());
	return *this;;
}

void	AForm::setTarget(const std::string &target) {
	_target = target;
}

std::string	AForm::getTarget(void) const {
	return _target;
}

std::string	AForm::getName(void) const {
	return _name;
}

bool	AForm::isSigned(void) const {
	return _isSigned;
}

long long	AForm::gradeRequiredToSign(void) const {
	return _gradeRequiredToSign;
}

long long	AForm::gradeRequiredToExecute(void) const {
	return _gradeRequiredToExecute;
}

void	AForm::beSigned(const Bureaucrat &bureaucrat) {
	if (bureaucrat.getGrade() > gradeRequiredToSign()) {
		std::string error = bureaucrat.getName() + " couldn't sign " + getName() + "because his grade is too low";
		throw AForm::GradeTooLowException(error);
	}
	if (isSigned() == true) {
		std::string error = bureaucrat.getName() + " couldn't sign " + getName() + "because " + getName() + " is already signed";
		throw std::runtime_error(error);
	}
	std::cout << bureaucrat.getName() + " signed " + getName() << std::endl; 
	_isSigned = true;
}

void	AForm::execute(const Bureaucrat &bureaucrat) const {
	if (bureaucrat.getGrade() > gradeRequiredToExecute()) {
		std::string error = bureaucrat.getName() + " couldn't execute " + getName() + "because his grade is too low";
		throw AForm::ExecGradeTooLowException(error);
	}
	if (isSigned() == false) {
		std::string error = bureaucrat.getName() + " couldn't execute " + getName() + "because " + getName() + " is not signed";
		throw std::runtime_error(error);
	}
	FormAction();
	std::cout << COLOR_GREEN + bureaucrat.getName() + " executed " + getName() + COLOR_RESET << std::endl;
}

std::ostream &operator<<(std::ostream &os, const AForm &other) {
	os << std::boolalpha;
	os << "form: " + other.getName() + "," + " is signed: " << other.isSigned(); 
	os << ", grade required to sign: " << other.gradeRequiredToSign();
	os << ", grade required to execute: " << other.gradeRequiredToExecute();
	return os;
}
