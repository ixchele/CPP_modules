#pragma once
#include <AForm.hpp>

struct RobotomyRequestForm : public AForm {
	RobotomyRequestForm(void);
	RobotomyRequestForm(const std::string &name);
	RobotomyRequestForm(const RobotomyRequestForm &other);
	~RobotomyRequestForm(void);

	RobotomyRequestForm	&operator=(const RobotomyRequestForm &other);

	void	FormAction(void) const;

};

