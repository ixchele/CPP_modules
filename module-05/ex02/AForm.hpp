#pragma once
#include <ostream>
#include <stdexcept>
#include <string>

class Bureaucrat;

class AForm {
protected:
	std::string			_target;
	const std::string	_name;
	bool				_isSigned;
	const long long		_gradeRequiredToSign;
	const long long		_gradeRequiredToExecute;

	long long	checkGrade(long long grade);
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
	struct SignGradeTooLowException : public GradeTooLowException {
		SignGradeTooLowException(const std::string &erroe);
	};
	struct ExecGradeTooLowException : public GradeTooLowException {
		ExecGradeTooLowException(const std::string &erroe);
	};
	struct SignGradeTooHighException : public GradeTooHighException {
		SignGradeTooHighException(const std::string &erroe);
	};
	struct ExecGradeTooHighException : public GradeTooHighException {
		ExecGradeTooHighException(const std::string &erroe);
	};

	AForm(void);
	AForm(std::string name, long long gradeRequiredToSign, long long gradeRequiredToExecute);
	AForm(const AForm &other);
	virtual ~AForm(void);

	virtual AForm	&operator=(const AForm &other);

	std::string		getName(void) const;
	bool			isSigned(void) const;
	long long		gradeRequiredToSign(void) const;
	long long		gradeRequiredToExecute(void) const;

	std::string		getTarget(void) const;
	void			setTarget(const std::string &target);

	void			beSigned(const Bureaucrat &bureaucrat);
	virtual	void	FormAction(void) const = 0 ;
	virtual void	execute(Bureaucrat const &executor) const;
};

std::ostream &operator<<(std::ostream &os, const AForm &form);
