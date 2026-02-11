#pragma once
#include <AForm.hpp>

class PresidentialPardonForm : public AForm {
private:
	static std::string	_shrubbery;
public:
	PresidentialPardonForm(void);
	PresidentialPardonForm(const std::string &name);
	PresidentialPardonForm(const PresidentialPardonForm &other);
	~PresidentialPardonForm(void);

	PresidentialPardonForm	&operator=(const PresidentialPardonForm &other);

	void	FormAction(void);

};
