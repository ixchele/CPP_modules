#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>

int main() {
	try {
		Bureaucrat boss("The Boss", 1);
		Bureaucrat intern("The Intern", 140);

		AForm *shrub = new ShrubberyCreationForm("Garden");
		AForm *robo = new RobotomyRequestForm("Bender");
		AForm *pardon = new PresidentialPardonForm("Ford Prefect");

		std::cout << "--- Shrubbery ---" << std::endl;
		boss.signForm(*shrub);
		try {
			intern.executeForm(*shrub);
		} catch (std::exception &e) {
			std::cerr << "Intern execution failed: " << e.what() << std::endl;
		}
		boss.executeForm(*shrub);

		std::cout << "\n--- Robotomy ---" << std::endl;
		boss.signForm(*robo);
		boss.executeForm(*robo);
		boss.executeForm(*robo);

		std::cout << "\n--- Pardon ---" << std::endl;
		boss.signForm(*pardon);
		boss.executeForm(*pardon);

		delete shrub;
		delete robo;
		delete pardon;

	} catch (std::exception &e) {
		std::cerr << "Critical Error: " << e.what() << std::endl;
	}

	return 0;
}
