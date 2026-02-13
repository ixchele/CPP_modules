#include <AForm.hpp>
#include <Intern.hpp>
#include <cctype>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>



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
	return "";
}

static std::string	sanitizeForm(const std::string &formName) {
	std::string	form = formName;

	strlower(form);
	removeSpaces(form);
	return validForm(form);
}

AForm	*Intern::makeForm(const std::string &formName, const std::string &target) const {
	(void)target;
	std::string validFormName = sanitizeForm(formName);
	if (validFormName.empty() == true)
		throw std::runtime_error("invalid from name");
	return NULL;
}
