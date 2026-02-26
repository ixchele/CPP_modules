#include "Base.hpp"
#include <fstream>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <A.hpp>
#include <B.hpp>
#include <C.hpp>

struct GetRandomException : public std::runtime_error {
	GetRandomException(const std::string &error) : std::runtime_error(error) {};
};

std::size_t	getRandom(void) {
	unsigned int	value = 0;
	std::ifstream	file("/dev/urandom");
	if (!file.is_open()) {
		throw GetRandomException("[x] couldn't open the file urandom");
	}
	file.read(reinterpret_cast<char*>(&value), sizeof(value));
	file.close();
	return value;
}

bool	oncChanceIn(std::size_t x) {
	return (x != 0 && getRandom() % x == 0);
}

Base	*generate(void) {
	std::size_t	val = getRandom() % 3;
	switch (val) {
		case 0 : return new A();
		case 1 : return new B();
		case 2 : return new C();
		default: return NULL;
	}
}

int main() {
	try {
		
	} catch (declaration) {
	
	}

}
