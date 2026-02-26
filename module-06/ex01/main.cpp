#include "Data.hpp"
#include <Serializer.hpp>
#include <iostream>



int main () {
	Data	data = {"hamid", 47, "love football"};

	std::cout << "Before:\n" << data;
	std::cout << "original: " << &data << std::endl;
	uintptr_t raw = Serializer::serialize(&data);
	std::cout << "serialized: " << raw << std::endl;
	Data* ptr = Serializer::deserialize(raw);
	std::cout << "deserialized: " << ptr << std::endl;
	std::cout << "after: \n" << *ptr; 
}
