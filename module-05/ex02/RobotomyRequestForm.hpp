#pragma once
#include <AForm.hpp>

class RobotomyRequestForm : public AForm {
private:
	static std::string	_shrubbery;
public:
	RobotomyRequestForm(void);
	RobotomyRequestForm(const std::string &name);
	RobotomyRequestForm(const RobotomyRequestForm &other);
	~RobotomyRequestForm(void);

	RobotomyRequestForm	&operator=(const RobotomyRequestForm &other);

	void	FormAction(void);

};
