#pragma once
#include <Bureaucrat.hpp>
#include <stdexcept>
#include <string>

class Form {
private:
	const std::string	_name;
	bool				_isSigned;
	const short			_gradeRequiredToSign;
	const short			_gradeRequiredToExecute;
public:
	struct GradeException : public std::runtime_error {
		GradeException(const std::string &error);
	};
	struct GradeTooHighException : public GradeException {
		GradeTooHighException(const std::string &error);
	};
	struct GradeTooLowException : public GradeException {
		GradeTooLowException(const std::string &error);
	};

	Form(void);
	Form(std::string name, short gradeRequiredToSign, short gradeRequiredToExecute);
	Form(const Form &other);
	~Form(void);

	std::string	getName(void) const;
	bool		isSigned(void) const;
	short		gradeRequiredToSign(void) const;
	short		gradeRequiredToExecute(void) const;
	void		beSigned(Bureaucrat bureaucrat);
};
