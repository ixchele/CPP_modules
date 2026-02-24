#include "Data.hpp"
#include <Serializer.hpp>
#include <iostream>

int main () {
	Data	data = {"hamid", 47, "love football"};
	uintptr_t raw = Serializer::serialize(&data);
	Data* ptr = Serializer::deserialize(raw);

	if (ptr == &data)
		std::cout << "[✓] Nom : " << ptr->name << std::endl;
	else
		std::cout << "[✗] conversion error." << std::endl;
	return 0;
}
