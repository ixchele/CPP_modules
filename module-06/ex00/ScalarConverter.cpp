#include <ScalarConverter.hpp>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iomanip>
#include <ios>
#include <iostream>
#include <limits>
#include <string>


bool	isPSeudoLiterals(const std::string &input) {
	std::string	pseudoLiterals [] = {
		"-inff", "+inff", "nanf",
		"-inf", "+inf", "nan",
		"",
	};
	
	for (size_t i = 0; !pseudoLiterals[i].empty(); i++) {
		if (pseudoLiterals[i] == input)
			return true;
	}

	return false;
}

void	handlePSeudoLiterals(std::string input) {
	std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;

    bool hasF = (input.at(input.size()-1) == 'f' && input != "inf" && input != "nan");

    std::string asFloat = hasF ? input : input + "f";
    std::string asDouble = hasF ? input.substr(0, input.size() - 1) : input;

    std::cout << "float: " << asFloat << std::endl;
    std::cout << "double: " << asDouble << std::endl;
}

void	printChar(const double val) {
	if (std::isnan(val) || val > std::numeric_limits<char>::max() || val < std::numeric_limits<char>::min())
		std::cout << "char: impossible" << std::endl;
	else if (std::isprint(static_cast<char>(val)) == false)
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: " << static_cast<char>(val) << std::endl;
}

void	printInt(const double val) {
	if (std::isnan(val) || val > std::numeric_limits<int>::max() || val < std::numeric_limits<int>::min())
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(val) << std::endl;
}

void	printFloat(const double val) {
	float f = static_cast<float>(val);
	if (std::isinf(f) == false)
		std::cout << std::fixed << std::setprecision(1);
	std::cout << "float: " << f << "f" << std::endl;
}

void	printDouble(const double val) {
	float d = static_cast<float>(val);
	if (std::isinf(d) == false)
		std::cout << std::fixed << std::setprecision(1);
	std::cout << "double: " << d << std::endl;
}

void	ScalarConverter::convert(const std::string &input) {

	if (isPSeudoLiterals(input)) {
		handlePSeudoLiterals(input);
		return ;
	}

	char *endPtr = NULL;
	double value = std::strtod(input.c_str(), &endPtr);
	if (*endPtr != '\0' && input.size() > 1) {
		std::cout << "[!] invalid argument." << std::endl;
		return ;
	}
	else if (*endPtr != '\0' && input.size() == 1) {
		value = static_cast<double>(input[0]);
	}

	printChar(value);
	printInt(value);
	printFloat(value);
	printDouble(value);
}
