#include "AForm.hpp"
#include <ShrubberyCreationForm.hpp>
#include <fstream>

#define SIGN_GRADE 145 
#define EXEC_GRADE 137 

ShrubberyCreationForm::ShrubberyCreationForm(void)
	: AForm("ShrubberyCreationForm", "default", SIGN_GRADE, EXEC_GRADE) {
	//pass;
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target)
	: AForm("ShrubberyCreationForm", target, SIGN_GRADE, EXEC_GRADE) {
	//pass;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other)
	: AForm(other.getName(), other.getTarget(), SIGN_GRADE, EXEC_GRADE) {
	//pass;
}

ShrubberyCreationForm::~ShrubberyCreationForm(void) {
	//pass;
}

ShrubberyCreationForm	&ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other) {
	if (this == &other)
		return *this;
	AForm::operator=(other);
	return *this;
}

void	ShrubberyCreationForm::FormAction(void) const {
	std::ofstream	target((getTarget() + "_shrubbery").c_str());
	if (!target.is_open())
		throw std::runtime_error("[!] Error : could not open the file for writing.");
	target << SHRUBBERY;
	target.close();
}
