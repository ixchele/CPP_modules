#include "AForm.hpp"
#include <PresidentialPardonForm.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <colors.h>
#define SIGN_GRADE 25
#define EXEC_GRADE 5
#define PARDON_MSG COLOR_GREEN + getTarget() + " has been pardoned by Zaphod Beeblebrox." COLOR_RESET

PresidentialPardonForm::PresidentialPardonForm(void)
	: AForm("PresidentialPardonForm", "Missi", SIGN_GRADE, EXEC_GRADE) {
	std::srand(std::time(0));
}

PresidentialPardonForm::PresidentialPardonForm(const std::string &target)
	: AForm("PresidentialPardonForm", target, SIGN_GRADE, EXEC_GRADE) {
	std::srand(std::time(0));
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &other)
	: AForm(other.getName(), other.getTarget(), SIGN_GRADE, EXEC_GRADE) {
	//pass;
}

PresidentialPardonForm::~PresidentialPardonForm(void) {
	//pass;
}

PresidentialPardonForm	&PresidentialPardonForm::operator=(const PresidentialPardonForm &other) {
	if (this == &other)
		return *this;
	AForm::operator=(other);
	return *this;
}

void	PresidentialPardonForm::FormAction(void) const {
	std::cout << PARDON_MSG << std::endl;
}
