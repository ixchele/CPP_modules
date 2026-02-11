#include <ShrubberyCreationForm.hpp>
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm(void) : AForm("ShrubberyCreationForm", 145, 137), _target("default"){
	//pass;
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target) : AForm("ShrubberyCreationForm", 145, 137), _target(target) {
	//pass;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other)
	: AForm(other.getName(), 145, 137) {
	//pass;
}

ShrubberyCreationForm::~ShrubberyCreationForm(void) {
	//pass;
}

ShrubberyCreationForm	&ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other) {
	if (this != &other)
		return *this;
	_target = other._target;
	return *this;
}

void	ShrubberyCreationForm::FormAction(void) const {
	std::ofstream	target((_target + "_shrubbery").c_str());

	if (!target.is_open())
		throw std::runtime_error("[!] Error : could not open the file for writing.");
	target << SHRUBBERY;
	target.close();
}
