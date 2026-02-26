#pragma once

#include <ostream>
#include <string>
struct Data {
	std::string	name;
	int			age;
	std::string	desc;
};
std::ostream &operator<<(std::ostream &os, const Data data);
