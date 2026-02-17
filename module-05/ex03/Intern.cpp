#include <AForm.hpp>
#include <Intern.hpp>
#include <iostream>
#include <cctype>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <PresidentialPardonForm.hpp>
#include <RobotomyRequestForm.hpp>
#include <ShrubberyCreationForm.hpp>

Intern::Intern() {}
Intern::Intern(const Intern& other) { *this = other; }
Intern& Intern::operator=(const Intern& other) { (void)other; return *this; }
Intern::~Intern() {}


AForm* Intern::makePresidential(const std::string &target) const {
    return new PresidentialPardonForm(target);
}

AForm* Intern::makeRobotomy(const std::string &target) const {
    return new RobotomyRequestForm(target);
}

AForm* Intern::makeShrubbery(const std::string &target) const {
    return new ShrubberyCreationForm(target);
}

static void	strlower(std::string &str) {
	for (size_t	i = 0; i < str.size(); ++i) {
		str[i] = std::tolower((unsigned char)str[i]);
	}
}

static void	removeSpaces(std::string &str) {
	for (size_t i = 0; i < str.size(); ++i) {
		if (std::isspace(str[i]) != false)
			str.erase(i, 1);
	}
}

static std::string	validForm(const std::string &form) {
	std::string	validForms[] = {
		"shrubberycreation",
		"robotomyrequest",
		"presidentialpardon",
	};
	std::string	realFormName[] = {
		"ShrubberyCreationForm",
		"RobotomyRequestForm",
		"PresidentialPardonForm",
	};

	for (size_t i = 0; i < 3; ++i) {
		if (form == validForms[i])
			return realFormName[i];
	}
	return std::string();
}

static std::string	sanitizeForm(const std::string &formName) {
	std::string	form = formName;

	strlower(form);
	removeSpaces(form);
	return validForm(form);
}

struct FormEntry {
	std::string	formName;
	AForm	*(Intern::*f)(const std::string &) const;
};

AForm	*Intern::makeForm(const std::string &formName, const std::string &target) const {
	(void)target;

	std::string validFormName = sanitizeForm(formName);
	if (validFormName.empty() == true)
		throw std::runtime_error("invalid from name");

	FormEntry	formPairs[] = {
		{"ShrubberyCreationForm", &Intern::makeShrubbery},
		{"RobotomyRequestForm", &Intern::makeRobotomy},
		{"PresidentialPardonForm", &Intern::makePresidential},
		{"", NULL},
	};

	for (size_t i = 0; formPairs[i].formName.empty() == false; i++) {
		if (validFormName == formPairs[i].formName) {
			std::cout << "Intern creates " << validFormName << std::endl;
			return (this->*(formPairs[i].f))(target);
		}
	}
	return NULL;
}
