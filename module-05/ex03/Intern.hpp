#pragma once
#include <AForm.hpp>

struct Intern {
private:
    AForm* makePresidential(const std::string &target) const;
    AForm* makeRobotomy(const std::string &target) const;
    AForm* makeShrubbery(const std::string &target) const;
public:
	Intern();
	Intern(const Intern& other); // = delete
	~Intern();

	Intern& operator=(const Intern& other); // = delete
	//
	AForm	*makeForm(const std::string &formName, const std::string &target) const;
};
