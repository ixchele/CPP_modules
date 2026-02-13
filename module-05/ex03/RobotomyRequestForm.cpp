#include "AForm.hpp"
#include <RobotomyRequestForm.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <colors.h>
#define SIGN_GRADE 72
#define EXEC_GRADE 45

static bool	_randomInit(void) {
	std::srand(std::time(NULL));
	return true;
}

static bool	_RandomInit = _randomInit();

RobotomyRequestForm::RobotomyRequestForm(void)
	: AForm("RobotomyRequestForm", "Missi", SIGN_GRADE, EXEC_GRADE) {
	std::srand(std::time(0));
}

RobotomyRequestForm::RobotomyRequestForm(const std::string &target)
	: AForm("RobotomyRequestForm", target, SIGN_GRADE, EXEC_GRADE) {
	std::srand(std::time(0));
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &other)
	: AForm(other.getName(), other.getTarget(), SIGN_GRADE, EXEC_GRADE) {
	//pass;
}

RobotomyRequestForm::~RobotomyRequestForm(void) {
	//pass;
}

RobotomyRequestForm	&RobotomyRequestForm::operator=(const RobotomyRequestForm &other) {
	if (this == &other)
		return *this;
	AForm::operator=(other);
	return *this;
}

void	RobotomyRequestForm::FormAction(void) const {
	if (!(std::rand() % 2)) {
		std::cout << "Robotomy " + getTarget() + " failed." << std::endl;
		return;
	}
	std::cout << COLOR_YELLOW "* VRRRRRRRRRRRRRRRR *" COLOR_RESET << std::endl;
	std::cout << COLOR_GREEN + getTarget() + " was successfully robotized" COLOR_RESET << std::endl;
}
