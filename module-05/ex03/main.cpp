#include "Intern.hpp"
#include <iostream>

int main() {
    Intern someRandomIntern;
    AForm* rrf;

    try {
        rrf = someRandomIntern.makeForm("robotomy request", "Bender");
        std::cout << *rrf << std::endl;
        delete rrf;
    }
    catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << "---------------------------------" << std::endl;

    try {
        rrf = someRandomIntern.makeForm("shrubbery creation", "Home");
        std::cout << *rrf << std::endl;
        delete rrf;
    }
    catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << "---------------------------------" << std::endl;

    try {
        rrf = someRandomIntern.makeForm("coffee request", "Boss");
        std::cout << *rrf << std::endl;
        delete rrf;
    }
    catch (std::exception& e) {
        std::cerr << "Caught Exception: " << e.what() << std::endl;
    }

    return 0;
}
