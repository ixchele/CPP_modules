#pragma once
#include <ostream>
#include <stdexcept>
#include <string>
#include <Form.hpp>


class Bureaucrat {
private:
	const std::string	_name;
	int					_grade;

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
	Bureaucrat(void);
	Bureaucrat(const std::string name, long long grade);
	Bureaucrat(const Bureaucrat &other);
	~Bureaucrat(void);

	Bureaucrat	&operator=(const Bureaucrat &other);

	int			getGrade(void) const;
	std::string	getName(void) const;
	void		setGrade(long long grade);
	void		setName(std::string name);

	void		incrementGrade(void);
	void		decrementGrade(void);
	void		signForm(Form &form);
};

std::ostream	&operator<<(std::ostream &os, const Bureaucrat &bureaucrat);
