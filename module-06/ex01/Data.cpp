#include <Data.hpp>
#include <ostream>

std::ostream	&operator<<(std::ostream &os, const Data data) {
	os << "name: " << data.name << std::endl; 
	os << "age: " << data.age << std::endl; 
	os << "desc: " << data.desc << std::endl; 
	return os;
}
