#pragma once
#include <ostream>
#include <stdexcept>
#include <string>

class Bureaucrat {
private:
	const std::string	_name;
	int					_grade;

public:
	class GradeException : public std::runtime_error {
	public:
		GradeException(const std::string &error);
	};
	class GradeTooHighException : public GradeException {
	public:
		GradeTooHighException(const std::string &error);
	};
	class GradeTooLowException : public GradeException {
	public:
		GradeTooLowException(const std::string &error);
	};
	Bureaucrat(void);
	Bureaucrat(const std::string name, short grade);
	Bureaucrat(Bureaucrat &other);
	~Bureaucrat(void);


	int			getGrade(void) const;
	std::string	getName(void) const;
	void		setGrade(short grade);
	void		setName(std::string name);

	void		incrementGrade(void);
	void		decrementGrade(void);

};

std::ostream	&operator<<(std::ostream &os, const Bureaucrat &other);
