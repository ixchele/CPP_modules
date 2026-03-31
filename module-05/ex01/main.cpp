#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>

int main() {
    try {
        Bureaucrat bob("Bob", 50);
        Form taxForm("Tax Form 28B", 45, 10);

        std::cout << taxForm << std::endl;
        bob.signForm(taxForm);

        for (int i = 0; i < 6; i++) 
            bob.incrementGrade();
        
        std::cout << bob << std::endl;
        bob.signForm(taxForm);
        std::cout << taxForm << std::endl;

    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
