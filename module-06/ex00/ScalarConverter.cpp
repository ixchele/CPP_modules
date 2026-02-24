#include <ScalarConverter.hpp>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iomanip>
#include <ios>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>


void	printChar(const double val) {
	if (std::isnan(val) || val > std::numeric_limits<char>::max() || val < std::numeric_limits<char>::min())
		std::cout << "char: impossible" << std::endl;
	else if (std::isprint(static_cast<char>(val)) == false)
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: '" << static_cast<char>(val) << "'" << std::endl;
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
	std::cout << "double: " << val << std::endl;
}

bool	handlePSeudoLiterals(std::string input) {
	char	*endPtr = NULL;
	double	val = std::strtod(input.c_str(), &endPtr);
	if (*endPtr != '\0' && *endPtr != 'f')
		return false;
	printChar(val);
	printInt(val);
	printFloat(val);
	printDouble(val);
	return true;
}

void	ScalarConverter::convert(const std::string &input) {
	std::stringstream	sstream(input);
	double				val;

	if (!(sstream >> val)) {
		if (handlePSeudoLiterals(input) == false)
			std::cout << "[!] invalid argument." << std::endl; 
		return;
	}

	std::string	remaining;
	sstream >> remaining;

	if (!remaining.empty() && remaining != "f") {
		std::cout << "[!] invalid end argument." << std::endl; 
		return;
	}
	printChar(val);
	printInt(val);
	printFloat(val);
	printDouble(val);
}
