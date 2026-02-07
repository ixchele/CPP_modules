#pragma once
#include <ostream>
#include <stdexcept>
#include <string>

class Bureaucrat;

class Form {
private:
	const std::string	_name;
	bool				_isSigned;
	const long long		_gradeRequiredToSign;
	const long long		_gradeRequiredToExecute;
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
	Form(std::string name, long long gradeRequiredToSign, long long gradeRequiredToExecute);
	Form(const Form &other);
	~Form(void);

	Form	&operator=(const Form &other);

	std::string	getName(void) const;
	bool		isSigned(void) const;
	long long	gradeRequiredToSign(void) const;
	long long	gradeRequiredToExecute(void) const;
	void		beSigned(const Bureaucrat &bureaucrat);
};

std::ostream &operator<<(std::ostream &os, const Form &form);
