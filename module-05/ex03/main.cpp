#include "Intern.hpp"
#include <iostream>

int main() {
    Intern someRandomIntern;
    AForm* rrf = NULL;

    try {
        rrf = someRandomIntern.makeForm("robotomy request", "Bender");
        if (rrf) {
            std::cout << "Form " + rrf->getName() + " created!" << std::endl;
            delete rrf;
        }

        std::cout << "---" << std::endl;

        AForm* unknown;
        unknown = someRandomIntern.makeForm("invalid form name", "Target");
        delete unknown;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception catched : " << e.what() << std::endl;
    }

    return 0;
}
