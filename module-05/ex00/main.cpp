#include <iostream>
#include <Bureaucrat.hpp>

int main() {
	std::cout << "=== TEST 1 : Création normale ===" << std::endl;
	try {
		Bureaucrat a("Alice", 42);
		Bureaucrat b("Bob", 1);
		Bureaucrat c("Charlie", 150);

		std::cout << a << std::endl;
		std::cout << b << std::endl;
		std::cout << c << std::endl;
	} catch (std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 2 : Incrément / Décrément ===" << std::endl;
	try {
		Bureaucrat d("David", 3);
		std::cout << d << std::endl;

		d.incrementGrade(); // 3 -> 2
		std::cout << "After increment: " << d << std::endl;

		d.decrementGrade(); // 2 -> 3
		std::cout << "After decrement: " << d << std::endl;
	} catch (std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 3 : Trop haut (grade 0) ===" << std::endl;
	try {
		Bureaucrat e("ErrorHigh", 0);
		std::cout << e << std::endl;
	} catch (std::exception &e) {
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 4 : Trop bas (grade 151) ===" << std::endl;
	try {
		Bureaucrat f("ErrorLow", 151);
		std::cout << f << std::endl;
	} catch (std::exception &e) {
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 5 : Incrément impossible ===" << std::endl;
	try {
		Bureaucrat g("God", 1);
		std::cout << g << std::endl;
		g.incrementGrade(); // doit throw
	} catch (std::exception &e) {
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 6 : Décrément impossible ===" << std::endl;
	try {
		Bureaucrat h("Peasant", 150);
		std::cout << h << std::endl;
		h.decrementGrade(); // doit throw
	} catch (std::exception &e) {
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	return 0;
}
