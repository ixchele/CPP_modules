#pragma once
#include <ostream>
#include <stdexcept>
#include <string>

class Bureaucrat {
private:
	const std::string	_name;
	int					_grade;

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
public:
	Bureaucrat(void);
	Bureaucrat(const std::string name, int grade);
	Bureaucrat(Bureaucrat &other);
	~Bureaucrat(void);


	int			getGrade(void) const;
	std::string	getName(void) const;
	void		setGrade(int grade);

	void		incrementGrade(void);
	void		decrementGrade(void);

};

std::ostream	&operator<<(std::ostream &os, const Bureaucrat &other);
