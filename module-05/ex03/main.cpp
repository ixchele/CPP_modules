#include <iostream>
#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main() {

	std::cout << "--- 1. Tests Grades and Exceptions ---" << std::endl;
	try {
		Bureaucrat low("Stagiaire", 150);
		Bureaucrat high("Directeur", 1);

		ShrubberyCreationForm f1("Jardin");

		high.executeForm(f1);
	} catch (std::exception &e) {
		std::cerr << "Erreur : " << e.what() << std::endl;
	}

	std::cout << "\n--- 2. Test Shrubbery (file creation) ---" << std::endl;
	try {
		Bureaucrat b1("Gardener", 130);
		ShrubberyCreationForm f2("Garden");

		b1.signForm(f2);
		b1.executeForm(f2);
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	std::cout << "\n--- 3. Test Robotomy (50/50) ---" << std::endl;
	try {
		Bureaucrat b2("Scientifique", 40);
		RobotomyRequestForm f3("Bender");

		b2.signForm(f3);
		for (int i = 0; i < 4; i++) {
			std::cout << "try #" << i + 1 << " :" << std::endl;
			b2.executeForm(f3);
			std::cout << "---" << std::endl;
		}
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	std::cout << "\n--- 4. Test Presidential Pardon ---" << std::endl;
	try {
		Bureaucrat president("Zaphod Beeblebrox", 1);
		PresidentialPardonForm f4("Arthur Dent");

		president.signForm(f4);
		president.executeForm(f4);
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
